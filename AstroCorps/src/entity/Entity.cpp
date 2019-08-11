#include <iostream>

#include "Entity.h"
#include "main\Application.h"

bool Entity::add_component(Component* comp) {
	// type id of component to be added
	std::type_index component_id(typeid(*comp));

	/* check if a component of the same 
	   type was already added */
	for (unsigned int i = 0; i < m_components.size(); i++) {
		// check if type of component is the same
		if (component_id == std::type_index(typeid(m_components[i]))) {
			std::cout << "Component Already Added!\n";
			std::cout << "Adding Base: " << comp->get_base_name() << " " << m_components[i]->get_base_name() << "\n";
			return false;
		}
		// check if type is derivative of already added comp
		if (comp->get_base_name() == m_components[i]->get_base_name()) {
			std::cout << "Component with same base was already added!\n";
			return false;
		}
	}

	// all good to add to the map & vector
	std::cout << "Id: " << " base: " << comp->get_base_name() << "\n";
	m_component_indices[component_id] = m_components.size();
	m_components.push_back(comp); // add graphucal base
}

Entity::Entity(const char* filepath)
	: m_fx_base(nullptr), m_transform(nullptr) {
	// load entity into component vector
	XML::load_entity(this, filepath);
}

Entity::~Entity() {
	// free components
	for (unsigned int i = 0; i < m_components.size(); i++)
		delete m_components[i];
}

void Entity::update(const sf::Time& delta_time) {
	for (unsigned int i = 0; i < m_components.size(); i++) {
		Component::Flag f = m_components[i]->update(delta_time);
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