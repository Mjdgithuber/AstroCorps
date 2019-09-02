#ifndef __REGISTER__PARSER__H__
#define __REGISTER__PARSER__H__

#include <list>

#include "engine/common.h"
#include "XMLUtils.h"

namespace Engine {
	namespace XML {

		////////////////////////////////////////////////////////////
		/// This will load an xml file given the path to the register
		/// file. This will cache the root node to avoid having to
		/// reopen the register for each operation
		/// Params:
		/// register_filepath - The path the the main register file
		////////////////////////////////////////////////////////////
		bool load_register_file(const char* register_filepath);

		////////////////////////////////////////////////////////////
		/// This will load the Tile part of the Registry file. The
		/// registry allows the map files to be appropriately loaded
		/// in a flexible manner.
		/// Params:
		/// locations - The place to store the location data 
		/// register_path - The path to the register
		////////////////////////////////////////////////////////////
		bool read_tile_location_register(std::vector<std::pair<std::string, Util::Point>>& assets);

		////////////////////////////////////////////////////////////
		/// This will load the Font part of the Registry file. The
		/// registry allows the fonts to be used all of the program
		/// without having to needlessly create fonts whenever they
		/// are used
		/// Params:
		/// fonts - The place to store the font data 
		/// register_path - The path to the register
		////////////////////////////////////////////////////////////
		bool read_font_register(std::vector<sf::Font>& fonts);
		
		////////////////////////////////////////////////////////////
		/// This will read and store all needed information about 
		/// the various texture sheets found in the register file
		/// Params:
		/// textures - The list to store texture sheets in
		////////////////////////////////////////////////////////////		
		bool read_texture_sheet_register(std::list<sf::Texture>& textures);

		////////////////////////////////////////////////////////////
		/// This will load the tile sheet, which contains the assets
		/// for all of the tiles. NOTE: the tile sheet is loaded as
		/// one large texture in which contains all the tiles
		/// Params:
		/// texture - The texture to store the tile sheet in
		////////////////////////////////////////////////////////////
		bool read_tile_sheet_register(sf::Texture& texture);

	}
}

#endif