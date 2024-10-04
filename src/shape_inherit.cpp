#include <shape_inherit.hpp>

// these are here because of GCC, see TODO find the link (link)
shape::shape() = default;
shape::shape(const shape& other) = default;
shape::~shape() = default;
shape shape::operator=(const shape& other){}
bool shape::contains(const vector2& point) const {}

float shape::area_radius() const
{
    d_log("Unexpected reach to base class method shape.", l_level::l_warning);
    return 0;
}

circle_i::circle_i(const vector2& pos, const float& radius)
    :
    radius(radius)
{
    position = pos;
}

bool circle_i::contains(const vector2& point) const
{
    return (position - point).magnitude_squared() < radius * radius;
}

float circle_i::area_radius() const
{
    return radius;
}

bounding_rect circle_i::bounding_rectangle() const override {
	return {position, radius + bounding_volume_extra, radius + bounding_volume_extra};
}

triangle_i::triangle_i(const std::array<vector2, 3>& p_vertices)
    :
    vertices(p_vertices)
{
    this->position = (vertices.at(0) + vertices.at(1) + vertices.at(2)) / 3;
}

bool triangle_i::contains(const vector2& point) const
{
    return matrix2x2(vertices.at(1) - vertices.at(0), point - vertices.at(0)).determinant() < 0 && matrix2x2(vertices.at(2) - vertices.at(1), point - vertices.at(1)).determinant() < 0 && matrix2x2(vertices.at(0) - vertices.at(2), point - vertices.at(2)).determinant() < 0;
}

float triangle_i::area_radius() const
{
    return std::max(std::max(vertices.at(0).magnitude(), vertices.at(1).magnitude()), vertices.at(2).magnitude());
}

rectangle_i::rectangle_i(const vector2& pos, const float& width, const float& height, const float& rotation_in_radians)
    :
    width(width), height(height), rotation_in_radians(rotation_in_radians)
{
    position = pos;
}

bool rectangle_i::contains(const vector2& point) const
{
    float cos_of_angle = std::cos(rotation_in_radians);
    float sin_of_angle = std::sin(rotation_in_radians);

    // rotation_in_radians is in accordance to the trigonometry
    // top_mid and right_mid represent points their name would suggest if the rotation was 0
    vector2 top_mid(sin_of_angle * width, - cos_of_angle * height);
    vector2 right_mid(cos_of_angle * width, sin_of_angle * height);

    return height < dot2(top_mid, point)
         && width < dot2(right_mid, point);
}

bounding_rect triangle_i::bounding_rectangle() const override {
	// maybe use something else than the regular std for this kind of thing
	float min_x = std::min(std::min(vertices.at(0).x, vertices.at(1).x), vertices.at(2).x);
	float max_x = std::max(std::max(vertices.at(0).x, vertices.at(1).x), vertices.at(2).x);
	float min_y = std::min(std::min(vertices.at(0).y, vertices.at(1).y), vertices.at(2).y);
	float max_y = std::max(std::max(vertices.at(0).y, vertices.at(1).y), vertices.at(2).y);

	return {this->position, max_x - min_x + bounding_volume_extra, max_y - min_y + bounding_volume_extra};
}

float rectangle_i::area_radius() const
{
    return std::sqrt(width * width + height * height);
}

rectangle_v_i::rectangle_v_i(const vector2& pos, const float& width, const float& height, const float& rot_in_radians)
{
    position = pos;
    float x = std::cos(rot_in_radians) * width;
    float y = std::sin(rot_in_radians) * height;
    vertices[0] = vector2(x, y);
    vertices[1] = vector2(- x, y);
    vertices[2] = vector2(- x, - y);
    vertices[3] = vector2(x, - y);
}

bool rectangle_v_i::contains(const vector2& point) const
{
    vector2 AB_mid((vertices[0] + vertices[1]) / 2);
    vector2 AD_mid((vertices[0] + vertices[3]) / 2);

    float ab_dot = dot2(point, AB_mid);
    float ad_dot = dot2(point, AD_mid);
    return ab_dot * ab_dot < (AB_mid - position).magnitude_squared()
        && ad_dot * ad_dot < (AD_mid - position).magnitude_squared();
}

float rectangle_v_i::area_radius() const
{
    return vertices.at(0).magnitude();
}

bounding_rect rectangle_i::bounding_rectangle() const override {
	// TODO
	return {{0,0}, 0, 0};
}

polygon_i::polygon_i(const std::vector<vector2>& vertices)
    :
    vertices(vertices)
{
    position = vector2(0,0);
    for (vector2 vertex : vertices)
    {
        position += vertex;
    }
    position /= (uint16_t)vertices.size();
}

bool polygon_i::contains(const vector2& point) const
{
    //TODO
    return false;
}

float polygon_i::area_radius() const
{
    float max_mag_squared = vertices.at(0).magnitude_squared();
    for (size_t i = 1; i < vertices.size(); i++)
    {
        float curr = vertices.at(i).magnitude_squared();
        if (max_mag_squared < curr)
            max_mag_squared = curr;
    }
    return std::sqrt(max_mag_squared);
}
