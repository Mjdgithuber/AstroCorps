#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

#include "..\interfaces\Updatable.h"

class Entity : public Updatable {
protected:
	sf::Sprite m_sprite;

	unsigned int m_entity_size;

	unsigned int m_tile_x;
	unsigned int m_tile_y;
public:
	/* Constructors & Destructor */
	Entity(unsigned int entity_size, unsigned int tile_x, unsigned int tile_y);
	virtual ~Entity();

	/* Functions */
	void draw(sf::RenderWindow& window);
};

#endif