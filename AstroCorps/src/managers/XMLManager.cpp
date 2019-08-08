#include "XMLManager.h"

#include <iostream>

#include "..\tiles\TilePackage.h"
#include "..\util\Util.h"

namespace XML {

	using namespace tinyxml2;
	#ifndef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("XML Error: %i\n", a_eResult); return false; }
	#endif
	#ifndef XMLNullCheck
		#define XMLNullCheck(ptr, error) if(ptr == nullptr) { printf("XML Null Ptr Error: %i\n", error); }
	#endif

	/* Anonymous namespace allows for private functions without, 
	   wrapping in a class because there would be no point of 
	   having more than one XML manager per project! */
	namespace {
		/* Given a filepath it will attempt (if filepath is valid)
		   to load it into the passed in XMLDocument. It will also
		   get the root node and return it. NOTE: all XML files
		   must have a node otherwise it is malformed*/
		XMLNode* load_xml_file(XMLDocument& doc, const char* filepath) {
			// attempt to load file
			XMLError eResult = doc.LoadFile(filepath);
			XMLCheckResult(eResult);

			// get the root of the document
			XMLNode* root = doc.FirstChild();
			XMLNullCheck(root, XML_ERROR_FILE_READ_ERROR);

			// return the node
			return root;
		}

		/* Loads width and height from the size element in
		   file. The node is the root node of the doc, and
		   the return values are passed in by reference. */
		bool load_size_element(XMLNode* parent_node, unsigned int& width, unsigned int& height) {
			// attempt to locate the size element from the node
			XMLElement* size_element = parent_node->FirstChildElement("Size");
			XMLNullCheck(size_element, XML_ERROR_PARSING_ELEMENT);

			// get the width and height from the size element
			XMLCheckResult(size_element->QueryUnsignedAttribute("width", &width));
			XMLCheckResult(size_element->QueryUnsignedAttribute("height", &height));

			// if this is reached then it was successful
			return true;
		}

		bool load_all_tiles(XMLNode* parent_node, Tiles::TilePackage* tp) {
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

				std::cout << "X: " << x << " Y: " << y << ", Reg Num: " << reg_num << ", Mod Num: " << modifier_reg_num << ", Script: " << script << "\n";

				// load tile into package
				tp->modify_tile(x, y, reg_num, modifier_reg_num, script);
				
				// go to next tile, will be nullptr if there isn't any more
				tile_element = tile_element->NextSiblingElement("Tile");
			}
		}
	}

	/* This function takes in a filepath to a map xml file. This
	   will allocate and return a TilePackage with all of the
	   information contained in the map file. This TilePackage
	   MUST be deleted (freed) by the caller of this function! */
	Tiles::TilePackage* load_map(const char* map_filepath) {
		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, map_filepath);

		// get width and height from xml file
		unsigned int width, height;
		load_size_element(root, width, height);

		// make a new tile package to hold all tile information
		Tiles::TilePackage* tp = new Tiles::TilePackage(width, height);
		printf("Width: %d Height: %d\n", width, height);

		// load tiles
		load_all_tiles(root, tp);

		return tp;
	}

	/* This method takes in a vector of points by reference which it 
	   uses to store the location of each tile's texture on the tile
	   sheet. The register_path is the path the the register file 
	   containing the location data. */
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path) {
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
	}

}