#include <cmath>
#include <vector.hpp>
#include <shape.hpp>
#include <line.hpp>

triangle::triangle(const vector2& p_vertex1,const vector2& p_vertex2,const vector2& p_vertex3)
    :
    center((p_vertex1 + p_vertex2 + p_vertex3) / 3), vertex1(p_vertex1), vertex2(p_vertex2), vertex3(p_vertex3)
{
    if (v2_equals(p_vertex1, p_vertex2) || v2_equals(p_vertex1, p_vertex3) || v2_equals(p_vertex2, p_vertex3))
        d_log("Trying to construct a triangle out of the same points", l_warning);
}

triangle::triangle(const std::array<vector2, 3>& points)
    :
    center((points.at(0) + points.at(1) + points.at(2)) / 3),
    vertex1(points.at(0)),
    vertex2(points.at(1)),
    vertex3(points.at(2))
{
}

bool triangle::contains(const vector2& point) const
{
    return matrix2x2(point - vertex1, vertex2 - vertex1).determinant() < 0 && matrix2x2(point - vertex2, vertex3 - vertex2).determinant() < 0 && matrix2x2(point - vertex3, vertex1 - vertex3).determinant() < 0;
}

rectangle::rectangle(const vector2 &position, const float &w, const float &h, const float &rotation_in_radians)
    :
    position(position), width(w), height(h), rotation_in_radians(rotation_in_radians)
{}

bool rectangle::contains(const vector2& point) const
{
    vector2 point_local_to_rectangle(point.x - position.x, point.y - position.y);
    float cos_of_angle = std::cos(rotation_in_radians);
    float sin_of_angle = std::sin(rotation_in_radians);
    // rotation_in_radians is in accordance to the trigonometry
    // top_mid and right_mid represent points their name would suggest if the rotation was 0
    vector2 top_middle(height * cos_of_angle, height * sin_of_angle);
    vector2 right_middle(width * cos_of_angle, width * sin_of_angle);
    return height < std::fabs(dot2(point_local_to_rectangle, top_middle))
         && width < std::fabs(dot2(point_local_to_rectangle, right_middle));
}

polygon::polygon(const std::vector<vector2>& vertices)
    :
    vertices(vertices)
{
    center = vector2(0,0);
    for (const vector2& vertex : vertices)
    {
        center += vertex;
    }
    center /= static_cast<float>(vertices.size());
    order();
}

bool polygon::contains(const vector2& point)
{
    // TODO
    return false;
}

void polygon::order()
{
    std::sort(vertices.begin(), vertices.end(), [&](const  vector2& a, const vector2& b)->bool
    {
        bool a_y = a.y > 0;
        bool b_y = b.y > 0;
        if (a_y && b_y)
        {
            return a.x > b.x;
        }
        else
        {
            return a_y;
        }
    });
}

bool circle::contains(const vector2& point)
{
    vector2 point_minus_circle_center(point.x - position.x, point.y - position.y);
    return point_minus_circle_center.magnitude_squared() < radius * radius;
}
