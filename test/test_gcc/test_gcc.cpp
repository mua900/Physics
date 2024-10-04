#include <cmath>
#include <cstddef>
#include <vector>

#include <vector.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <shape_inherit.hpp>
#include <collision.hpp>

#include <iostream>

int main()
{
	line_segment test({1,0}, {0,1});
	std::vector<vector2> vert;
	vert.push_back({2,0}); vert.push_back({3,1}); vert.push_back({-2,4}); vert.push_back({2,8});
	polygon p(vert);
	rectangle_i r({2, 2}, 10, 20, 0);

	for (size_t i = 0; i < 10; i++)
	{
		if (i%2 == 0)
			vert.emplace_back(vector2(i - std::cos(i), i - std::sin(i)));
		else
			vert.push_back({i - std::cos(i), i - std::sin(i)});
	}

	return 0;
}
