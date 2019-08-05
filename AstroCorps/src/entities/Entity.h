#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

#include "..\interfaces\Updatable.h"

class Entity : public Updatable {
private:
	void move(int hor, int vert, float move_time);
protected:
	//sprite
	sf::Sprite m_sprite;
	float scale;

	// size to be rendered on screen
	unsigned int m_entity_size;

	// current x & y location
	unsigned int m_tile_x;
	unsigned int m_tile_y;

	// varibles dealing with movement
	bool m_moving;
	float m_move_time;
	sf::Time m_elap_time;

	unsigned int m_final_tile_x;
	unsigned int m_final_tile_y;
public:
	/* Constructors & Destructor */
	Entity(unsigned int entity_size, unsigned int tile_x, unsigned int tile_y);
	virtual ~Entity() = 0; // ensures entities are destructed correctly

	/* Functions */
	void draw(sf::RenderWindow& window);

	/* To move the entity note these don't check if
	   the move is valid */
	void move_horizontally(bool left, float move_time);
	void move_vertically(bool up, float move_time);

	/* Will return true if the entity shares the x, y
	   value passed into the functions or is in between
	   this tile and another */
	bool occupies(unsigned int tile_x, unsigned int tile_y);

	/* Override of update function */
	void update(const sf::Time& delta_time) override;
};

#endif