#include <vector>

#include <SFML/Graphics.hpp>

#include "Register.h"
#include "engine/common.h"
#include "engine/tools/xml/parsers/RegisterParser.h"

namespace Register {
	/* anonymous namespace to provide static encapsulation */
	namespace {
		bool inited = false;
		std::vector<Util::Point> tilesheet_locations;
		std::vector<sf::Font> fonts;
		sf::Texture tile_sheet;
		std::vector<sf::Texture> textures;
	}

	/* Load the registry */
	void init(const char* register_filepath) {
		XML::load_register(register_filepath);

		if (!inited) {
			XML::load_tile_register(tilesheet_locations);
			XML::load_texture_register(textures);
			XML::load_tile_sheet_register(tile_sheet);
			XML::load_font_register(fonts);
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

	const sf::Texture& get_tile_sheet() {
		return tile_sheet;
	}

	const sf::Texture& get_texture(unsigned int reg_num) {
		return textures[reg_num];
	}
}