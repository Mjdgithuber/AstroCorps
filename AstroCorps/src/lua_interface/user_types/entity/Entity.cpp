#include "Entity.h"
#include "engine/common.h"
#include "managers/TextureManager.h"

Entity::Entity(const std::string& name, unsigned int entry_no, int x, int y, int width, int height)
	: m_sprite(), m_name(name), m_entry_no(entry_no), m_x(x), m_y(y), m_width(width), m_height(height) {
	
	// Need to remove, just for testing
	m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
	m_sprite.setScale(Application::get_scale(), Application::get_scale());
	m_sprite.setPosition(Application::get_scaled_tile_size() * x, Application::get_scaled_tile_size() * y);
}

Entity::~Entity() {
	LOG_DEBUG("Destructor for '{0}' called!\n", m_name);
}

void Entity::update(const sf::Time& delta_time) {
	// needs to be done
}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

const std::string& Entity::get_name() const {
	return m_name;
}

int Entity::get_x() const {
	return m_x;
}

int Entity::get_y() const {
	return m_y;
}