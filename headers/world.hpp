#pragma once

#include <bvh.hpp>
#include <body.hpp>
#include <cstddef>
#include <vector>

#define WORLD_BUFFER 100

#define WORLD_WIDTH 1000
#define WORLD_HEIGHT 1000

class world
{
public:
    void start();
    void update(const float& dt);
private:

    void init_partitions();
    void update_partitions();
    void broad_phase();
    void resolve_collisions();

    std::vector<static_body> m_static_bodies{};
    std::vector<dynamic_body> m_dynamic_bodies{};
    size_t m_object_count = 0;
    float m_world_height = WORLD_HEIGHT;
    float m_world_width = WORLD_WIDTH;
};
