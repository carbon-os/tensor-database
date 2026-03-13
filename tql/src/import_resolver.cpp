// Pass 1 — Import resolution.
// Walks importDecl nodes in the executable file context, calls
// PackageResolver for each path, parses the returned package source,
// and registers all declared types into a PackageRegistry.

#include "semantic.hpp"
#include "TQLLexer.h"
#include "TQLParser.h"
#include "TQLParserBaseVisitor.h"
#include <antlr4-runtime.h>

namespace tensor::tql {

namespace {

static std::string strip_quotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

// ── Reads a parsed packageFile tree and extracts its type declarations ─────

class PackageFileReader : public TQLParserBaseVisitor {
public:
    std::string           package_name;
    std::vector<TypeDecl> types;

    std::any visitPackageDecl(TQLParser::PackageDeclContext* ctx) override {
        package_name = ctx->IDENTIFIER()->getText();
        return {};
    }

    std::any visitTypeDecl(TQLParser::TypeDeclContext* ctx) override {
        TypeDecl decl;
        decl.name = ctx->IDENTIFIER()->getText();
        for (auto* fd : ctx->fieldDecl()) {
            FieldDef f;
            f.name = fd->IDENTIFIER()->getText();
            f.type = resolve_type(fd->typeExpr());
            decl.fields.push_back(std::move(f));
        }
        types.push_back(std::move(decl));
        return {};
    }

private:
    TypeRef resolve_type(TQLParser::TypeExprContext* ctx) {
        TypeRef t;
        if (auto* s = dynamic_cast<TQLParser::ScalarTypeExprContext*>(ctx)) {
            t = resolve_scalar(s->scalarType());
            t.nullable = s->QUESTION() != nullptr;
        } else if (auto* v = dynamic_cast<TQLParser::VectorTypeExprContext*>(ctx)) {
            t.kind       = TypeRef::Kind::Vector;
            t.vector_dim = static_cast<uint32_t>(std::stoul(v->INTEGER_LIT()->getText()));
            t.nullable   = v->QUESTION() != nullptr;
        } else if (auto* a = dynamic_cast<TQLParser::ArrayTypeExprContext*>(ctx)) {
            t.kind     = TypeRef::Kind::Array;
            t.nullable = a->QUESTION() != nullptr;
        } else if (auto* j = dynamic_cast<TQLParser::JsonTypeExprContext*>(ctx)) {
            t.kind     = TypeRef::Kind::Json;
            t.nullable = j->QUESTION() != nullptr;
        } else if (auto* u = dynamic_cast<TQLParser::UserDefinedTypeExprContext*>(ctx)) {
            t.kind = TypeRef::Kind::UserDefined;
            auto ids = u->qualifiedTypeName()->IDENTIFIER();
            if (ids.size() == 2) {
                t.package = ids[0]->getText();
                t.name    = ids[1]->getText();
            } else {
                t.name = ids[0]->getText();
            }
            t.nullable = u->QUESTION() != nullptr;
        }
        return t;
    }

    TypeRef resolve_scalar(TQLParser::ScalarTypeContext* ctx) {
        TypeRef t;
        if      (ctx->INT32())        t.kind = TypeRef::Kind::Int32;
        else if (ctx->INT64())        t.kind = TypeRef::Kind::Int64;
        else if (ctx->FLOAT32())      t.kind = TypeRef::Kind::Float32;
        else if (ctx->FLOAT64())      t.kind = TypeRef::Kind::Float64;
        else if (ctx->BOOL_KW())      t.kind = TypeRef::Kind::Bool;
        else if (ctx->TEXT_KW())      t.kind = TypeRef::Kind::Text;
        else if (ctx->UUID_KW())      t.kind = TypeRef::Kind::Uuid;
        else if (ctx->TIMESTAMP_KW()) t.kind = TypeRef::Kind::Timestamp;
        else if (ctx->DECIMAL_KW()) {
            t.kind = TypeRef::Kind::Decimal;
            auto lits = ctx->INTEGER_LIT();
            t.decimal.precision = static_cast<uint8_t>(std::stoi(lits[0]->getText()));
            t.decimal.scale     = static_cast<uint8_t>(std::stoi(lits[1]->getText()));
        }
        return t;
    }
};

// ── Parse a package source into a PackageFileReader ───────────────────────

static Result<PackageFileReader> parse_package(
    const std::string& source,
    std::string_view   import_path
) {
    antlr4::ANTLRInputStream  input(source.data(), source.size());
    TQLLexer                  lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    TQLParser                 parser(&tokens);

    std::optional<Error> err;
    struct EL : antlr4::BaseErrorListener {
        std::optional<Error>* err;
        void syntaxError(antlr4::Recognizer*, antlr4::Token*,
                         size_t line, size_t col,
                         const std::string& msg, std::exception_ptr) override {
            if (!*err) *err = Error{ msg, line, col };
        }
    } el;
    el.err = &err;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&el);
    parser.removeErrorListeners();
    parser.addErrorListener(&el);

    auto* tree = parser.file();

    if (err)
        return Result<PackageFileReader>::failure(Error{
            "in package \"" + std::string(import_path) + "\": " + err->message,
            err->line, err->column
        });

    auto* pkg = dynamic_cast<TQLParser::PackageFileContext*>(tree);
    if (!pkg)
        return Result<PackageFileReader>::failure(Error{
            "imported file \"" + std::string(import_path) +
            "\" is not a package file (missing 'package' declaration)",
            0, 0
        });

    PackageFileReader reader;
    reader.visit(tree);
    return Result<PackageFileReader>::success(std::move(reader));
}

} // anonymous namespace

// ── Pass 1 entry point ────────────────────────────────────────────────────

Result<PackageRegistry> resolve_imports(
    TQLParser::ExecutableFileContext* ctx,
    PackageResolver*                  resolver
) {
    PackageRegistry registry;

    if (ctx->importDecl().empty())
        return Result<PackageRegistry>::success(std::move(registry));

    // No resolver — skip silently. UserDefined type fields will be unresolved;
    // the scope and type checkers degrade gracefully in this case.
    if (!resolver)
        return Result<PackageRegistry>::success(std::move(registry));

    for (auto* imp : ctx->importDecl()) {
        std::string path = strip_quotes(imp->STRING_LIT()->getText());

        auto source_result = resolver->resolve(path);
        if (!source_result.ok()) {
            Error e = source_result.error();
            if (e.line == 0) {
                e.line   = imp->getStart()->getLine();
                e.column = imp->getStart()->getCharPositionInLine();
            }
            return Result<PackageRegistry>::failure(std::move(e));
        }

        auto pkg_result = parse_package(source_result.value(), path);
        if (!pkg_result.ok())
            return Result<PackageRegistry>::failure(pkg_result.error());

        auto& reader = pkg_result.value();
        for (auto& decl : reader.types)
            registry.register_type(reader.package_name, std::move(decl));
    }

    return Result<PackageRegistry>::success(std::move(registry));
}

} // namespace tensor::tql