#include <verlet.hpp>

namespace verlet
{
    void update(vector2& position, vector2& velocity, vector2& acceleration, const float& dt)
    {
        position = position + velocity * dt + acceleration * (0.5 * dt * dt);
    }
}
