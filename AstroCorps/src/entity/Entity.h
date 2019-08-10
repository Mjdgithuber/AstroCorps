#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <map>
#include <typeindex>

#include "managers\XMLManager.h"
#include "components\Component.h"
#include "components\GraphicalBase.h"
#include "components\Movable.h"

class Entity {
private:
	GraphicalBase* m_fx_base = nullptr;
	Transform* m_transform = nullptr;

	std::map<std::type_index, Component*> m_components;

public:
	Entity(const char* filepath);
	~Entity();

	void update(const sf::Time& delta_time);
	void draw(sf::RenderWindow& window);

	template <typename T>
	T* get_component();

	// allow load_entity to access private varibles
	friend bool XML::load_entity(Entity* entity, const char* filepath);
};

template <typename T>
T* Entity::get_component() {
	auto it = m_components.find(std::type_index(typeid(T)));
	if (it != m_components.end()) {
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

#endif