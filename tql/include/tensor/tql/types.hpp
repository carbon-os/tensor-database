#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace tensor::tql {

// ── Decimal precision/scale ───────────────────────────────────────────────

struct DecimalSpec {
    uint8_t precision = 0;
    uint8_t scale     = 0;
};

// ── Type reference ────────────────────────────────────────────────────────

struct TypeRef {
    enum class Kind {
        Int32, Int64, Float32, Float64, Decimal,
        Bool, Text, Uuid, Timestamp,
        Json, Array, Vector,
        UserDefined,
    };

    Kind        kind       = Kind::Int32;
    bool        nullable   = false;
    uint32_t    vector_dim = 0;
    DecimalSpec decimal    = {};
    std::string package;
    std::string name;

    // ── Convenience factories ─────────────────────────────────────────────

    static TypeRef make_bool()      noexcept { TypeRef t; t.kind = Kind::Bool;      return t; }
    static TypeRef make_int32()     noexcept { TypeRef t; t.kind = Kind::Int32;     return t; }
    static TypeRef make_int64()     noexcept { TypeRef t; t.kind = Kind::Int64;     return t; }
    static TypeRef make_float64()   noexcept { TypeRef t; t.kind = Kind::Float64;   return t; }
    static TypeRef make_text()      noexcept { TypeRef t; t.kind = Kind::Text;      return t; }
    static TypeRef make_uuid()      noexcept { TypeRef t; t.kind = Kind::Uuid;      return t; }
    static TypeRef make_timestamp() noexcept { TypeRef t; t.kind = Kind::Timestamp; return t; }

    // ── Predicates ────────────────────────────────────────────────────────

    bool is_numeric() const noexcept {
        return kind == Kind::Int32   || kind == Kind::Int64  ||
               kind == Kind::Float32 || kind == Kind::Float64 ||
               kind == Kind::Decimal;
    }
    bool is_bool()      const noexcept { return kind == Kind::Bool; }
    bool is_text()      const noexcept { return kind == Kind::Text; }
    bool is_uuid()      const noexcept { return kind == Kind::Uuid; }
    bool is_timestamp() const noexcept { return kind == Kind::Timestamp; }
    bool is_vector()    const noexcept { return kind == Kind::Vector; }

    bool is_comparable() const noexcept {
        return is_numeric() || is_text() || is_uuid() || is_timestamp();
    }

    bool is_unresolved() const noexcept {
        // UserDefined type whose fields could not be looked up in the registry.
        return kind == Kind::UserDefined;
    }

    // ── Equality ──────────────────────────────────────────────────────────

    bool operator==(const TypeRef& o) const noexcept {
        if (kind != o.kind || nullable != o.nullable) return false;
        if (kind == Kind::Vector)      return vector_dim == o.vector_dim;
        if (kind == Kind::Decimal)     return decimal.precision == o.decimal.precision &&
                                              decimal.scale     == o.decimal.scale;
        if (kind == Kind::UserDefined) return package == o.package && name == o.name;
        return true;
    }
    bool operator!=(const TypeRef& o) const noexcept { return !(*this == o); }

    std::string qualified_name() const {
        if (package.empty()) return name;
        return package + "." + name;
    }
};

// ── Field definition ──────────────────────────────────────────────────────

struct FieldDef {
    std::string name;
    TypeRef     type;
};

// ── Type declaration ──────────────────────────────────────────────────────

struct TypeDecl {
    std::string           name;
    std::vector<FieldDef> fields;

    const FieldDef* find_field(std::string_view n) const noexcept {
        for (const auto& f : fields)
            if (f.name == n) return &f;
        return nullptr;
    }
};

// ── Package registry ——— built by ImportResolver (Pass 1) ─────────────────
// Maps package_name → type_name → TypeDecl.

class PackageRegistry {
public:
    void register_type(const std::string& pkg, TypeDecl decl) {
        packages_[pkg][decl.name] = std::move(decl);
    }

    const TypeDecl* find(std::string_view pkg, std::string_view type) const noexcept {
        auto pi = packages_.find(std::string(pkg));
        if (pi == packages_.end()) return nullptr;
        auto ti = pi->second.find(std::string(type));
        return ti == pi->second.end() ? nullptr : &ti->second;
    }

    const TypeDecl* find(const TypeRef& ref) const noexcept {
        if (ref.kind != TypeRef::Kind::UserDefined) return nullptr;
        return find(ref.package, ref.name);
    }

    bool empty() const noexcept { return packages_.empty(); }

private:
    std::unordered_map<std::string,
        std::unordered_map<std::string, TypeDecl>> packages_;
};

// ── Error ─────────────────────────────────────────────────────────────────

struct Error {
    std::string message;
    size_t      line   = 0;
    size_t      column = 0;
};

// ── Result<T> ─────────────────────────────────────────────────────────────

template <typename T>
class Result {
public:
    [[nodiscard]] static Result success(T v)     { return Result{std::move(v)}; }
    [[nodiscard]] static Result failure(Error e) { return Result{std::move(e)}; }

    [[nodiscard]] bool ok() const noexcept { return std::holds_alternative<T>(data_); }

    T&           value()       { return std::get<T>(data_); }
    const T&     value() const { return std::get<T>(data_); }
    const Error& error() const { return std::get<Error>(data_); }

private:
    explicit Result(T v)     : data_(std::move(v)) {}
    explicit Result(Error e) : data_(std::move(e)) {}

    std::variant<T, Error> data_;
};

// ── Result<void> specialisation ───────────────────────────────────────────

template <>
class Result<void> {
public:
    [[nodiscard]] static Result success()        { return Result{true}; }
    [[nodiscard]] static Result failure(Error e) { return Result{std::move(e)}; }

    [[nodiscard]] bool ok() const noexcept { return std::holds_alternative<bool>(data_); }

    const Error& error() const { return std::get<Error>(data_); }

private:
    explicit Result(bool)    : data_(true) {}
    explicit Result(Error e) : data_(std::move(e)) {}

    std::variant<bool, Error> data_;
};

} // namespace tensor::tql