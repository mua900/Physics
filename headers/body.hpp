#pragma once

#include <shape_inherit.hpp>
#include <vector.hpp>

class body
{
public:
    shape body_shape;
    body(const body& other);
    body& operator=(const body& other);
    virtual ~body();

    bool create_and_check_bounding_box();
private:
    body();
};

class dynamic_body : public body
{
public:
    vector2 position;
    vector2 velocity;
    vector2 acceleration;

    void move(const float& dt);
private:
};

class static_body : public body
{
public:
    vector2 position;
private:
};
