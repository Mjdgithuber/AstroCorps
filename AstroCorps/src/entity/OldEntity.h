#ifndef __ENTITY__OLD__H__
#define __ENTITY__OLD__H__

#include <map>
#include <vector>
#include <typeindex>

#include "xml/parsers/EntityParser.h"
#include "components/Component.h"
#include "components/GraphicalBase.h"
#include "components/Movable.h"

class OldEntity {
private:
	std::string m_name;

	/* every entity must contain graphical and tranform
	   component, or a component that extends it */
	GraphicalBase* m_fx_base = nullptr;
	Transform* m_transform = nullptr;

	/* The map is for location of elements, vector
	   is for Component* storage */
	std::map<std::type_index, unsigned int> m_component_indices;
	std::vector<Component*> m_components;

	bool add_component(Component* comp);
	void update_sprite_position();
public:
	OldEntity(const char* filepath);
	~OldEntity();

	void update(const sf::Time& delta_time);
	void draw(sf::RenderWindow& window);

	template <typename T>
	T* get_component();

	const std::string& get_name();

	// allow load_entity to access private varibles
	friend bool XML::load_entity(OldEntity* entity, const char* filepath);
};

template <typename T>
T* OldEntity::get_component() {
	auto it = m_component_indices.find(std::type_index(typeid(T)));
	if (it != m_component_indices.end()) {
		return dynamic_cast<T*>(m_components[it->second]);
	}
	return nullptr;
}

#endif