#include <iostream>
#include <fstream>

#include "TileMap.h"
#include "..\util\Util.h"
#include "..\xml\Register.h"
#include "..\managers\TextureManager.h"
#include "..\managers\XMLManager.h"
#include "..\tiles\TilePackage.h"

namespace Tiles {

	/* ============== Constructors and Destructors =============== */

	/* Makes a new empty tile map */
	TileMap::TileMap(float scale)
		: m_rows(0), m_cols(0), m_scale(scale), m_bordered(false) {
		
		// TODO this needs to be fixed to use application size thingy
		m_tile_size = TextureManager::get_tile_sheet(Textures::TileSheet::MASTER_TILE_SHEET).getSize().x / 10; // size is assumed to be square
	}

	/* ======================== Functions ======================== */

	/* Will draw all of the tiles and entities*/
	void TileMap::draw_map(sf::RenderWindow& window) {
		// draw tiles
		for (unsigned int row = 0; row < m_rows; row++) {
			for (unsigned int col = 0; col < m_cols; col++)
				window.draw(m_tiles[row][col]);
		}

		// draw entites
		for (Entity* e : m_enties)
			(*e).draw(window);
	}

	/* Will load a map file into the tile map */
	void TileMap::load_map(const char* map_file) {
		// load map from xml file passed in
		Tiles::TilePackage* tp = XML::load_map(map_file);

		// make sure tiles is empty
		m_tiles.clear();

		// save size data
		m_rows = tp->get_rows();
		m_cols = tp->get_cols();

		// get tile sheet ref for convenience
		const sf::Texture& tile_sheet = TextureManager::get_tile_sheet(Textures::TileSheet::MASTER_TILE_SHEET);

		// load the tile map
		m_tiles.reserve(m_rows);

		for (unsigned int r = 0; r < m_rows; r++) {
			std::vector<Tile> tile_col;
			tile_col.reserve(m_cols);
			for (unsigned int c = 0; c < m_cols; c++) {
				// get tile info from packet
				unsigned int reg_num = tp->get_register_num(c, r);
				unsigned int mod_num = tp->get_modifier_register_num(c, r);
				const std::string& script = tp->get_script(c, r);

				// get register information for texture location
				const Util::Point& location = Register::get_tilesheet_location(reg_num);

				// make a new tile
				Tile t(reg_num, mod_num, script);
				t.setTexture(tile_sheet);
				t.setTextureRect(sf::IntRect(m_tile_size * (location.x * 2 + (m_bordered ? 1 : 0)), 0, m_tile_size, m_tile_size));
				t.setScale(m_scale, m_scale);
				t.setPosition(c * m_tile_size * m_scale, r * m_tile_size * m_scale);
				tile_col.push_back(t); // move semantics please
			}
			m_tiles.push_back(std::move(tile_col));
		}

		// free the tile package
		delete tp;
	}

	/* As of now updates the entities */
	void TileMap::update(const sf::Time& delta_time) {
		for (Entity* e : m_enties)
			(*e).update(delta_time);
	}

	/* Adds an entity to the tile map */
	void TileMap::add_entity(Entity* e) {
		m_enties.push_back(e);
	}

	/* Will reset all of the tile textures */
	void TileMap::set_tile_textures() {
		std::cout << "Setting the tile textures!\n";

		// loop though each tile by row
		for (unsigned int r = 0; r < m_rows; r++) {
			for (unsigned int c = 0; c < m_cols; c++) {
				// get the tile
				Tile& t = m_tiles[r][c];

				// get it's texture location
				const Util::Point& location = Register::get_tilesheet_location(t.get_register_number());

				// set the tile's texture
				t.setTextureRect(
					sf::IntRect(m_tile_size * (location.x * 2 + (m_bordered ? 1 : 0)),
					0, m_tile_size, m_tile_size));
			}
		}
	}

	/* Toggles the m_bordered bool and resets the textures */
	void TileMap::toggle_borders() {
		std::cout << "Toggling Borders!\n";
		m_bordered = !m_bordered;
		set_tile_textures();
	}

	/* ========================= Getters ========================= */

	Tile& TileMap::get_tile(unsigned int row, unsigned int col) { return m_tiles[row][col]; }
	const Tile& TileMap::get_tile(unsigned int row, unsigned int col) const { return m_tiles[row][col]; }

	unsigned int TileMap::get_rows() const { return m_rows; }
	unsigned int TileMap::get_cols() const { return m_cols; }

}