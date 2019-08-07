#include "XMLManager.h"

#include <iostream>

#include "..\tiles\TilePackage.h"
#include "..\util\Util.h"

namespace XML {

	using namespace tinyxml2;
	#ifndef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("XML Error: %i\n", a_eResult); return false; }
		#define XMLNullCheck(ptr, error) if(ptr == nullptr) { printf("XML Null Ptr Error: %i\n", error); }
	#endif

	namespace {
		// Think about returning root node
		bool load_xml_file(XMLDocument& doc, const char* filepath) {
			XMLError eResult = doc.LoadFile(filepath);
			XMLCheckResult(eResult);

			return true;
		}

		/* Loads width and height from element */
		bool load_size_element(XMLNode* parent_node, unsigned int& width, unsigned int& height) {
			XMLError err_res;

			XMLElement* size_element = parent_node->FirstChildElement("Size");
			XMLNullCheck(size_element, XML_ERROR_PARSING_ELEMENT);

			err_res = size_element->QueryUnsignedAttribute("width", &width);
			XMLCheckResult(err_res);
			err_res = size_element->QueryUnsignedAttribute("height", &height);
			XMLCheckResult(err_res);

			return true;
		}

		void load_all_tiles(XMLNode* parent_node, Tiles::TilePackage* tp) {
			// get all of the tiles
			XMLElement* tile_element = parent_node->FirstChildElement("Tile");
			while (tile_element != nullptr) {
				unsigned int x, y, reg_num, modifier_reg_num;
				std::string script;
				
				// load a single tile 
				////////////////////////////////////////////////// NEED TO ERROR CHECK HERE!!!!
				const char* raw_text = nullptr;
				tile_element->QueryUnsignedAttribute("x", &x);
				tile_element->QueryUnsignedAttribute("y", &y);
				tile_element->QueryUnsignedAttribute("reg_num", &reg_num);
				tile_element->QueryUnsignedAttribute("modifier_reg_num", &modifier_reg_num);
				raw_text = tile_element->Attribute("script");

				if (raw_text != nullptr)
					script = raw_text;

				std::cout << "X: " << x << " Y: " << y << ", Reg Num: " << reg_num << ", Mod Num: " << modifier_reg_num << ", Script: " << script << "\n";

				// load tile into package
				tp->modify_tile(x, y, reg_num, modifier_reg_num, script);
				
				// go to next tile, will be nullptr if there isn't any more
				tile_element = tile_element->NextSiblingElement("Tile");
			}
		}
	}

	Tiles::TilePackage* load_map(const char* map_filepath) {
		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// open the file
		load_xml_file(xmlDoc, map_filepath);

		// parent root is the root node of the xml file
		XMLNode* root = xmlDoc.FirstChild();
		XMLNullCheck(root, XML_ERROR_FILE_READ_ERROR);

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

	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path) {
		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// open the file
		load_xml_file(xmlDoc, register_path);
		
		// get node of xml doc
		XMLNode* root = xmlDoc.FirstChild();
		XMLNullCheck(root, XML_ERROR_FILE_READ_ERROR);

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