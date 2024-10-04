#pragma once

#include "vector.hpp"
#include <array>

struct line
{
    vector2 param_vec{};
    vector2 start_vec{};
    line(vector2& point1, vector2& point2);
    bool on_line(const vector2& point) const;
};

struct line_segment
{
    vector2 point0{}, point1{};

    line_segment();
    line_segment(const vector2& p_point0, const vector2& p_point1);
    line_segment(const std::array<vector2, 2>& points);

    ~line_segment() = default;

    bool on_line_segment(const vector2& point);

    vector2 facing_normal(const vector2& point) const;
    vector2 mid_point() const;
    vector2 projection(const vector2& point) const;
};

/// @brief parametirized representation of line segment
struct line_segment_t
{
    line base_line; 
    float t0, t1;

    line_segment_t(line  base_line, const float& t0, const float& t1);
};