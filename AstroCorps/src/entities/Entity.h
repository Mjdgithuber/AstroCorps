#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

#include "..\interfaces\Updatable.h"

class Entity : public Updatable {
private:
	void calculate_movement(const sf::Time& delta_time);
protected:
	//sprite
	sf::Sprite m_sprite;
	float scale;

	// size to be rendered on screen
	unsigned int m_entity_size;

	// current x & y location
	float m_tile_x;
	float m_tile_y;

	// varibles dealing with movement
	float m_acceleration;
	float m_max_speed;
	float m_speed;
	bool m_moving_hor;
	bool m_moving_ver;
	bool m_hor_movement;
	bool m_ver_movement;
public:
	/* Constructors & Destructor */
	Entity(unsigned int entity_size, float tile_x, float tile_y, float speed = 0.0f);
	virtual ~Entity() = 0; // ensures entities are destructed correctly

	/* Functions */
	void draw(sf::RenderWindow& window);

	/* To move the entity note these don't check if
	   the move is valid */
	void set_horizontal_movement(bool moving, bool right = true);
	void set_vertical_movement(bool moving, bool down = true);

	/* Will return true if the entity shares the x, y
	   value passed into the functions or is in between
	   this tile and another */
	bool occupies(unsigned int tile_x, unsigned int tile_y);

	/* Override of update function */
	void update(const sf::Time& delta_time) override;

	sf::Vector2f get_center() const;
};

#endif