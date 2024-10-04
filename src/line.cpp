#include <line.hpp>
#include <utils.hpp>
#include <utility>

line::line(vector2& point1, vector2& point2)
{
    param_vec = (point2 - point1).normalized();
    vector2 line_perp = param_vec.perpendicular();
    float line_perp_length = dot2(line_perp, point1);
    if (line_perp_length < 0)
    {
        line_perp = -line_perp;
        line_perp_length = -line_perp_length;
    }
    start_vec = line_perp * line_perp_length;
}

bool line::on_line(const vector2& point) const
{
    // param_vec * t + start_vec = point
    // t = (point - start_vec) / param_vec
    float t_x = (point.x - start_vec.x) / param_vec.x;
    float t_y = (point.y - start_vec.y) / param_vec.y;
    return utils::float_equality(t_x, t_y);
}

line_segment::line_segment() = default;

line_segment::line_segment(const vector2& p_point0, const vector2& p_point1)
{
    vector2 p0 = p_point0.normalized();
    vector2 p1 = p_point1.normalized();

    p0.x = std::fabs(p0.x); p0.y = std::fabs(p0.y); p1.x = std::fabs(p1.x); p1.y = std::fabs(p1.y);

    if (!utils::float_equality(p0.x, p1.x))
    {
        if (p0.x < p1.x)
        {
            point0 = p_point0;
            point1 = p_point1;
        }
        else
        {
            point0 = p_point1;
            point1 = p_point0;
        }
    }
    else
    {
        if (p_point0.magnitude_squared() > p_point1.magnitude_squared())
        {
            point0 = p_point1;
            point1 = p_point0;
        }
        else
        {
            point0 = p_point0;
            point1 = p_point1;
        }
    }
}

line_segment::line_segment(const std::array<vector2, 2>& points)
{
    vector2 p0 = points.at(0).normalized();
    vector2 p1 = points.at(1).normalized();

    p0.x = std::fabs(p0.x); p0.y = std::fabs(p0.y); p1.x = std::fabs(p1.x); p1.y = std::fabs(p1.y);

    if (!utils::float_equality(p0.x, p1.x))
    {
        if (p0.x < p1.x)
        {
            point0 = points.at(0);
            point1 = points.at(1);
        }
        else
        {
            point0 = points.at(1);
            point1 = points.at(0);
        }
    }
    else
    {
        if (points.at(0).magnitude_squared() > points.at(1).magnitude_squared())
        {
            point0 = points.at(1);
            point1 = points.at(0);
        }
        else
        {
            point0 = points.at(0);
            point1 = points.at(1);
        }
    }
}

bool line_segment::on_line_segment(const vector2& point)
{
    if (utils::float_equality((point.y - point0.y) / (point.x - point0.x), (point1.y - point0.y) / (point1.x - point0.x)))
    {
        vector2 point0_to_point(point.x - point0.x, point.y - point0.y); // point - point0
        vector2 point0_to_point1(point1.x - point0.x, point1.y - point0.y); // point1 - point0
        float lambda = dot2(point0_to_point1, point0_to_point) / point0_to_point1.magnitude_squared(); // lambda = <p0_p, p0_p1> / <p0_p1, p0_p1>
        return lambda < 1 && lambda > 0;
    }
    else
    {
        return false;
    }
}

vector2 line_segment::facing_normal(const vector2& point) const
{
    // maybe could be done with cross product also but this is fine I think

    vector2 perp = (point1 - point0).perpendicular();

    if (dot2(perp, point - this->mid_point()) < 0)
        return -perp;
    else
        return perp;
}

// maybe inline
vector2 line_segment::mid_point() const
{
    return vector2(point0.x + point1.x, point0.y + point1.y) / 2;
}

vector2 line_segment::projection(const vector2 &point) const
{
    float lambda = dot2(point - point0, point1 - point0) / (point1 - point0).magnitude_squared();
    return point0 + point1 * lambda;
}


line_segment_t::line_segment_t(line  base_line, const float& t0, const float& t1)
    :
    base_line(std::move(base_line)), t0(t0), t1(t1)
{}
