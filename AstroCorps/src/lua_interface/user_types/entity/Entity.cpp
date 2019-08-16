#include "Entity.h"

Entity::Entity(int x, int y, int width, int height) 
	: m_x(x), m_y(y), m_width(width), m_height(height) {}

void Entity::update(const sf::Time& delta_time) {
	// needs to be finsihed
}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

int Entity::get_x() const {
	return m_x;
}

int Entity::get_y() const {
	return m_y;
}