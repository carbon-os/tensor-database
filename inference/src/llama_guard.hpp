// Internal header — not installed, not included by any public header.
// Ensures llama_backend_init() is called exactly once across all engine
// instances in the process.

#pragma once

#include <llama.h>
#include <mutex>

namespace tensor::inference::detail {

inline void ensure_backend_init() noexcept {
    static std::once_flag flag;
    std::call_once(flag, [] { llama_backend_init(); });
}

} // namespace tensor::inference::detail