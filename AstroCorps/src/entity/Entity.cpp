#include "Entity.h"
#include "..\managers\XMLManager.h"

#include "..\main\Application.h"

Entity::Entity(const char* filepath) {
	// load entity into component vector
	XML::load_entity(this, filepath);
}

Entity::~Entity() {
	// free components
	for (auto i = m_components.begin(); i != m_components.end(); i++)
		delete i->second;
}

void Entity::update(const sf::Time& delta_time) {
	for (auto i = m_components.begin(); i != m_components.end(); i++) {
		Component::Flag f =	i->second->update(delta_time);
		if (f == Component::UPDATE_POS) {
			float x_pos = m_transform->get_x() + m_transform->get_x_offset();
			float y_pos = m_transform->get_y() + m_transform->get_y_offset();
			x_pos *= Application::get_scaled_tile_size();
			y_pos *= Application::get_scaled_tile_size();
			m_fx_base->get_sprite().setPosition(x_pos, y_pos);
		}
	}
		
}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_fx_base->get_sprite());
}