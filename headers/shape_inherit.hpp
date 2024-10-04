#pragma once

#include <shape.hpp>
#include <cmath>
#include <debug.hpp>
#include <cstdint>
#include <array>
#include <vector>
#include <vector.hpp>
#include <support_function.hpp>

#define bounding_volume_extra 0
struct bounding_rect {
	vector2 position;
	float width, height;
};

class shape
{
public:
    vector2 position;

	/*
    enum class type : uint8_t
    {
        base = 0,
        circle,
        triangle,
        rectangle,
        rectangle_v,
        polygon
    } base;
	*/

    shape();
    shape(const shape& other);
    virtual ~shape();
    virtual shape operator=(const shape& other);
    virtual bool contains(const vector2& point) const;
    virtual float area_radius() const;
    /// does the calculation on the function call
    virtual bounding_rect bounding_rectangle() const;
};

class circle_i : public shape
{
public:
    float radius;

    circle_i(const vector2& pos, const float& radius);
    bool contains(const vector2& point) const override;
    float area_radius() const override;
    bounding_rect bounding_rectangle() const override;
};

class triangle_i : public shape
{
public:
    std::array<vector2, 3> vertices;

    explicit triangle_i(const std::array<vector2, 3>& p_vertices);
    bool contains(const vector2& point) const override;
    float area_radius() const override;
    bounding_rect bounding_rectangle() const override;
};

class rectangle_i : public shape
{
public:
    float width, height;
    float rotation_in_radians;

    /*
        1,B----A,0
          |    |
        2,C----D,3
    */
    rectangle_i(const vector2& pos, const float& width, const float& height, const float& rotation_in_radians);
    bool contains(const vector2& point) const override;
    float area_radius() const override;
    bounding_rect bounding_rectangle() const override;
};

class rectangle_v_i : public shape
{
public:
    /*
        2,B-----A,1
          |  P  |
        3,C-----D,4
    */
	// position is already on the base class shape

   /// @brief local coordinates
    std::array<vector2, 4> vertices{};

    rectangle_v_i(const vector2& pos, const float& width, const float& height, const float& rot_in_radians);
    bool contains(const vector2& point) const override;
    float area_radius() const override;
    bounding_rect bounding_rectangle() const override;
};

class polygon_i : public shape
{
public:
    std::vector<vector2> vertices;

    explicit polygon_i(const std::vector<vector2>& vertices);
    bool contains(const vector2& point) const override;
    float area_radius() const override;
    bounding_rect bounding_rectangle() const override;
};
