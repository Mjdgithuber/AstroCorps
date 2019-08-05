#include "Entity.h"
#include <iostream>

Entity::Entity(unsigned int entity_size, float tile_x, float tile_y, float speed)
	: m_entity_size(entity_size), m_tile_x(tile_x), m_tile_y(tile_y), m_acceleration(25 * speed),
	m_max_speed(speed), m_speed(0.f), m_moving_hor(0), m_moving_ver(0), m_hor_movement(0), m_ver_movement(0) {
	m_sprite.setPosition(entity_size * tile_x, entity_size * tile_y);
}

Entity::~Entity() {}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Entity::calculate_movement(const sf::Time& delta_time) {
	if (m_moving_hor || m_moving_ver) {
		// add acceleration to speed
		m_speed += m_acceleration * delta_time.asSeconds();
		m_speed = m_speed > m_max_speed ? m_max_speed : m_speed;

		float mov_x, mov_y;
		mov_x = mov_y = m_speed * delta_time.asSeconds();

		mov_x *= m_moving_hor * (m_hor_movement ? 1.f : -1.f) * (m_moving_ver ? 0.707106781f : 1.f);
		mov_y *= m_moving_ver * (m_ver_movement ? 1.f : -1.f) * (m_moving_hor ? 0.707106781f : 1.f);

		m_tile_x += mov_x;
		m_tile_y += mov_y;

		m_sprite.setPosition((int) (m_tile_x * m_entity_size), (int) (m_tile_y * m_entity_size));
		//m_sprite.move(mov_x, mov_y);
	} else {
		//m_speed -= m_acceleration * delta_time.asSeconds();
		m_speed = 0;
	}

	//std::cout << "Speed: " << m_speed << "\n";
}

void Entity::set_horizontal_movement(bool moving, bool right) {
	m_moving_hor = moving;
	m_hor_movement = right;
}

void Entity::set_vertical_movement(bool moving, bool down) {
	m_moving_ver = moving;
	m_ver_movement = down;
}

void Entity::update(const sf::Time& delta_time) {
	calculate_movement(delta_time);
}

sf::Vector2f Entity::get_center() const {
	return sf::Vector2f((int) (m_sprite.getPosition().x + m_entity_size / 2),
		                (int) (m_sprite.getPosition().y + m_entity_size / 2));
}