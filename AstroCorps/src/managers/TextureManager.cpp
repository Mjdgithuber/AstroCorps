#include "TextureManager.h"

namespace TextureManager {
	/* anonymous namespace to provide static encapsulation */
	namespace {
		using namespace Textures;

		/* varibles to store texture information */
		bool inited = false;
		sf::Texture entity_textures[(int)Textures::Entity::CARDINALITY];
		sf::Texture tile_sheets[(int)Textures::TileSheet::CARDINALITY];

		/* loads each of the entities into seperate blocks */
		void load_all_entites() {
			entity_textures[(int)Entity::TEST].loadFromFile("assets/textures/testentity.png");
		}

		/* loads each of the tilesheets into seperate blocks */
		void load_all_tilesheets() {
			tile_sheets[(int)TileSheet::MASTER_TILE_SHEET].loadFromFile("assets/spritesheets/mapsheet.png");
		}
	}
	
	void init() {
		// this should only ever happen once
		if (!inited) {
			// load all necessary textures
			load_all_entites();
			load_all_tilesheets();
			inited = true;
		}
	}

	/* Grabs the texture of the Entity (enum) passed in. This is
	   error proof as long as CARDINALITY isn't passed in. */
	const sf::Texture& get_entity_texture(Textures::Entity e) {
		return entity_textures[(int)e];
	}

	/* Grabs the texture of the TileSheet (enum) passed in. This is
	   error proof as long as CARDINALITY isn't passed in. */
	const sf::Texture& get_tile_sheet(Textures::TileSheet ts) {
		return tile_sheets[(int)ts];
	}
}