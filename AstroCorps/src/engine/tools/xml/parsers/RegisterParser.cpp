#include "RegisterParser.h"

namespace Engine {
	namespace XML {

		namespace {
			/* xmlDoc - The document that is loaded with xml stored
			   DOM format
			   register_node - The parent node of the document */
			XMLDocument xmlDoc;
			XMLNode* register_node;

			/* Will print an error about register numbers (reg_nums)
			   note being consecutive, for another layer of error 
			   checking */
			void print_register_error(const std::string& reg, const std::string& name,
				unsigned int received, unsigned int expected) {
				LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
				LOG_ERROR("Register Error Occured With \'{0}\'", reg);
				LOG_ERROR("\'{0}\' Was Loaded With Register #: {1}, Expected Register: {2}",
					name, received, expected);
				LOG_ERROR("Register Numbers Must Be Consecutive!");
				LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
			}
		}

		/* Opens the register file and stores both the document
		   and the document's node for accessing the elements
		   of the file */
		bool load_register_file(const char* register_filepath) {
			LOG_DEBUG("Loading Register!");

			// will log error if it fails
			register_node = load_xml_file(xmlDoc, register_filepath);
			if (!register_node) return false;

			return true;
		}

		/* This method takes in a vector of points by reference which it
		   uses to store the location of each tile's texture on the tile
		   sheet. The register_path is the path the the register file
		   containing the location data. */
		bool read_tile_location_register(std::vector<std::pair<std::string, Util::Point>>& assets) {
			LOG_DEBUG("Loading Tile Location Register");

			// get the tile register head
			XMLElement* tile_register_head = register_node->FirstChildElement("TileLocationRegister");
			LOG_IF_AR(CRIT_LEVEL, tile_register_head == nullptr,
				"TileLocationRegister Element Not Found in Register");

			// for error checking
			unsigned int current_reg_num = 0;

			// get the tile information
			XMLElement* tile_entry = tile_register_head->FirstChildElement("Tile");
			while (tile_entry != nullptr) {
				unsigned int reg_num, x, y;
				const char* name;

				// get tilesheet x & y and name + reg_num with error checking 
				LOG_IF_AR(CRIT_LEVEL, tile_entry->QueryUnsignedAttribute("reg_num", &reg_num) !=
					XML_SUCCESS, "Failed to find reg_num in a tile register entry");
				LOG_IF_AR(CRIT_LEVEL, (name = tile_entry->Attribute("name")) == nullptr, "Failed to "
					"find name attribute for tile entry reg_num \'{0}\'", reg_num);
				LOG_IF_AR(CRIT_LEVEL, tile_entry->QueryUnsignedAttribute("spritesheet_x", &x) !=
					XML_SUCCESS, "Failed to find spritesheet_x in tile with reg no {0}", reg_num);
				LOG_IF_AR(CRIT_LEVEL, tile_entry->QueryUnsignedAttribute("spritesheet_y", &y) !=
					XML_SUCCESS, "Failed to find spritesheet_y in tile with reg no {0}", reg_num);
				assets.emplace_back(std::make_pair(name, Util::Point(x, y)));

				// ensure register numbers are consecutive
				if (reg_num != current_reg_num++) {
					print_register_error("TileLocationRegister", name, reg_num, current_reg_num - 1);
					return false;
				}

				LOG_TRACE("Tile Location Register reg_no '{0}' named '{1}' loaded successfully!",
					reg_num, name);

				// increment to next registry entry
				tile_entry = tile_entry->NextSiblingElement("Tile");
			}

			// indicate tile locations were read successfully
			return true;
		}

		/* This will load all of the fonts in the registry
		   file in to the passed in list. This function uses
		   a list because fonts are heavy resources */
		bool read_font_register(std::list<sf::Font>& fonts) {
			LOG_DEBUG("Loading Fonts!");

			// get the tile register head
			XMLElement* font_register_head = register_node->FirstChildElement("FontRegister");
			LOG_IF_AR(CRIT_LEVEL, font_register_head == nullptr,
				"FontRegister Tag Not Found in Register XML Document");

			// for error checking
			unsigned int current_reg_num = 0;

			// get the tile information
			XMLElement* font_entry = font_register_head->FirstChildElement("Font");
			while (font_entry != nullptr) {
				unsigned int reg_num;
				const char* font_filepath, *font_name;

				// get font filepath, name, and reg_num with error checking
				LOG_IF_AR(CRIT_LEVEL, font_entry->QueryUnsignedAttribute("reg_num", &reg_num) != XML_SUCCESS,
					"No reg_num for one of the fonts in FontRegister");
				LOG_IF_AR(CRIT_LEVEL, (font_filepath = font_entry->Attribute("filepath")) == nullptr,
					"Font reg number '{0}' has no filepath attribute", reg_num);
				LOG_IF_AR(CRIT_LEVEL, (font_name = font_entry->Attribute("name")) == nullptr,
					"Font reg number '{0}' has no name attribute", reg_num);

				// ensure register numbers are consecutive
				if (reg_num != current_reg_num++) {
					print_register_error("FontRegister", font_name, reg_num, current_reg_num - 1);
					return false;
				}

				// add font to vector and load the font file
				fonts.emplace_back();
				fonts.back().loadFromFile(font_filepath);

				LOG_TRACE("Font Register reg_no '{0}' named '{1}' with file path '{2}' loaded successfully!",
					reg_num, font_name, font_filepath);

				// increment to next registry entry
				font_entry = font_entry->NextSiblingElement("Font");
			}

			return true;
		}

		/* Will load all of the texture sheets into the passed in
		   list of textures. A list is used instead of a vectore 
		   because textures are heavy assets and opengl doesn't
		   like it when you try to copy/move them which happens
		   when a vector expands. */
		bool read_texture_sheet_register(std::list<sf::Texture>& textures) {
			LOG_DEBUG("Loading Texture Sheets!");

			XMLElement* texture_register_head = register_node->FirstChildElement("TextureSheetRegister");
			LOG_IF_AR(CRIT_LEVEL, texture_register_head == nullptr,
				"TextureSheetRegister Tag Not Found in XML Register!");

			// for error checking
			unsigned int current_reg_num = 0;
			XMLElement* texture_entry = texture_register_head->FirstChildElement("Texture");
			while (texture_entry != nullptr) {
				unsigned int reg_num;
				const char* texture_name;
				const char* texture_filepath;

				// get texture sheet name, num, and filepath with error checking
				LOG_IF_AR(CRIT_LEVEL, texture_entry->QueryUnsignedAttribute("reg_num", &reg_num) != XML_SUCCESS,
					"No reg_num tag found in one of the texture entries in texture register!");
				LOG_IF_AR(CRIT_LEVEL, (texture_name = texture_entry->Attribute("name")) == nullptr,
					"Texture entry with reg_num = '{0}' has no name attribute!", reg_num);
				LOG_IF_AR(CRIT_LEVEL, (texture_filepath = texture_entry->Attribute("filepath")) == nullptr,
					"Texture entry with reg_num = '{0}' has no filepath attribute!", reg_num);

				// ensure register numbers are consecutive
				if (reg_num != current_reg_num++) {
					print_register_error("TextureRegister", texture_name, reg_num, current_reg_num - 1);
					return false;
				}

				// add font to vector and load the font file
				textures.emplace_back();
				bool loaded = textures.back().loadFromFile(texture_filepath);

				/* Log failure or success */
				LOG_IF_AR(CRIT_LEVEL, !loaded, "Texture Register No. '{0}' name '{1}' failed to "
					"load with filepath '{2}'!", reg_num, texture_name, texture_filepath);
				LOG_TRACE("Texture Sheet Register No. '{0}' name '{1}' loaded successfully with filepath "
					"'{2}'!", reg_num, texture_name, texture_filepath);

				// increment to next registry entry
				texture_entry = texture_entry->NextSiblingElement("Texture");
			}
			return true;
		}

		/* Reads the tile sheet and stores it into the passed in 
		   texture. Includes verbose error checking for better
		   debugging */
		bool read_tile_sheet_register(sf::Texture& texture) {
			LOG_DEBUG("Loading Tile Sheet!");

			// get head and log if not found
			XMLElement* tilesheet_register_head =
				register_node->FirstChildElement("TileSheetRegister");
			LOG_IF_AR(CRIT_LEVEL, tilesheet_register_head == nullptr,
				"TileSheetRegister Tag Not Found in XML register file!");

			// for error checking
			XMLElement* texture_sheet_entry =
				tilesheet_register_head->FirstChildElement("Texture");

			if (texture_sheet_entry != nullptr) {
				const char* name;
				const char* filepath;

				// get texture sheet filepath and name with error checking
				LOG_IF_AR(CRIT_LEVEL, (name = texture_sheet_entry->Attribute("name"))
					== nullptr, "The Tile Sheet Has No Name Attribute!");
				LOG_IF_AR(CRIT_LEVEL, (filepath = texture_sheet_entry->Attribute("filepath"))
					== nullptr, "Tile Sheet '{0}' Has No Name Attribute!", name);

				bool loaded = texture.loadFromFile(filepath);

				/* Log success or failure. NOTE: LOG_IF_AR will return false if logged */
				LOG_IF_AR(CRIT_LEVEL, !loaded, "Texture Sheet named '{0}' with filepath '{1}' "
					"failed to load!", name, filepath);
				LOG_TRACE("Texture Sheet named '{0}' with filepath '{1}' was successfully "
					"loaded!", name, filepath);

				return true;
			}
			LOG_CRITICAL("No Texture Found For Tile Sheet!");
			return false;
		}

	}
}