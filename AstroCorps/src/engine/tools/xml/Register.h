#ifndef __REGISTER__H__
#define __REGISTER__H__

#include "engine/common.h"

namespace Engine {
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
		/// Params:
		/// register_filepath - The file path of the register file
		////////////////////////////////////////////////////////////
		bool init(const char* register_filepath);

		////////////////////////////////////////////////////////////
		/// Given a register number of a tile, this will return a
		/// point by reference. The point hold the x and y location
		/// on the tilesheet for the tile's texture. Both x & y start
		/// at 0.
		/// Params:
		/// reg_num - The register number of tile you want the 
		/// location of
		////////////////////////////////////////////////////////////
		const Util::Point& get_tilesheet_location(unsigned int reg_num);

		////////////////////////////////////////////////////////////
		/// Given a register number of a font, this will return 
		/// that font (loaded from the register file). It returns
		/// by reference.
		/// Params:
		/// reg_num - The register number of the font
		////////////////////////////////////////////////////////////
		const sf::Font& get_font(unsigned int reg_num);

		////////////////////////////////////////////////////////////
		/// Returns the tile sheet that contains all of the tile's
		/// textures. NOTE: as of current there is only one tile
		/// sheet
		////////////////////////////////////////////////////////////
		const sf::Texture& get_tilesheet();

		////////////////////////////////////////////////////////////
		/// Given a register number of a texture this method will
		/// return that texture by reference
		/// Params:
		/// reg_num - The register number of the texture
		////////////////////////////////////////////////////////////
		const sf::Texture& get_texture(unsigned int reg_num);
	}
}

#endif