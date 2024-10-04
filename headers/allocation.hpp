#pragma once

#define MAX_ALLOC (1024 * 1024 * 4) // 4 MB
#include <cstdlib>
#include <cstddef>

/// @brief a wrapper around malloc, returns malloc(size) NULL if size exceeds a predefined value
void *c_alloc(size_t size);
