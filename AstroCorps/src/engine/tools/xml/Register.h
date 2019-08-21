#ifndef __REGISTER__H__
#define __REGISTER__H__

#include "engine/common.h"

////////////////////////////////////////////////////////////
/// The Register namespace handles everything dealing with
/// Registry values. The registry holds the information
/// needed to read the various xml files thoughout the game
////////////////////////////////////////////////////////////
namespace Register {
	////////////////////////////////////////////////////////////
	/// This function initilizes the entire registy. This method
	/// should only be called once and is therefore locked after
	/// it is first called and will do nothing on subsequent calls.
	////////////////////////////////////////////////////////////
	void init(const char* register_filepath);

	////////////////////////////////////////////////////////////
	/// Given a register number of a tile, this will return a
	/// point by reference. The point hold the x and y location
	/// on the tilesheet for the tile's texture. Both x & y start
	/// at 0.
	////////////////////////////////////////////////////////////
	const Util::Point& get_tilesheet_location(unsigned int reg_num);

	////////////////////////////////////////////////////////////
	/// Given a register number of a font, this will return 
	/// that font (loaded from the register file). It returns
	/// by reference.
	////////////////////////////////////////////////////////////
	const sf::Font& get_font(unsigned int reg_num);

	const sf::Texture& get_tile_sheet();

	const sf::Texture& get_texture(unsigned int reg_num);
}

#endif