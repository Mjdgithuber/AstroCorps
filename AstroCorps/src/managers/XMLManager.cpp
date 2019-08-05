#include "XMLManager.h"

#include <iostream>

namespace XML {

	using namespace tinyxml2;
	#ifndef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return false; }
		#define ERROR_CHECK(result) if(!result) { printf("ERROR_CHECK FAILED!\n"); return false; }
	#endif

	namespace {
		bool load_xml_file(XMLDocument& doc, const char* filepath) {
			XMLError eResult = doc.LoadFile(filepath);
			XMLCheckResult(eResult);

			return true;
		}
	}

	bool load_map_data(const char* map_filepath) {
		XMLDocument xmlDoc;
		XMLError err_res; // stores errors we might heave

		ERROR_CHECK(load_xml_file(xmlDoc, map_filepath));

		// parent root is the root node of the xml file
		XMLNode* parent_root = xmlDoc.FirstChild();
		if (parent_root == nullptr) return XML_ERROR_FILE_READ_ERROR;

		XMLElement* size_element = parent_root->FirstChildElement("Size");
		if (size_element == nullptr) return XML_ERROR_PARSING_ELEMENT;

		// get width and height from xml file
		int width, height;
		err_res = size_element->QueryIntAttribute("width", &width);
		XMLCheckResult(err_res);
		err_res = size_element->QueryIntAttribute("height", &height);
		XMLCheckResult(err_res);

		printf("Width: %d Height: %d\n", width, height);

		// get all of the tiles
		XMLElement* tile_element = parent_root->FirstChildElement("Tile");
		while (tile_element != nullptr) {
			std::string text;
			int x, y;
			
			const char* raw_text = nullptr;
			raw_text = tile_element->Attribute("name");// ->q->QueryStringAttribute("name", name);
			tile_element->QueryIntAttribute("x", &x);
			tile_element->QueryIntAttribute("y", &y);

			if (!raw_text)
				return 0;

			text = raw_text;


			std::cout << "X: " << x << " Y: " << y << " Name: " << text << "\n";
			tile_element = tile_element->NextSiblingElement("Tile");
		}


		return true;
	}

}