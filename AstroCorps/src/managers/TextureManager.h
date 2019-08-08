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

////////////////////////////////////////////////////////////
/// The TextureManager namespace hold all of the important
/// Texture information that the game uses. This is to avoid
/// having multiple textures all throughout the program that
/// potentially are identical. It saves memory and execution
/// time!
////////////////////////////////////////////////////////////
namespace TextureManager {

	////////////////////////////////////////////////////////////
	/// Initializes the texture manager by loading all of the 
	/// various textures. There are two types of textures 
	/// Tile sheets, which are png's that hold multiple tile
	/// assets. Entity's are less defined, but typically consist
	/// of a single texture or a spritesheet.
	////////////////////////////////////////////////////////////
	void init();

	////////////////////////////////////////////////////////////
	/// Returns a reference to a given entity texture.
	/// Params:
	/// Textures::Entity e - The entity you want the texture of
	////////////////////////////////////////////////////////////
	const sf::Texture& get_entity_texture(Textures::Entity e);

	////////////////////////////////////////////////////////////
	/// Returns a reference to a given tile sheet texture.
	/// Params:
	/// Textures::TileSheet ts - The tilesheet you want the texture of
	////////////////////////////////////////////////////////////
	const sf::Texture& get_tile_sheet(Textures::TileSheet ts);
}

#endif