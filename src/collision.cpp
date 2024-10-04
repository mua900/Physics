#include <collision.hpp>

bool aabb(const rectangle& rect1, const rectangle& rect2)
{
    // TODO turn back if we don't ensure rotation is modulo 2pi before calling the function
    assert(rect1.rotation_in_radians != 0 || rect2.rotation_in_radians != 0);

    const float r1_hh = rect1.height/2;
    const float r1_hw = rect1.width/2;
    const float r2_hh = rect2.height/2;
    const float r2_hw = rect2.width/2;

    return rect2.position.x - r2_hw < rect1.position.x + r1_hw && rect1.position.x - r1_hw < rect2.position.x + r2_hw && rect2.position.y - r2_hh < rect1.position.y + r1_hh && rect1.position.y - r1_hh < rect2.position.y + r2_hh;
}

static inline vector2 findMinkowskiPoint(const polygon& p1, const polygon& p2, vector2& direction)
{
    vector2 support_point1 = support_function(p1, direction);
    vector2 support_point2 = support_function(p2, - direction);
    return support_point1 - support_point2;
}

// terrible that we have to add this
static inline vector2 findMinkowskiPoint(const polygon& p1, const polygon& p2, vector2&& direction)
{
    vector2 support_point1 = support_function(p1, direction);
    vector2 support_point2 = support_function(p2, - direction);
    return support_point1 - support_point2;
}

bool gjk(const polygon& polygon1, const polygon& polygon2)
{
    // p2.center - p1.center
    vector2 first_dir(polygon2.center.x - polygon1.center.x, polygon2.center.y - polygon1.center.y);

    // we can construct a polygon out of this at the end, but we need to push and pop back points
    std::array<vector2, 3> simplex{};

    // minkowski difference polygon
    simplex[0] = findMinkowskiPoint(polygon1, polygon2, first_dir);
    vector2 second_dir = - simplex[0];
    vector2 second_point = findMinkowskiPoint(polygon1, polygon2, second_dir);

    if (check_point_passing_origin(simplex[0], second_point))
    {
        simplex[1] = second_point;
        // when the gjk_triangle_case function is called, and it finds a new valid point, it adds it to the simplex by itself
        if (gjk_line_case(simplex, polygon1, polygon2))
        {
            // the triangle_case function iteratively continues to search
            return gjk_triangle_case(simplex, polygon1, polygon2);
        }
        else
            return false;
    }
    else
        return false;
}

inline bool check_point_passing_origin(const vector2& anchor, const vector2& point)
{
    return dot2(anchor, point) < 0;
}

bool gjk_line_case(std::array<vector2, 3>& line_points, const polygon& p1, const polygon& p2)
{
    line_segment line(line_points[0], line_points[1]);
    vector2 new_support = findMinkowskiPoint(p1, p2, line.facing_normal(vector2(0, 0)));
    if (check_point_passing_origin(line.mid_point(), new_support))
    {
        line_points[2] = new_support;
        return true;
    }
    else
        return false;
}

bool gjk_triangle_case(std::array<vector2, 3> simplex, const polygon& p1, const polygon& p2)
{
    // A -> 2, B -> 1, C -> 0
    line_segment AB(simplex[2], simplex[1]);
    line_segment AC(simplex[2], simplex[0]);

    for (uint8_t i = 0; i < GJK_MAX_ITERATIONS; i++)
    {
        // AB
        vector2 AB_support = findMinkowskiPoint(p1, p2, AB.mid_point());
        vector2 AC_support = findMinkowskiPoint(p1, p2, AB.mid_point());
        if (check_point_passing_origin(AB.mid_point(), AB_support))
        {
            // walk
            simplex[0] = simplex[1];
            simplex[1] = simplex[2];
            simplex[2] = AB_support;
        }
        //AC
        else if (check_point_passing_origin(AC.mid_point(), AC_support))
        {
            simplex[1] = simplex[2];
            simplex[2] = AC_support;
        }
        else
        {
            return true;
        }
    }
    return false;
}

#define EPA_MAX_ITERATIONS 40

/// @brief Finds the minimal direction to push the objects detected to collide by the GJK and moves them apart.
/// @param simplex 
/// @param poly1 
/// @param poly2 
vector2 epa(const triangle& simplex, const polygon& poly1, const polygon& poly2)
{
    std::vector<vector2> polytope;
    polytope.reserve(7);

    line_segment side_to_search;

    std::array<utils::id_value_pair<float>, 3> mags{};

    mags[0].id = 0;
    mags[0].value = simplex.vertex1.magnitude_squared();
    mags[1].id = 1;
    mags[1].value = simplex.vertex2.magnitude_squared();
    mags[2].id = 2;
    mags[2].value = simplex.vertex3.magnitude_squared();

    uint16_t ind = 0;
	if (mags.at(0).value < mags.at(1).value)
		ind = 1;
	if (mags.at(ind).value < mags.at(2).value)
		ind = 2;
    
    switch(ind)
    {
        case 0:
            side_to_search = line_segment(simplex.vertex2, simplex.vertex3);
            polytope.push_back(simplex.vertex2);
            polytope.push_back(simplex.vertex3);
        case 1:
            side_to_search = line_segment(simplex.vertex1, simplex.vertex3);
            polytope.push_back(simplex.vertex1);
            polytope.push_back(simplex.vertex3);
        case 2:
            side_to_search = line_segment(simplex.vertex2, simplex.vertex3);
            polytope.push_back(simplex.vertex2);
            polytope.push_back(simplex.vertex3);
        default:
            d_log("Unexpected result", l_error);
    }

    vector2 new_support = findMinkowskiPoint(poly1, poly2, side_to_search.mid_point());

    if (v2_equals(new_support, side_to_search.point0) || v2_equals(new_support, side_to_search.point1))
        return side_to_search.projection({0,0});
    else
    {
        polytope.push_back(new_support);
        vector2 next{};
        for (uint8_t i = 0; i < EPA_MAX_ITERATIONS; i++)
        {
            vector2 line_seg_projection = line_segment(polytope.at(-2), polytope.at(-1)).projection({0,0});
            next = findMinkowskiPoint(poly1, poly2, line_seg_projection);
            if (v2_equals(next, new_support))
            {
                return line_seg_projection;
            }
            else
            {
                new_support = next;
                polytope.push_back(new_support);
            }
        }
    }
    return {0,0};
}
