#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "Register.h"
#include "engine/common.h"
#include "engine/tools/xml/parsers/RegisterParser.h"

namespace Engine {
	namespace Register {

		/* Anonymous namespace to provide static encapsulation */
		namespace {
			/* To ensure register is only loaded once */
			bool inited = false;
			
			/* The tile_sheet is a single texture that holds
			   every tile's texture. The tile_assets list holds
			   every tile's name and location on the tile_sheet */
			sf::Texture tile_sheet;
			std::vector<std::pair<std::string, Util::Point>>
				tile_assets;
			
			/* A list that holds all loaded fonts */
			std::list<sf::Font> fonts;
			
			/* A list that holds all loaded texture_sheet, a
			   texture_sheet is a singe texture that holds all 
			   the info about a certain entity's texture such 
			   as animations */
			std::list<sf::Texture> texture_sheets;
		}

		/* Allows the returning of false only if the condition
		   is also false. NOTE: this will never return true! */
		#define FALSE_WRAPPER(condition) if(!condition) return false

		/* Load the registry */
		bool init(const char* register_filepath) {			
			if (!inited) {
				// load register and read each component
				FALSE_WRAPPER(XML::load_register_file(register_filepath));
				FALSE_WRAPPER(XML::read_tile_location_register(tile_assets));
				FALSE_WRAPPER(XML::read_texture_sheet_register(texture_sheets));
				FALSE_WRAPPER(XML::read_tile_sheet_register(tile_sheet));
				FALSE_WRAPPER(XML::read_font_register(fonts));
			}

			return (inited = true);
		}

		/* Returns the tile sheet. NOTE: there is only one tilesheet */
		const sf::Texture& get_tile_sheet() {
			return tile_sheet;
		}

		/* Returns the location of the tile's texture baes on
		   a register number */
		const Util::Point& get_tile_location(unsigned int reg_num) {
			LOG_IF(ERROR_LEVEL, reg_num >= tile_assets.size(), "Attemped "
				"to call 'get_tile_location' with reg_num '{0}' when "
				"when maximum reg_num is '{1}'", reg_num, tile_assets.size() - 1);

			return tile_assets[reg_num].second;
		}

		/* Returns the location of the tile's texture based on
		   the name of the texture. NOTE: Register number should
		   is perfered, but it makes sense to look something up
		   by name under certain circumstances */
		const Util::Point& get_tile_location(const std::string& name) {
			bool found = false;
			
			// locate object
			auto itr = tile_assets.begin();
			for (unsigned int i = 0; i < tile_assets.size(); i++) {
				if (name == itr->first) {
					found = true;
					break;
				}
				itr++;
			}

			// log error if element wan't found!!
			LOG_IF(ERROR_LEVEL, "Attempted to call get_tile_location with invalid "
				"texture name '{0}'", name);

			return itr->second;
		}

		/* Returns the font with the given register number */
		const sf::Font& get_font(unsigned int reg_num) {
			LOG_IF(CRIT_LEVEL, reg_num >= fonts.size(), "Attempted to retrieve "
				" font reg_num '{0}' when maximum reg_num is '{1}'",
				reg_num, fonts.size() - 1);

			// locate specific font in list
			auto itr = fonts.begin();
			for (unsigned int i = 0; i < reg_num; i++) itr++;

			return *itr;
		}

		/* Returns the texture with the given register number */
		const sf::Texture& get_texture_sheet(unsigned int reg_num) {
			LOG_IF(CRIT_LEVEL, reg_num >= texture_sheets.size(), "Attempted to retrieve "
				" texture_sheet reg_num '{0}' when maximum reg_num is '{1}'",
				reg_num, texture_sheets.size() - 1);

			// locate texture in list
			auto itr = texture_sheets.begin();
			for (unsigned int i = 0; i < reg_num; i++) itr++;

			return *itr;
		}
	}
}