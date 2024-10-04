#include <utils.hpp>
#include <vector.hpp>

// the void(0) thing is just a hack for getting around the compiler warnings and maybe doesn't work for other compilers return to this


vector2::vector2(const float& p_x, const float& p_y)
    :
    x(p_x), y(p_y)
{}

vector2::vector2(const float&& p_x, const float&& p_y)
    :
    x(p_x), y(p_y)
{}

vector2::vector2(const vector2& other) = default;
vector2 vector2::operator+(const vector2& other) const{return {x + other.x, y + other.y};}
vector2 vector2::operator-(const vector2& other) const{return {x - other.x, y - other.y};}
vector2 vector2::operator*(const float& scalar) const{return {x * scalar, y * scalar};}
vector2 vector2::operator/(const float& scalar) const
{
    if (scalar != 0)
        return {x / scalar, y / scalar};
    else
    {
        d_log("Divide by zero in vector2", l_warning); void(0);
	}
}
float vector2::magnitude_squared() const {return x * x + y * y;}
float vector2::magnitude() const{return std::sqrt(x * x + y * y);}
vector2 vector2::perpendicular() const {return {-y, x};}
vector2 vector2::normalized() const
{
    float mag = magnitude();
    if(mag != 0){return {x / mag, y / mag};}
    else {d_log("Divide by zero in vector2", l_warning); void(0);}
}
vector2 vector2::operator-() const {return {-x,-y};}
bool vector2::operator==(const vector2& other) const{return x == other.x && y == other.y;}
bool vector2::operator!=(const vector2& other) const{return x != other.x || y != other.y;}
void vector2::operator+=(const vector2& other){x += other.x; y += other.y;}
void vector2::operator/=(const float& scalar)
{
    if (scalar == 0)
        d_log("Divide by zero in vector2", l_warning);
    x /= scalar;
    y /= scalar;
}

bool v2_equals(const vector2& v1, const vector2& v2)
{
    return utils::float_equality(v1.x, v2.x) && utils::float_equality(v1.y, v2.y);
}

float dot2(const vector2& v, const vector2& u)
{
    return v.x * u.x + v.y * u.y;
}


matrix2x2::matrix2x2(const vector2&  c1, const vector2&  c2) : c1(c1), c2(c2){}
float matrix2x2::determinant() const {return c1.x * c2.y - c1.y - c2.x;}
vector2 matrix2x2::transform(const vector2& v) const {return {v.x * c1.x + v.y * c2.x, v.x * c1.y + v.y * c2.y};}

matrix2x2 matrix2x2::transpose() const {
	return {{c1.x, c2.x}, {c1.y, c2.y}};
}

vector3::vector3(const vector2& vec2)
    : x(vec2.x), y(vec2.y), z(0)
{}

vector3::vector3(const float& p_x, const float& p_y, const float& p_z)
    : x(p_x), y(p_y), z(p_z)
{}

vector3::vector3(const float&& p_x, const float&& p_y, const float& p_z)
    :
    x(p_x), y(p_y), z(p_z)
{}

vector3::vector3(const vector3& other) = default;
vector3& vector3::operator=(const vector3& other) = default;
vector3 vector3::operator+(const vector3& other) const {return {x + other.x, y + other.y, z + other.z};}
vector3 vector3::operator-(const vector3& other) const {return {x - other.x, y - other.y, z - other.z};}
vector3 vector3::operator*(const float& scalar) const {return {x * scalar, y * scalar, z * scalar};}
vector3 vector3::operator/(const float& scalar) const
{
    if (scalar != 0)
        return {x / scalar, y / scalar, z / scalar};
    else
    {
        d_log("Divide by zero in vector3", l_warning); void(0);
	}
}
float vector3::magnitude_squared() const {return x * x + y * y + z * z;}
float vector3::magnitude() const {return std::sqrt(x * x + y * y + z * z);}
vector3 vector3::normalized() const {
    float mag = magnitude();
    if(mag != 0){return {x / mag, y / mag, z / mag};}
    else {d_log("Divide by zero in vector3", l_warning); void(0);}
}

float dot3(const vector3& v, const vector3& u)
{
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

vector3 cross(const vector3& v, const vector3& u)
{
    return {v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x};
}

vector4::vector4(const float& p_x, const float& p_y, const float& p_z, const float& p_w)
	:
	x(p_x), y(p_y), z(p_z), w(p_w)
{}

vector4::vector4(const float&& p_x, const float&& p_y, const float&& p_z, const float&& p_w)
	:
	x(p_x), y(p_y), z(p_z), w(p_w)
{}

vector4 vector4::operator+(const vector4& other) const {return {x + other.x, y + other.y, z + other.z, w + other.w};}

vector4 vector4::operator-(const vector4& other) const {return {x - other.x, y - other.y, z - other.z, w - other.w};}

vector4	vector4::operator*(const float& scalar) const{
	return {scalar * x, scalar * y, scalar * z, scalar * w};
}

vector4 vector4::operator/(const float& scalar) const{
	return {scalar / x, scalar / y, scalar / z, scalar / w};
}

float vector4::magnitude_squared() const {return x * x + y * y + z * z + w * w;}
float vector4::magnitude() const {return std::sqrt(x * x + y * y + z * z + w * w);}

vector4 vector4::normalized() const {
	float mag = this->magnitude();
	if (!mag == 0)
		return {x / mag, y / mag, z / mag, w / mag};
	else
		{d_log("Divide by zero in vector4", l_warning); void(0);}
}

vector4 vector4::operator-() const {return {-x, -y, -z, -w};}

bool vector4::operator==(const vector4& other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}
bool vector4::operator!=(const vector4& other) const {
	return x != other.x || y != other.y || z != other.z || w != other.w;
}
void vector4::operator+=(const vector4& other) {
	x += other.x; y += other.y; z += other.z; w += other.w;
}
void vector4::operator/=(const float& scalar) {
	if (scalar != 0)
		{x /= scalar; y /= scalar; z /= scalar; w /= scalar;}
	else
		{d_log("Divide by zero in vector4", l_warning); void(0);}
}

float dot4(const vector4& v, const vector4& u) {
	return v.x * u.x + v.y * u.y, v.z * u.z + v.w * u.w;
}

matrix4x4::matrix4x4(const vector4& p_c1, const vector4& p_c2, const vector4& p_c3, const vector4& p_c4)
	:
	c1(p_c1), c2(p_c2), c3(p_c3), c4(p_c4)
{}

matrix4x4 matrix4x4::transpose() const {
	return {{c1.x, c2.x, c3.x, c4.x}, {c1.y, c2.y, c3.y, c4.y}, {c1.z, c2.z, c3.z, c4.z}, {c1.w, c2.w, c3.w, c4.w}};
}
