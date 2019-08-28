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
			
			std::vector<std::pair<std::string, Util::Point>>
				tile_sheet_assets;
			//std::vector<Util::Point> tilesheet_locations;
			std::vector<sf::Font> fonts;
			sf::Texture tile_sheet;
			std::vector<sf::Texture> textures;
		}

		#define FALSE_WRAPPER(wrapped) if(!wrapped) return false

		/* Load the registry */
		bool init(const char* register_filepath) {
			FALSE_WRAPPER(XML::load_register_file(register_filepath));

			if (!inited) {
				FALSE_WRAPPER(XML::read_tile_register(tile_sheet_assets));
				FALSE_WRAPPER(XML::read_texture_register(textures));
				FALSE_WRAPPER(XML::read_tilesheet_register(tile_sheet));
				FALSE_WRAPPER(XML::read_font_register(fonts));
			}
			inited = true;

			return true;
		}

		/* Returns the location of the tile's texture baes on
		   a register number */
		const Util::Point& get_tile_sheet_location(unsigned int reg_num) {
			LOG_IF(ERROR_LEVEL, reg_num >= tile_sheet_assets.size(), "Attemped "
				"to call \'get_tilesheet_location\' with reg_num \'{0}\' when "
				"there is only '{1}' possible reg_num's (starting a 0)", reg_num,
				tile_sheet_assets.size());

			return tile_sheet_assets[reg_num].second;
		}

		/* Returns the location of the tile's texture based on
		   the name of the texture. NOTE: Register number should
		   is perfered, but it makes sense to look something up
		   by name under certain circumstances */
		Util::Point get_tile_sheet_location(const std::string& name) {
			// attempt to locate texture with the name
			for (unsigned int i = 0; i < tile_sheet_assets.size(); i++) {
				if (name == tile_sheet_assets[i].first)
					return tile_sheet_assets[i].second;
			}

			// the name wasn't found
			LOG_ERROR("Attempted to call get_tilesheet_location with invalid "
				"texture name \'{0}\'", name);

			return Util::Point(-1, -1);
		}

		/* Returns the font with the given register number */
		const sf::Font& get_font(unsigned int reg_num) {
			return fonts[reg_num];
		}

		/* Returns the tile sheet. NOTE: there is only one tilesheet */
		const sf::Texture& get_tile_sheet() {
			return tile_sheet;
		}

		/* Returns the texture with the given register number */
		const sf::Texture& get_texture_sheet(unsigned int reg_num) {
			return textures[reg_num];
		}
	}
}