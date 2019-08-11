#include "EntityParser.h"

#include "xml\Register.h"
#include "managers\TextureManager.h"
#include "entity\Entity.h"

namespace XML {

	Movable* read_movable_component(XMLElement* comp) {
		unsigned int x, y, width, height;
		float speed;

		XMLElement* child = comp->FirstChildElement();
		while (child != nullptr) {
			std::string name = child->Name();

			if (name == "Size") load_size_element(child, width, height);
			else if (name == "Location") load_location_element(child, x, y);
			else if (name == "Speed") load_float(child, "speed", speed);

			child = child->NextSiblingElement();
		}

		return new Movable(x, y, width, height, speed);
	}

	GraphicalBase* read_graphical_base_component(XMLElement* comp) {
		return nullptr;
	}

	Transform* read_transform_component(XMLElement* comp) {
		return nullptr;
	}

	bool load_entity(Entity* entity, const char* filepath) {
		LOG_DEBUG("Loading Entity \'{0}\'", filepath);

		// make a xml doc to load xml data DOM model
		XMLDocument xmlDoc;

		// load the file and get the root node
		XMLNode* root = load_xml_file(xmlDoc, filepath);

		const char* raw_name;
		XMLNullCheck((raw_name = root->ToElement()->Attribute("name")), XML_NO_ATTRIBUTE);
		LOG_DEBUG("Entity File Opened. Entity Name: {0}", raw_name);

		// set entities name
		entity->m_name = raw_name;

		XMLElement* component = root->FirstChildElement("Component");
		while (component != nullptr) {
			unsigned int reg_num;
			XMLCheckResult(component->QueryUnsignedAttribute("reg_num", &reg_num));

			std::string type(Register::get_component_name(reg_num));
			if (type == "Movable") {
				Movable* mov = read_movable_component(component);
				if (!entity->add_component(mov)) delete mov;
			}
			else if (type == "Graphics") {
				GraphicalBase* fx_base = new GraphicalBase();
				sf::Sprite& fx_sprite = fx_base->get_sprite();
				fx_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
				fx_sprite.setScale(Application::get_scale(), Application::get_scale());
				fx_sprite.setPosition(0, 0);
				//entity->m_fx_base = fx_base;
				entity->add_component(fx_base);
				//entity->m_components[typeid(GraphicalBase)] = fx_base;
			}

			component = component->NextSiblingElement("Component");
		}

		return true;
	}

}