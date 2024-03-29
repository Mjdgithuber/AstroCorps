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
		/// Returns the tile sheet that contains all of the tile's
		/// textures. NOTE: as of current there is only one tile
		/// sheet. This differs from get_texture_sheet in that 
		/// the tile sheet contains 1-2 images for every different
		/// tile, and there is only one tile sheet while there is
		/// no limit on the number of texture sheets.
		////////////////////////////////////////////////////////////
		const sf::Texture& get_tile_sheet();

		////////////////////////////////////////////////////////////
		/// Given a register number of a tile, this will return a
		/// point by reference. The point holds the x and y location
		/// on the tilesheet for the tile's texture. Both x & y start
		/// at 0.
		/// Params:
		/// reg_num - The register number of tile you want the 
		/// location of
		////////////////////////////////////////////////////////////
		const Util::Point& get_tile_location(unsigned int reg_num);

		////////////////////////////////////////////////////////////
		/// Given a name of a tile, this will attempt to locate it 
		/// in the vector and will return the location if it was 
		/// found. Otherwise it will return -1, -1 and log an error.
		/// Params:
		/// name - the name of the tile you want the location of
		////////////////////////////////////////////////////////////
		const Util::Point& get_tile_location(const std::string& name);

		////////////////////////////////////////////////////////////
		/// Given a register number of a font, this will return 
		/// that font (loaded from the register file). It returns
		/// by reference.
		/// Params:
		/// reg_num - The register number of the font
		////////////////////////////////////////////////////////////
		const sf::Font& get_font(unsigned int reg_num);

		////////////////////////////////////////////////////////////
		/// Given a register number of a texture sheet this method 
		/// will return that texture sheet by reference. NOTE: The
		/// texture sheet is just loaded as a texture to allow the
		/// caller to define what needs to be done with the texture.
		/// For instance a texture sheet could just be a single
		/// static image, or it could be a sprite sheet with all the
		/// animations for some entity.
		/// Params:
		/// reg_num - The register number of the texture sheet
		////////////////////////////////////////////////////////////
		const sf::Texture& get_texture_sheet(unsigned int reg_num);
	}
}

#endif