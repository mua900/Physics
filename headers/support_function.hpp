#pragma once

#include <vector.hpp>
#include <shape.hpp>
#include <array>

const vector2& support_function(const polygon& polygon, const vector2& direction);
/// @brief the support_function that returns the two farthest point
/// @return two vertices that have the two biggest dot product with the given direction
std::array<vector2, 2> support_function_two(const polygon& polygon, const vector2& direction);
