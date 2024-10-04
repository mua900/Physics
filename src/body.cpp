#include <body.hpp>
#include <verlet.hpp>

void dynamic_body::move(const float& dt)
{
    verlet::update(this->position, this->velocity, this->acceleration, dt);
}

body::body(const body &other) = default;

body::~body() = default;

body& body::operator=(const body &other) = default;

body::body() = default;

bool body::create_and_check_bounding_box()
{
    // TODO
    return false;
}
