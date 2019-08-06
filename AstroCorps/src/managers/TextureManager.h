#ifndef __TEXTURE__MANAGER__H__
#define __TEXTURE__MANAGER__H__

#include <SFML/Graphics.hpp>

namespace Textures {
	enum class Entity {
		TEST,
		CARDINALITY
	};

	enum class TileSheet {
		TEST,
		MASTER_TILE_SHEET,
		CARDINALITY
	};
}

namespace TextureManager {
	void init();
	const sf::Texture& get_entity_texture(Textures::Entity i);
}

/*class TextureManager {
private:
	std::vector<sf::Texture> m_entity_texture;
	std::vector<sf::Texture> m_tile_spritesheets;

	void init();
public:
	TextureManager() = default;

	const sf::Texture get_entity_texture(int i) const;
}; */

#endif