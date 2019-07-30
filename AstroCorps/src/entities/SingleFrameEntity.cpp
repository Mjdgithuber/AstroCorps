#include "SingleFrameEntity.h"

#include "..\managers\TextureManager.h"

SingleFrameEntity::SingleFrameEntity(unsigned int entity_size, unsigned int tile_x,
	unsigned int tile_y, const std::string& filename) 
	: MovableEntity(entity_size, tile_x, tile_y) {
	// load texture
	m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
	float scale = ((float)entity_size) / m_sprite.getTexture()->getSize().x;
	m_sprite.setScale(sf::Vector2f(2, 2));
}