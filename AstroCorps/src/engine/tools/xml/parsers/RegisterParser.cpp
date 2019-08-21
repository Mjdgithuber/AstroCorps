#include "RegisterParser.h"

namespace XML {

	namespace {
		XMLDocument xmlDoc;
		XMLNode* register_node;

		void print_register_error(const std::string& reg, const std::string& name,
			unsigned int received, unsigned int expected) {
			LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
			LOG_ERROR("Register Error Occured With \'{0}\'", reg);
			LOG_ERROR("\'{0}\' Was Loaded With Register #: {1}, Expected Register: {2}", name, received, expected);
			LOG_ERROR("Register Numbers Must Be Consecutive!");
			LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
		}
	}

	bool load_register(const char* register_filepath) {
		LOG_DEBUG("Loading Register!");

		register_node = load_xml_file(xmlDoc, register_filepath);

		return true;
	}

	/* This method takes in a vector of points by reference which it
	   uses to store the location of each tile's texture on the tile
	   sheet. The register_path is the path the the register file
	   containing the location data. */
	bool load_tile_register(std::vector<Util::Point>& locations) {
		LOG_DEBUG("Loading Tile Register");

		// get the tile register head
		XMLElement* tile_register_head = register_node->FirstChildElement("TileRegister");
		XMLNullCheck(tile_register_head, XML_NO_ATTRIBUTE);

		// get the tile information
		XMLElement* tile_entry = tile_register_head->FirstChildElement("Tile");
		while (tile_entry != nullptr) {
			// get tilesheet x & y
			unsigned int x, y;
			XMLCheckResult(tile_entry->QueryUnsignedAttribute("spritesheet_x", &x));
			XMLCheckResult(tile_entry->QueryUnsignedAttribute("spritesheet_y", &y));
			locations.emplace_back(x, y);

			// increment to next registry entry
			tile_entry = tile_entry->NextSiblingElement("Tile");
		}

		return true;
	}

	bool load_font_register(std::vector<sf::Font>& fonts) {
		LOG_DEBUG("Loading Fonts!");

		// get the tile register head
		XMLElement* font_register_head = register_node->FirstChildElement("FontRegister");
		XMLNullCheck(font_register_head, XML_NO_ATTRIBUTE);

		// for error checking
		unsigned int current_reg_num = 0;

		// get the tile information
		XMLElement* font_entry = font_register_head->FirstChildElement("Font");
		while (font_entry != nullptr) {
			// get font filepath
			unsigned int reg_num;
			const char* font_filepath, *font_name;
			XMLNullCheck((font_filepath = font_entry->Attribute("filepath")), XML_NO_ATTRIBUTE);
			XMLNullCheck((font_name = font_entry->Attribute("name")), XML_NO_ATTRIBUTE);
			XMLCheckResult(font_entry->QueryUnsignedAttribute("reg_num", &reg_num));

			if (reg_num != current_reg_num++) {
				print_register_error("FontRegister", font_name, reg_num, current_reg_num - 1);
				return false;
			}

			// add font to vector and load the font file
			fonts.emplace_back();
			fonts.back().loadFromFile(font_filepath);

			// increment to next registry entry
			font_entry = font_entry->NextSiblingElement("Font");
		}

		return true;
	}

	

	bool load_texture_register(std::vector<sf::Texture>& textures) {
		LOG_DEBUG("Loading Textures!");

		XMLElement* texture_register_head = register_node->FirstChildElement("TextureRegister");
		XMLNullCheck(texture_register_head, XML_NO_ATTRIBUTE);

		// for error checking
		unsigned int current_reg_num = 0;
		XMLElement* texture_entry = texture_register_head->FirstChildElement("Texture");
		while (texture_entry != nullptr) {
			// get texture asset sheet filepath
			unsigned int reg_num;
			const char* texture_name;
			const char* texture_filepath;
			XMLNullCheck((texture_name = texture_entry->Attribute("name")), XML_NO_ATTRIBUTE);
			XMLNullCheck((texture_filepath = texture_entry->Attribute("filepath")), XML_NO_ATTRIBUTE);
			XMLCheckResult(texture_entry->QueryUnsignedAttribute("reg_num", &reg_num));

			if (reg_num != current_reg_num++) {
				print_register_error("TextureRegister", texture_name, reg_num, current_reg_num - 1);
				return false;
			}

			// add font to vector and load the font file
			textures.emplace_back();
			bool loaded = textures.back().loadFromFile(texture_filepath);

			if (!loaded) {
				LOG_CRITICAL("Texture Register No. '{0}' name '{1}' failed to load with filepath '{2}'!", reg_num, texture_name, texture_filepath);
				return false;
			} else {
				LOG_DEBUG("Texture Register No. '{0}' name '{1}' loaded successfully with filepath '{2}'!", reg_num, texture_name, texture_filepath);
			}

			// increment to next registry entry
			texture_entry = texture_entry->NextSiblingElement("Texture");
		}

		return true;
	}

	bool load_tile_sheet_register(sf::Texture& texture) {
		LOG_DEBUG("Loading Tile Sheet!");

		XMLElement* tile_sheet_register_head = register_node->FirstChildElement("TileSheetRegister");
		XMLNullCheck(tile_sheet_register_head, XML_NO_ATTRIBUTE);

		// for error checking
		XMLElement* texture_sheet_entry = tile_sheet_register_head->FirstChildElement("Texture");

		if (texture_sheet_entry != nullptr) {
			// get texture asset sheet filepath
			const char* texture_sheet_name;
			const char* texture_sheet_filepath;
			XMLNullCheck((texture_sheet_name = texture_sheet_entry->Attribute("name")), XML_NO_ATTRIBUTE);
			XMLNullCheck((texture_sheet_filepath = texture_sheet_entry->Attribute("filepath")), XML_NO_ATTRIBUTE);

			bool loaded = texture.loadFromFile(texture_sheet_filepath);

			if (loaded) {
				LOG_DEBUG("Texture Sheet named '{0}' with filepath '{1}' was successfully loaded!", texture_sheet_name, texture_sheet_filepath);
				return true;
			}
			else {
				LOG_CRITICAL("Texture Sheet named '{0}' with filepath '{1}' failed to load!", texture_sheet_name, texture_sheet_filepath);
			}
		} else {
			LOG_CRITICAL("Tile Sheet Not Found!!!");
		}

		return false;
	}

}