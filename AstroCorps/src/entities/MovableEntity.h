#ifndef __MOVABLE__ENTITY__H__
#define __MOVABLE__ENTITY__H__

#include "Entity.h"

class MovableEntity : public Entity {
private:
	/* private helper functions */
	void move(int hor, int vert, float move_time);
protected:
	bool m_moving;
	float m_move_time;
	sf::Time m_elap_time;

	unsigned int m_final_tile_x;
	unsigned int m_final_tile_y;
public:
	MovableEntity(unsigned int entity_size, unsigned int tile_x, unsigned int tile_y);

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