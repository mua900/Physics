#pragma once

#include <debug.hpp>
#include <vector.hpp>
#include <variant>
#include <cstdint>
#include <vector>
#include <algorithm>

enum class shape_type : uint8_t {
    Circle = 0,
    Triangle,
    Rectangle,
    Polygon
};

struct circle
{
    vector2 position;
    float radius;
    const shape_type shapeType = shape_type::Circle;

    bool contains(const vector2& point);
};
struct triangle{
    vector2 center;
    vector2 vertex1, vertex2, vertex3;
    const shape_type shapeType = shape_type::Triangle;

    triangle(const vector2& p_vertex1,const vector2& p_vertex2,const vector2& p_vertex3);

    explicit triangle(const std::array<vector2, 3>& points);

    bool contains(const vector2& point) const;
};
struct rectangle
{
    vector2 position;
    float width, height;
    float rotation_in_radians;
    const shape_type shapeType = shape_type::Rectangle;

    rectangle(const vector2& position, const float& w, const float& h, const float& rotation_in_radians);

    bool contains(const vector2& point) const;
};
struct polygon
{
    vector2 center;
    std::vector<vector2> vertices;
    const shape_type shapeType = shape_type::Polygon;

    explicit polygon(const std::vector<vector2>& vertices);

    //TODO maybe make this private
    /// @brief we call this function in the constructor
    void order();

    bool contains(const vector2& point);
};
