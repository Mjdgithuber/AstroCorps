#include "XMLManager.h"

#include <iostream>

#include "..\tiles\TilePackage.h"
#include "..\util\Util.h"
#include "..\xml\Register.h"
#include "..\entity\components\Movable.h"
#include "..\entity\components\GraphicalBase.h"
#include "TextureManager.h"
#include "..\main\Application.h"
#include "..\entity\Entity.h"

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

			return true;
		}

		void print_register_error(const std::string& reg, const std::string& name,
								  unsigned int received, unsigned int expected) {
			std::cout << "\n!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!\n";
			std::cout << "Register Error Occured With \'" << reg << "\'\n";
			std::cout << "\'" << name << "\' Was Loaded With Register #: " << received
				<< ", Expected: " << expected << "\n";
			std::cout << "Register Numbers Must Be Consecutive!\n";
			std::cout << "!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!\n\n";
		}
	}

	/* This function takes in a filepath to a map xml file. This
	   will allocate and return a TilePackage with all of the
	   information contained in the map file. This TilePackage
	   MUST be deleted (freed) by the caller of this function! */
	Tiles::TilePackage* load_map(const char* map_filepath) {
		std::cout << "Loading Map!\n";

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

	bool load_entity(Entity* entity, const char* filepath) {
		std::cout << "Loading An Entity!\n";

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, filepath);

		const char* raw_name;
		XMLNullCheck((raw_name = root->ToElement()->Attribute("name")), XML_NO_ATTRIBUTE);
		std::cout << "Loading Entity: \'" << raw_name << "\'!\n";
		std::cout << "Root: " << root << "\n";

		XMLElement* component = root->FirstChildElement("Component");
		while (component != nullptr) {
			unsigned int reg_num;
			XMLCheckResult(component->QueryUnsignedAttribute("reg_num", &reg_num));

			std::string type(Register::get_component_name(reg_num));
			if (type == "Movable") {
				Movable* mov = new Movable(0, 0, 1, 1, .33f);
				entity->m_transform = mov;
				entity->m_components[typeid(Movable)] = mov;// .push_back(mov);
				//please_remove->mov = new Movable(0, 0, 1, 1, .33f);
				//component_list.push_back(please_remove->mov);
			}
			else if (type == "Graphics") {
				GraphicalBase* fx_base = new GraphicalBase();
				sf::Sprite& fx_sprite = fx_base->get_sprite();
				fx_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
				fx_sprite.setScale(Application::get_scale(), Application::get_scale());
				fx_sprite.setPosition(0, 0);
				entity->m_fx_base = fx_base;
				entity->m_components[typeid(GraphicalBase)] = fx_base;
			}

			component = component->NextSiblingElement("Component");
		}

		return true;
	}

	/* This method takes in a vector of points by reference which it 
	   uses to store the location of each tile's texture on the tile
	   sheet. The register_path is the path the the register file 
	   containing the location data. */
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path) {
		std::cout << "Loading Tile Register!\n";

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
		std::cout << "Loading Fonts!\n";

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
		std::cout << "Loading Components!\n";

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