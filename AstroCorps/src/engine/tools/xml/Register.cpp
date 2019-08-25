#include <vector>

#include <SFML/Graphics.hpp>

#include "Register.h"
#include "engine/common.h"
#include "engine/tools/xml/parsers/RegisterParser.h"

namespace Engine {
	namespace Register {
		/* anonymous namespace to provide static encapsulation */
		namespace {
			bool inited = false;
			std::vector<Util::Point> tilesheet_locations;
			std::vector<sf::Font> fonts;
			sf::Texture tilesheet;
			std::vector<sf::Texture> textures;
		}

		#define FALSE_WRAPPER(wrapped) if(!wrapped) return false

		/* Load the registry */
		bool init(const char* register_filepath) {
			FALSE_WRAPPER(XML::load_register_file(register_filepath));

			if (!inited) {
				FALSE_WRAPPER(XML::read_tile_register(tilesheet_locations));
				FALSE_WRAPPER(XML::read_texture_register(textures));
				FALSE_WRAPPER(XML::read_tilesheet_register(tilesheet));
				FALSE_WRAPPER(XML::read_font_register(fonts));
			}
			inited = true;

			return true;
		}

		/* Returns the location of the tile's texture */
		const Util::Point& get_tilesheet_location(unsigned int reg_num) {
			return tilesheet_locations[reg_num];
		}

		/* Returns the font with the given register number */
		const sf::Font& get_font(unsigned int reg_num) {
			return fonts[reg_num];
		}

		/* Returns the tile sheet. NOTE: there is only one tilesheet */
		const sf::Texture& get_tilesheet() {
			return tilesheet;
		}

		/* Returns the texture with the given register number */
		const sf::Texture& get_texture(unsigned int reg_num) {
			return textures[reg_num];
		}
	}
}