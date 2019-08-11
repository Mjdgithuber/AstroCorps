#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <map>
#include <vector>
#include <typeindex>

#include "managers\XMLManager.h"
#include "components\Component.h"
#include "components\GraphicalBase.h"
#include "components\Movable.h"

class Entity {
private:
	/* every entity must contain graphical and tranform
	   component, or a component that extends it */
	GraphicalBase* m_fx_base = nullptr;
	Transform* m_transform = nullptr;

	/* The map is for location of elements, vector
	   is for Component* storage */
	std::map<std::type_index, unsigned int> m_component_indices;
	std::vector<Component*> m_components;

	bool add_component(Component* comp);
public:
	Entity(const char* filepath);
	~Entity();

	void update(const sf::Time& delta_time);
	void draw(sf::RenderWindow& window);

	template <typename T>
	int get_component_index();

	template <typename T>
	T* get_component(unsigned int index);

	// allow load_entity to access private varibles
	friend bool XML::load_entity(Entity* entity, const char* filepath);
};

template <typename T>
int Entity::get_component_index() {
	auto it = m_component_indices.find(std::type_index(typeid(T)));
	if (it != m_component_indices.end())
		return (signed)(it->second);
	return -1;
}

template <typename T>
T* Entity::get_component(unsigned int index) {
	return dynamic_cast<T*>(m_components[index]);
}

#endif