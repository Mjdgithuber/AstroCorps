#include <iostream>

#include "OldEntity.h"
#include "Core.h"

bool OldEntity::add_component(Component* comp) {
	// type id of component to be added
	std::type_index component_id(typeid(*comp));

	/* check if a component of the same 
	   type was already added */
	for (unsigned int i = 0; i < m_components.size(); i++) {
		// check if type of component is the same
		//LOG_WARN("Component With Base \'{0}\' Already Added\nIgnoring", comp->get_base_name());
		if (component_id == std::type_index(typeid(*m_components[i]))) {
			LOG_WARN("Component \'{0}\' Already Added To \'{1}\'. Ignoring!", comp->get_name(), m_name);
			//std::cout << "Component Already Added!\n";
			//std::cout << "Adding Base: " << comp->get_base_name() << " " << m_components[i]->get_base_name() << "\n";
			return false;
		}
		// check if type is derivative of already added comp
		if (comp->get_base_name() == m_components[i]->get_base_name()) {
			LOG_WARN("A Component With Base \'{0}\' Was Already Added To \'{1}\'. Ignoring!", comp->get_base_name(), m_name);
			//std::cout << "Component with same base was already added!\n";
			return false;
		}
	}
	
	// add component to entity
	m_component_indices[component_id] = m_components.size();
	m_components.push_back(comp); // add graphucal base

	if (comp->get_base_name() == "GraphicalBase")
		m_fx_base = dynamic_cast<GraphicalBase*>(comp);
	else if (comp->get_base_name() == "Transform")
		m_transform = dynamic_cast<Transform*>(comp);


	LOG_INFO("Added Base {0}", comp->get_base_name());

	return true;
}

const std::string& OldEntity::get_name() {
	return m_name;
}

OldEntity::OldEntity(const char* filepath)
	: m_fx_base(nullptr), m_transform(nullptr) {
	// load entity into component vector
	XML::load_entity(this, filepath);

	update_sprite_position();
}

OldEntity::~OldEntity() {
	// free components
	for (unsigned int i = 0; i < m_components.size(); i++)
		delete m_components[i];
}

void OldEntity::update(const sf::Time& delta_time) {
	for (unsigned int i = 0; i < m_components.size(); i++) {
		Component::Flag f = m_components[i]->update(delta_time);
		if (f == Component::UPDATE_POS)
			update_sprite_position();
	}		
}

void OldEntity::update_sprite_position() {
	float x_pos = m_transform->get_x() + m_transform->get_x_offset();
	float y_pos = m_transform->get_y() + m_transform->get_y_offset();
	x_pos *= OldApplication::get_scaled_tile_size();
	y_pos *= OldApplication::get_scaled_tile_size();
	m_fx_base->get_sprite().setPosition(x_pos, y_pos);
}

void OldEntity::draw(sf::RenderWindow& window) {
	window.draw(m_fx_base->get_sprite());
}