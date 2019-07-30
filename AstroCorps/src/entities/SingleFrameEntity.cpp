#include "SingleFrameEntity.h"

SingleFrameEntity::SingleFrameEntity(unsigned int entity_size, unsigned int tile_x,
	unsigned int tile_y, const std::string& filename) 
	: MovableEntity(entity_size, tile_x, tile_y) {
	// load texture
	m_static_texture.loadFromFile(filename);
	m_sprite.setTexture(m_static_texture);
}