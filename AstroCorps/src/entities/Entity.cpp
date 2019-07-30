#include "Entity.h"


Entity::Entity(unsigned int entity_size, unsigned int tile_x, unsigned int tile_y)
	: m_entity_size(entity_size), m_tile_x(tile_x), m_tile_y(tile_y) {}

Entity::~Entity() {}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}