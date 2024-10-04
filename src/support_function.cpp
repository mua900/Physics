#include <utils.hpp>
#include <support_function.hpp>
#include <cstddef>
#include <limits>

const vector2& support_function(const polygon& polygon, const vector2& direction)
{
    // we assume the points on the polygon are sorted properly it should be sorted in the polygon constructer
    size_t index = 0;
    float max_dot = dot2(polygon.vertices.at(0), direction);
    float curr_dot = dot2(polygon.vertices.at(1), direction);
    bool left = max_dot < curr_dot;

    if (left)
    {
        index = 1;
        for (size_t i = 2; i < polygon.vertices.size(); i++)
        {
            curr_dot = dot2(polygon.vertices.at(i), direction);
            if (max_dot < curr_dot)
            {
                max_dot = curr_dot;
                index = i;
            }
        }
    }
    else
    {
        for (size_t i = -1; - polygon.vertices.size() - 2 < i; i--)
        {
            curr_dot = dot2(polygon.vertices.at(i), direction);
            if (max_dot < curr_dot)
            {
                max_dot = curr_dot;
                index = i;
            }
        }
    }

    return polygon.vertices.at(index);
}

std::array<vector2, 2> support_function_two(const polygon& polygon, const vector2& direction)
{
    float max_first = dot2(direction, polygon.vertices.at(0));
    float max_second = dot2(direction, polygon.vertices.at(1));

    size_t max_first_index;
    size_t max_second_index;

    if (max_first < max_second) // if the polygon vertices are ordered this also means the way to search is to the counter clockwise direction (see polygon::order)
    {
        utils::swap(max_first, max_second);
        max_first_index = 1;
        max_second_index = 0;
        float curr_dot;
        for (size_t i = 2; i < polygon.vertices.size(); i++)
        {
            curr_dot = dot2(direction, polygon.vertices.at(i));
            if (max_first < curr_dot)
            {
                max_second = max_first;
                max_first = curr_dot;
                max_second_index = max_first_index;
                max_first_index = i;
            }
            else if (max_second < curr_dot)
            {
                max_second = curr_dot;
                max_second_index = i;
                break;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        max_first_index = 0;
        max_second_index = 1;
        float curr_dot;
        for (size_t i = -1; - polygon.vertices.size() < i; i--)
        {
            curr_dot = dot2(direction, polygon.vertices.at(i));
            if (max_first < curr_dot)
            {
                max_second = max_first;
                max_first = curr_dot;
                max_second_index = max_first_index;
                max_first_index = i;
            }
            else if (max_second < curr_dot)
            {
                max_second = curr_dot;
                max_second_index = i;
                break;
            }
            else
            {
                break;
            }
        }
    }
    return {polygon.vertices.at(max_first_index), polygon.vertices.at(max_second_index)};
}
