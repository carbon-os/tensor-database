#pragma once

#include <string_view>
#include "types.hpp"

namespace tensor::tql {

// ── PackageResolver — interface implemented by db::Engine ────────────────
//
// tql/ has no filesystem access. db::Engine knows where package files live
// on disk. Pipeline::compile() accepts a pointer to this interface.
//
// If null is passed, imports are silently skipped. UserDefined type
// references remain unresolved and field-level validation is bypassed.
// Variable scope (var names and their base types) is still enforced.

class PackageResolver {
public:
    virtual ~PackageResolver() = default;

    // Given an import path (e.g. "shared/commerce"), return the full source
    // text of the corresponding .tql package file, or an Error if not found.
    virtual Result<std::string> resolve(std::string_view import_path) = 0;
};

} // namespace tensor::tql