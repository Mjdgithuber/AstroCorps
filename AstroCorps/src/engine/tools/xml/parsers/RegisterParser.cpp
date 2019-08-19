#include "RegisterParser.h"

namespace XML {

	namespace {
		void print_register_error(const std::string& reg, const std::string& name,
			unsigned int received, unsigned int expected) {
			LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
			LOG_ERROR("Register Error Occured With \'{0}\'", reg);
			LOG_ERROR("\'{0}\' Was Loaded With Register #: {1}, Expected Register: {2}", name, received, expected);
			LOG_ERROR("Register Numbers Must Be Consecutive!");
			LOG_ERROR("!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!");
		}
	}

	/* This method takes in a vector of points by reference which it
	   uses to store the location of each tile's texture on the tile
	   sheet. The register_path is the path the the register file
	   containing the location data. */
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path) {
		LOG_DEBUG("Loading Tile Register");

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, register_path);

		// get the tile register head
		XMLElement* tile_register_head = root->FirstChildElement("TileRegister");
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

	bool load_font_register(std::vector<sf::Font>& fonts, const char* register_path) {
		LOG_DEBUG("Loading Fonts!");

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, register_path);

		// get the tile register head
		XMLElement* font_register_head = root->FirstChildElement("FontRegister");
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

	bool load_component_register(std::vector<std::string>& components, const char* register_path) {
		LOG_DEBUG("Loading Components!");

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, register_path);

		// get the tile register head
		XMLElement* component_register_head = root->FirstChildElement("ComponentRegister");
		XMLNullCheck(component_register_head, XML_NO_ATTRIBUTE);

		// for error checking
		unsigned int current_reg_num = 0;
		XMLElement* component_entry = component_register_head->FirstChildElement("Component");
		while (component_entry != nullptr) {
			// get font filepath
			unsigned int reg_num;
			const char* component_name;
			XMLNullCheck((component_name = component_entry->Attribute("name")), XML_NO_ATTRIBUTE);
			XMLCheckResult(component_entry->QueryUnsignedAttribute("reg_num", &reg_num));

			if (reg_num != current_reg_num++) {
				print_register_error("ComponentRegister", component_name, reg_num, current_reg_num - 1);
				return false;
			}

			// add font to vector and load the font file
			components.emplace_back(component_name);

			// increment to next registry entry
			component_entry = component_entry->NextSiblingElement("Component");
		}

		return true;
	}

}