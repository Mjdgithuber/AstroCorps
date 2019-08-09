#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

#include "..\util\Util.h"
#include "..\interfaces\Updatable.h"

class Entity : public Updatable {
protected:
	//sprite
	sf::Sprite m_sprite;

	// current x & y location
	unsigned int m_tile_x;
	unsigned int m_tile_y;

	// size of entity in tiles
	Util::Point m_size;
public:
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Makes a new entity at a specific location.
	/// Params:
	/// tile_x & y - The location on the tile map
	/// width & height - The size of the entity in tiles
	////////////////////////////////////////////////////////////
	Entity(float tile_x, float tile_y, unsigned int width, unsigned int height);

	////////////////////////////////////////////////////////////
	/// Virtual desturctor makes sure that polymorphic objects
	/// will be properly destructed.
	////////////////////////////////////////////////////////////
	virtual ~Entity() = 0;


	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Will draw this entities contained sprite onto the window
	/// Params:
	/// window - The window you wish to render to
	////////////////////////////////////////////////////////////
	void draw(sf::RenderWindow& window);

	////////////////////////////////////////////////////////////
	/// Will return weather this entity occupies the passed in
	/// x & y coord.
	/// Params:
	/// tile_x & y - The location you want to check if it occupies
	////////////////////////////////////////////////////////////
	bool occupies(unsigned int tile_x, unsigned int tile_y) const;
	

	/* =========================================================== */
	/* ========================= Getters ========================= */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Gets the center of the sprite. This is absolute, so the 
	/// main purpose of this is to be able to center the view on
	/// a specific entity.
	////////////////////////////////////////////////////////////
	sf::Vector2f get_center() const;
};

#endif