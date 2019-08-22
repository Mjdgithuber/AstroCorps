#include "MapParser.h"

namespace XML {

	/* Anonymous namespace allows for private functions without,
   wrapping in a class because there would be no point of
   having more than one XML manager per project! */
	namespace {
		bool load_all_tiles(const char* map_filepath, XMLNode* parent_node, TilePackage* tp) {
			// get all of the tiles
			XMLElement* tile_element = parent_node->FirstChildElement("Tile");
			while (tile_element != nullptr) {
				// varibles to be pull from xml file
				unsigned int x, y, reg_num, modifier_reg_num;
				std::string script;

				// load one tile from xml file w/ verbose error checking
				const char* raw_text = nullptr;
				LOG_IF(CRIT_LEVEL, tile_element->QueryUnsignedAttribute("x", &x) != XML_SUCCESS,
					"Map File '{0}' Contains a Tile With No X Attribute", map_filepath);
				LOG_IF(CRIT_LEVEL, tile_element->QueryUnsignedAttribute("y", &y) != XML_SUCCESS,
					"Map File '{0}' Contains Tile With X '{1}' & No Y Attribute", map_filepath, x);
				LOG_IF(CRIT_LEVEL, tile_element->QueryUnsignedAttribute("reg_num", &reg_num) != XML_SUCCESS,
					"Map File '{0}' Tile X '{1}' & Y '{2}' Has No reg_num Tag", map_filepath, x, y);
				LOG_IF(CRIT_LEVEL, tile_element->QueryUnsignedAttribute("modifier_reg_num", &modifier_reg_num) !=
					XML_SUCCESS, "Map File '{0}' Tile X '{1}' & Y '{2}' Has No modifier_reg_num Tag", map_filepath, x, y);
				LOG_IF(CRIT_LEVEL, (raw_text = tile_element->Attribute("script")) == nullptr,
					"Map File '{0}' Tile X '{1}' & Y '{2}' Has No script Tag", map_filepath, x, y);

				// convert char* to string
				script = raw_text;

				LOG_TRACE("X: {0} Y: {1}, Reg Num: {2}, Mod Num: {3}, Script {4}", x, y, reg_num, modifier_reg_num, script);

				// load tile into package
				tp->modify_tile(x, y, reg_num, modifier_reg_num, script);

				// go to next tile, will be nullptr if there isn't any more
				tile_element = tile_element->NextSiblingElement("Tile");
			}

			return true;
		}


	}

	/* This function takes in a filepath to a map xml file. This
	   will allocate and return a TilePackage with all of the
	   information contained in the map file. This TilePackage
	   MUST be deleted (freed) by the caller of this function! */
	TilePackage* load_map(const char* map_filepath) {
		LOG_DEBUG("Loading map: {0}", map_filepath);

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, map_filepath);

		// get width and height from xml file
		XMLElement* size = root->FirstChildElement("Size");
		LOG_IF(CRIT_LEVEL, size == nullptr, "Failed to Load Map '{0}', No Size Tag "
			"Was Found!", map_filepath);
		unsigned int width, height;
		load_size_element(size, width, height);

		// make a new tile package to hold all tile information
		TilePackage* tp = new TilePackage(width, height);
		LOG_TRACE("Width: {0} Height: {1}", width, height);

		// load tiles
		load_all_tiles(map_filepath, root, tp);

		return tp;
	}

}