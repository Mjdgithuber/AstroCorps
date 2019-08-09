#include <iostream>
#include <cmath>

#include "..\main\Application.h"
#include "Entity.h"

Entity::Entity(float tile_x, float tile_y, unsigned int width, unsigned int height)
	: m_tile_x(tile_x), m_tile_y(tile_y), m_size(width, height) {
	// sets position based on x & y location and tile size
	m_sprite.setPosition(Application::get_scaled_tile_size() * tile_x, Application::get_scaled_tile_size() * tile_y);
}

/* Must give a definition for the destructor even though
   it is pure virtual */
Entity::~Entity() {}

/* Draw entity sprite to the window */
void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

/* Returns the absolute center of the sprite */
sf::Vector2f Entity::get_center() const {
	// find width and height of entity
	unsigned int tile_size = Application::get_scaled_tile_size();
	unsigned int width = m_size.x * tile_size;
	unsigned int height = m_size.y * tile_size;

	// using round to ensure that position is always a whole number
	float x_cen = std::round(m_sprite.getPosition().x + width / 2);
	float y_cen = std::round(m_sprite.getPosition().y + height / 2);

	// return center
	return sf::Vector2f(x_cen, y_cen);
}