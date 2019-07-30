#include "TextureManager.h"

namespace TextureManager {
	namespace {
		bool inited = false;
		sf::Texture entity_textures[(int)Textures::Entity::CARDINALITY];
		sf::Texture tile_sheets[(int)Textures::TileSheet::CARDINALITY];

		void load_all_entites() {
			using namespace Textures;
			entity_textures[(int)Entity::TEST].loadFromFile("Textures/testentity.png");
		}

		void load_all_tile_sheets() {

		}
	}
	
	void init() {
		if (!inited) {
			load_all_entites();
			load_all_tile_sheets();
			inited = true;
		}
	}

	const sf::Texture& get_entity_texture(Textures::Entity e) {
		return entity_textures[(int)e];
	}
}

/*class TextureManager {
private:
	std::vector<sf::Texture> m_entity_texture;
	std::vector<sf::Texture> m_tile_spritesheets;

	static void init();
public:
	TextureManager() = default;

	const sf::Texture get_entity_texture(int i) const;
}; */