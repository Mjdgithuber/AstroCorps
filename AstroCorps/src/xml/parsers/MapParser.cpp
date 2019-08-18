#include "MapParser.h"

namespace XML {

	/* Anonymous namespace allows for private functions without,
   wrapping in a class because there would be no point of
   having more than one XML manager per project! */
	namespace {
		bool load_all_tiles(XMLNode* parent_node, Tiles::OldTilePackage* tp, int femma) {
			// get all of the tiles
			XMLElement* tile_element = parent_node->FirstChildElement("Tile");
			while (tile_element != nullptr) {
				// varibles to be pull from xml file
				unsigned int x, y, reg_num, modifier_reg_num;
				std::string script;

				// load one tile from xml file w/ error checking
				const char* raw_text = nullptr;
				XMLCheckResult(tile_element->QueryUnsignedAttribute("x", &x));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("y", &y));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("reg_num", &reg_num));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("modifier_reg_num", &modifier_reg_num));
				XMLNullCheck((raw_text = tile_element->Attribute("script")), XML_NO_ATTRIBUTE);

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

		bool load_all_tiles(XMLNode* parent_node, TilePackage* tp) {
			// get all of the tiles
			XMLElement* tile_element = parent_node->FirstChildElement("Tile");
			while (tile_element != nullptr) {
				// varibles to be pull from xml file
				unsigned int x, y, reg_num, modifier_reg_num;
				std::string script;

				// load one tile from xml file w/ error checking
				const char* raw_text = nullptr;
				XMLCheckResult(tile_element->QueryUnsignedAttribute("x", &x));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("y", &y));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("reg_num", &reg_num));
				XMLCheckResult(tile_element->QueryUnsignedAttribute("modifier_reg_num", &modifier_reg_num));
				XMLNullCheck((raw_text = tile_element->Attribute("script")), XML_NO_ATTRIBUTE);

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
	Tiles::OldTilePackage* load_map(const char* map_filepath, int emma) {
		LOG_DEBUG("Loading map: {0}", map_filepath);

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, map_filepath);

		// get width and height from xml file
		XMLElement* size = root->FirstChildElement("Size");
		XMLNullCheck(size, XML_NO_ATTRIBUTE);
		unsigned int width, height;
		load_size_element(size, width, height);

		// make a new tile package to hold all tile information
		Tiles::OldTilePackage* tp = new Tiles::OldTilePackage(width, height);
		LOG_TRACE("Width: {0} Height: {1}", width, height);

		// load tiles
		load_all_tiles(root, tp, emma);

		return tp;
	}

	TilePackage* load_map(const char* map_filepath) {
		LOG_DEBUG("Loading map: {0}", map_filepath);

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, map_filepath);

		// get width and height from xml file
		XMLElement* size = root->FirstChildElement("Size");
		XMLNullCheck(size, XML_NO_ATTRIBUTE);
		unsigned int width, height;
		load_size_element(size, width, height);

		// make a new tile package to hold all tile information
		TilePackage* tp = new TilePackage(width, height);
		LOG_TRACE("Width: {0} Height: {1}", width, height);

		// load tiles
		load_all_tiles(root, tp);

		return tp;
	}

}