#pragma once

#include <cassert>
#include <vector>
#include <line.hpp>
#include <support_function.hpp>
#include <shape.hpp>
#include <vector.hpp>
#include <utils.hpp>

bool aabb(const rectangle& rect1, const rectangle& rect2);

#define GJK_MAX_ITERATIONS 30

bool gjk(const polygon& polygon1, const polygon& polygon2);

inline bool check_point_passing_origin(const vector2& anchor, const vector2& point);

bool gjk_line_case(std::array<vector2, 3>& line_points, const polygon& p1, const polygon& p2);

bool gjk_triangle_case(std::array<vector2, 3> simplex, const polygon& p1, const polygon& p2);

vector2 epa(const triangle& simplex, const polygon& poly1, const polygon&);
