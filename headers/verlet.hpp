#pragma once

#include <vector.hpp>

namespace verlet
{
    void update(vector2& position, vector2& velocity, vector2& acceleration, const float& dt);
}
