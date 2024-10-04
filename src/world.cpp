#include <world.hpp>

void world::start()
{
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();
    for (auto& dynamic_body : m_dynamic_bodies)
    {
    	// there should be a better way
		if (dynamic_body.position.x > maxX)
			maxX = dynamic_body.position.x;
		else if (dynamic_body.position.x < minX)
			minX = dynamic_body.position.x;
		if (dynamic_body.position.y > maxY)
			maxY = dynamic_body.position.y;
		else if (dynamic_body.position.y < minY)
			minY = dynamic_body.position.y;
	}
	maxX = std::fabs(maxX);
	minX = std::fabs(minX);
	maxY = std::fabs(maxY);
	minY = std::fabs(minY);

	// init the bvh's width and height
	if (maxX > minX)
		this->m_world_width = maxX + WORLD_BUFFER;
	else
		this->m_world_width = minX + WORLD_BUFFER;
	if (maxY > minY)
		this->m_world_height = maxY + WORLD_BUFFER;
	else
		this->m_world_height = minY + WORLD_BUFFER;
}

void world::update(const float& dt)
{
   for (auto& dynamic_body : m_dynamic_bodies)
    {
    	dynamic_body.move(dt);
    }
    broad_phase();
    resolve_collisions();
}

void world::init_partitions()
{
    std::vector<vector2> positions;
    positions.reserve(m_object_count);

    for (auto & m_dynamic_body : m_dynamic_bodies)
        positions.emplace_back(m_dynamic_body.position);
    for (auto & m_static_body : m_static_bodies)
        positions.emplace_back(m_static_body.position);

    bvh_tree world_bvh;
    world_bvh.construct(5, m_world_width, m_world_height, positions);
}

void world::update_partitions()
{

}

void world::broad_phase()
{

}

void world::resolve_collisions()
{

}
