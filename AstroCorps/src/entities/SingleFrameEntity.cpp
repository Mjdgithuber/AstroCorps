#include "SingleFrameEntity.h"

#include "..\managers\TextureManager.h"

SingleFrameEntity::SingleFrameEntity(unsigned int entity_size, float tile_x,
	float tile_y, float speed)
	: Entity(entity_size, tile_x, tile_y, speed) {
	// load texture
	m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
	scale = ((float)entity_size) / m_sprite.getTexture()->getSize().x;
	m_sprite.setScale(sf::Vector2f(scale, scale));
}