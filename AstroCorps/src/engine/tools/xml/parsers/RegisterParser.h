#ifndef __REGISTER__PARSER__H__
#define __REGISTER__PARSER__H__

#include "engine/common.h"
#include "XMLUtils.h"

namespace XML {

	////////////////////////////////////////////////////////////
	/// This will load the Tile part of the Registry file. The
	/// registry allows the map files to be appropriately loaded
	/// in a flexible manner.
	/// Params:
	/// locations - The place to store the location data 
	/// register_path - The path to the register
	////////////////////////////////////////////////////////////
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path);

	////////////////////////////////////////////////////////////
	/// This will load the Font part of the Registry file. The
	/// registry allows the fonts to be used all of the program
	/// without having to needlessly create fonts whenever they
	/// are used
	/// Params:
	/// fonts - The place to store the font data 
	/// register_path - The path to the register
	////////////////////////////////////////////////////////////
	bool load_font_register(std::vector<sf::Font>& fonts, const char* register_path);

	////////////////////////////////////////////////////////////
	/// This will load the Component part of the Registry file. 
	/// As of now the component register makes sure that entities
	/// only have components that are register with the game.
	/// Params:
	/// components - The place to store the data from the readout
	/// register_path - The path to the register
	////////////////////////////////////////////////////////////
	bool load_component_register(std::vector<std::string>& components, const char* register_path);

}

#endif