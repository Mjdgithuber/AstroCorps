#ifndef __REGISTER__PARSER__H__
#define __REGISTER__PARSER__H__

#include <list>

#include "engine/common.h"
#include "XMLUtils.h"

namespace Engine {
	namespace XML {

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
		
		
		
		bool read_texture_sheet_register(std::list<sf::Texture>& textures);

		bool read_tile_sheet_register(sf::Texture& texture);


		/* Make a loader for each type of thingya */
	}
}

#endif