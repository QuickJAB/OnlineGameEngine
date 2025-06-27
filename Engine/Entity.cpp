#include "Entity.h"

Entity::Entity(float in_x, float in_y, float in_width, float in_height)
{
	m_rect = { in_x, in_y, in_width, in_height };
}

void Entity::update(float in_dt)
{
	m_rect.x += (m_speed * m_dir[0] * in_dt);
	m_rect.y += (m_speed * m_dir[1] * in_dt);
}