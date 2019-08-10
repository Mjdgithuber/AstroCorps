#include <vector>

#include <SFML/Graphics.hpp>

#include "Register.h"
#include "..\util\Util.h"
#include "..\managers\XMLManager.h"

namespace Register {
	/* anonymous namespace to provide static encapsulation */
	namespace {
		bool inited = false;
		std::vector<Util::Point> tilesheet_locations;
		std::vector<sf::Font> fonts;
		std::vector<sf::Texture> textures;
		std::vector<std::string> components;
	}

	/* Load the registry */
	void init() {
		const char* register_filepath = "assets/register/register.xml";

		if (!inited) {
			XML::load_tile_register(tilesheet_locations, register_filepath);
			XML::load_font_register(fonts, register_filepath);
			XML::load_component_register(components, register_filepath);
		}
		inited = true;
	}

	/* Returns the location of the tile's texture */
	const Util::Point& get_tilesheet_location(unsigned int reg_num) {
		return tilesheet_locations[reg_num];
	}

	const sf::Font& get_font(unsigned int reg_num) {
		return fonts[reg_num];
	}

	const std::string& get_component_name(unsigned int reg_num) {
		return components[reg_num];
	}
}