#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include "resolver.hpp"
#include "stage.hpp"
#include "types.hpp"

namespace tensor::tql {

enum class Mutation {
    None,
    Insert,
    Update,
    Delete,
    Upsert,
    Truncate,
};

struct RowField {
    std::string name;
    ExprPtr     value;
};

struct InsertPayload {
    std::vector<std::vector<RowField>> rows;
    bool                               is_from_query = false;
};

struct UpdatePayload {
    std::vector<RowField> set_fields;
};

struct UpsertPayload {
    std::string           conflict_field;
    std::vector<RowField> values;
    std::vector<RowField> conflict_set;
};

struct ReturningField {
    std::string name;
    ExprPtr     value;
    bool        is_mutation_field = false;
};

class Pipeline {
public:
    // resolver may be nullptr — imports are skipped and UserDefined types
    // remain unresolved. Variable scope and structural checks still run.
    [[nodiscard]] static Result<Pipeline> compile(
        std::string_view source,
        PackageResolver* resolver = nullptr
    );

    [[nodiscard]] std::string_view       target()    const noexcept { return target_;   }
    [[nodiscard]] std::string_view       from_var()  const noexcept { return from_var_; }
    [[nodiscard]] const TypeRef&         type()      const noexcept { return type_;     }
    [[nodiscard]] Mutation               mutation()  const noexcept { return mutation_; }
    [[nodiscard]] const PackageRegistry& registry()  const noexcept { return registry_; }

    [[nodiscard]] const std::vector<Stage>& stages() const noexcept { return stages_; }

    [[nodiscard]] const InsertPayload* insert_payload() const noexcept {
        return insert_.has_value() ? &insert_.value() : nullptr;
    }
    [[nodiscard]] const UpdatePayload* update_payload() const noexcept {
        return update_.has_value() ? &update_.value() : nullptr;
    }
    [[nodiscard]] const UpsertPayload* upsert_payload() const noexcept {
        return upsert_.has_value() ? &upsert_.value() : nullptr;
    }

    [[nodiscard]] bool has_returning() const noexcept { return !returning_.empty(); }
    [[nodiscard]] const std::vector<ReturningField>& returning_fields() const noexcept {
        return returning_;
    }

private:
    friend class Compiler;

    Pipeline() = default;

    std::string        target_;
    std::string        from_var_;      // alias of the primary from/mutation binding
    TypeRef            type_;
    Mutation           mutation_ = Mutation::None;
    PackageRegistry    registry_;      // populated by Pass 1

    std::vector<Stage> stages_;

    std::optional<InsertPayload> insert_;
    std::optional<UpdatePayload> update_;
    std::optional<UpsertPayload> upsert_;

    std::vector<ReturningField> returning_;
};

} // namespace tensor::tql