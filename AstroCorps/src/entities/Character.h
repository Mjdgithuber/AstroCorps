#ifndef __CHARACTER__H__
#define __CHARACTER__H__

#include "Entity.h"
#include "..\interfaces\Updatable.h"
#include "..\util\Util.h"

class Character : public Entity {
private:
	// dealing with movement
	bool m_moving;
	float m_speed; // in seconds per tile
	Util::Direction m_curr_dir;
	Util::Direction m_next_dir;
	sf::Time m_elap; // elasped movement time

	// destination coordinates
	unsigned int m_final_tile_x;
	unsigned int m_final_tile_y;


	/* =========================================================== */
	/* ==================== Helper Functions ===================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Updates the final tile x & y values to match the direction
	/// this character is moving in
	////////////////////////////////////////////////////////////
	void update_destination();

	////////////////////////////////////////////////////////////
	/// This function will check to see if the character has
	/// moved the required distance. If the player has moved
	/// that distance, if the character is changing directions
	/// it will snap percentage to 100% (so to snap the character
	/// to the grid) and reset the elasped time. If the player 
	/// is continuing in the same direction then it adjust m_elap
	/// appropriately. This is extensively commented in cpp file.
	/// It returns weather or not the character traveled the
	/// required distance.
	////////////////////////////////////////////////////////////
	bool check_percentage(float& percentage);
public:
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Makes a new character at a given x & y location. 
	/// Params:
	/// tile_x & y - The location of this character in tiles
	/// width & height - The width & height (in tiles) of char
	/// speed - The time it takes the character to traverse one tile
	////////////////////////////////////////////////////////////
	Character(float tile_x, float tile_y, unsigned int width, unsigned int height, float speed);

	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Will set the next direction of this character. If the 
	/// character is already moving then this will set the next
	/// direction it will move in.
	/// Params:
	/// dir - The direction to move in next
	////////////////////////////////////////////////////////////
	bool set_movement(Util::Direction dir = Util::STATIONARY);

	////////////////////////////////////////////////////////////
	/// Will move the character depending on the direction it is
	/// moving in and its speed.
	/// Params:
	/// delta_time - amount of time it took to render last frame
	////////////////////////////////////////////////////////////
	void update(const sf::Time& delta_time) override;
};

#endif