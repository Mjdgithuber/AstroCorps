#include "Entity.h"
#include <iostream>


Entity::Entity(unsigned int entity_size, unsigned int tile_x, unsigned int tile_y)
	: m_entity_size(entity_size), m_tile_x(tile_x), m_tile_y(tile_y), m_moving(false) {
	m_sprite.setPosition(entity_size * tile_x, entity_size * tile_y);
}

Entity::~Entity() {}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Entity::move(int hor, int vert, float move_time) {
	if (!m_moving) {
		m_moving = true;
		m_move_time = move_time;
		m_final_tile_x = m_tile_x + hor;
		m_final_tile_y = m_tile_y + vert;
		m_elap_time = sf::Time(); // reset time
		std::cout << "Time: " << m_elap_time.asSeconds() << "\n";
	}
}

void Entity::move_horizontally(bool left, float move_time) {
	move((left ? -1 : 1), 0, move_time);
}

void Entity::move_vertically(bool up, float move_time) {
	move(0, (up ? -1 : 1), move_time);
}

bool Entity::occupies(unsigned int tile_x, unsigned int tile_y) {
	if ((m_tile_x == tile_x) && (m_tile_y == tile_y))
		return true;

	if (m_moving)
		return (m_final_tile_x == tile_x) && (m_final_tile_y == tile_y);

	return false;
}

void Entity::update(const sf::Time& delta_time) {
	if (m_moving) {
		m_elap_time += delta_time;
		float percent = m_elap_time.asSeconds() / m_move_time;
		std::cout << percent << "\n";
		percent = percent > 1.f ? 1.f : percent; // snap to 100%

		float x_off = (m_final_tile_x - m_tile_x) * percent;
		float y_off = (m_final_tile_y - m_tile_y) * percent;

		m_sprite.setPosition((int)(m_entity_size * (m_tile_x + x_off)),
			(int)(m_entity_size * (m_tile_y + y_off)));
		if (percent >= 1.f) {
			std::cout << "Yeet\n";
			m_move_time = 0;
			m_moving = false;
			m_elap_time = sf::Time(); // reset time
		}
	}
}