#pragma once

#include "debug.hpp"

#include <utility>
#include <cmath>

struct vector2
{
    float x, y;

	vector2() = default;
    vector2(const float& p_x, const float& p_y);
    vector2(const float&& p_x, const float&& p_y);
    ~vector2() = default;
    vector2(const vector2& other);
    vector2 operator+(const vector2& other) const;
    vector2 operator-(const vector2& other) const;
    vector2 operator*(const float& scalar) const;
    vector2 operator/(const float& scalar) const;
    float magnitude_squared() const;
    float magnitude() const;
    vector2 perpendicular() const;
    vector2 normalized() const;
    vector2 operator-() const;
    bool operator==(const vector2& other) const;
    bool operator!=(const vector2& other) const;
    void operator+=(const vector2& other);
    void operator/=(const float& scalar);
};

bool v2_equals(const vector2& v1, const vector2& v2);

float dot2(const vector2& v, const vector2& u);

struct matrix2x2
{
    // column
    vector2 c1, c2;

    matrix2x2(const vector2&  c1, const vector2&  c2);
    matrix2x2() = default;
    ~matrix2x2() = default;
    float determinant() const;
    vector2 transform(const vector2& v) const;

	/// @brief constructs and returns the transpose matrix
    matrix2x2 transpose() const;
};

struct vector3
{
    float x, y, z;

    explicit vector3(const vector2& vec2);
    vector3(const float& p_x, const float& p_y, const float& p_z);
    vector3(const float&& p_x, const float&& p_y, const float& p_z);
    ~vector3() = default;
    vector3(const vector3& other);
    vector3& operator=(const vector3& other);
    vector3 operator+(const vector3& other) const;
    vector3 operator-(const vector3& other) const;
    vector3 operator*(const float& scalar) const;
    vector3 operator/(const float& scalar) const;
    float magnitude_squared() const;
    float magnitude() const;
    vector3 normalized() const;
};

float dot3(const vector3& v, const vector3& u);
vector3 cross(const vector3& v, const vector3& u);

struct vector4
{
    float x, y, z, w;

	vector4() = default;
    vector4(const float& p_x, const float& p_y, const float& p_z, const float& p_w);
    vector4(const float&& p_x, const float&& p_y, const float&& p_z, const float&& p_w);
    ~vector4() = default;
    vector4(const vector4& other) = default;
    vector4 operator+(const vector4& other) const;
    vector4 operator-(const vector4& other) const;
    vector4 operator*(const float& scalar) const;
    vector4 operator/(const float& scalar) const;
    float magnitude_squared() const;
    float magnitude() const;
    vector4 perpendicular() const;
    vector4 normalized() const;
    vector4 operator-() const;
    bool operator==(const vector4& other) const;
    bool operator!=(const vector4& other) const;
    void operator+=(const vector4& other);
    void operator/=(const float& scalar);
};

bool v4_equals(const vector4& v, const vector4& u);
float dot4(const vector4& v, const vector4& u);

struct matrix4x4
{
	vector4 c1,c2,c3,c4;

	matrix4x4() = default;
	matrix4x4(const vector4& p_c1, const vector4& p_c2, const vector4& p_c3, const vector4& p_c4);
	~matrix4x4() = default;
	float determinant() const;
	vector4 transform(const vector4& v) const;

	

	/// @brief constructs and returns the transpose matrix
	matrix4x4 transpose() const;
};
