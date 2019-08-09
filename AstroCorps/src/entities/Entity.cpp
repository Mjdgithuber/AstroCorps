#include <iostream>
#include <cmath>

#include "..\main\Application.h"
#include "Entity.h"

Entity::Entity(float tile_x, float tile_y, unsigned int width, unsigned int height)
	: m_tile_x(tile_x), m_tile_y(tile_y), m_size(width, height) {
	// sets position based on x & y location and tile size
	m_sprite.setPosition(Application::get_scaled_tile_size() * tile_x, Application::get_scaled_tile_size() * tile_y);
}

Entity::~Entity() {}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

sf::Vector2f Entity::get_center() const {
	unsigned int tile_size = Application::get_scaled_tile_size();
	unsigned int width = m_size.x * tile_size;
	unsigned int height = m_size.y * tile_size;

	// using round to ensure that position is always a whole number
	float x_cen = std::round(m_sprite.getPosition().x + width / 2);
	float y_cen = std::round(m_sprite.getPosition().y + height / 2);

	return sf::Vector2f(x_cen, y_cen);
}