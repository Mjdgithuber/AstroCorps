#include <iostream>
#include <fstream>

#include "OldTileMap.h"
#include "xml/Register.h"
#include "managers/TextureManager.h"
#include "xml/parsers/MapParser.h"
#include "tiles/OldTilePackage.h"
#include "Core.h"

namespace Tiles {

	/* ============== Constructors and Destructors =============== */

	/* Makes a new empty tile map */
	OldTileMap::OldTileMap()
		: m_rows(0), m_cols(0), m_bordered(false) {}

	/* ======================== Functions ======================== */

	/* Will draw all of the tiles and entities*/
	void OldTileMap::draw_map(sf::RenderWindow& window) {
		// draw tiles
		for (unsigned int row = 0; row < m_rows; row++) {
			for (unsigned int col = 0; col < m_cols; col++)
				window.draw(m_tiles[row][col]);
		}

		// draw entites
		for (OldEntity* e : m_enties)
			(*e).draw(window);
	}

	/* Will load a map file into the tile map */
	void OldTileMap::load_map(const char* map_file) {
		// load map from xml file passed in
		Tiles::OldTilePackage* tp = XML::load_map(map_file, -1);

		// make sure tiles is empty
		m_tiles.clear();

		// save size data
		m_rows = tp->get_rows();
		m_cols = tp->get_cols();

		// get tile sheet ref for convenience
		const sf::Texture& tile_sheet = TextureManager::get_tile_sheet(Textures::TileSheet::MASTER_TILE_SHEET);

		// load the tile map
		m_tiles.reserve(m_rows);

		// global tile data
		float scale = OldApplication::get_scale();
		unsigned int tile_size = OldApplication::get_unscaled_tile_size();

		for (unsigned int r = 0; r < m_rows; r++) {
			std::vector<OldTile> tile_col;
			tile_col.reserve(m_cols);
			for (unsigned int c = 0; c < m_cols; c++) {
				// get tile info from packet
				unsigned int reg_num = tp->get_register_num(c, r);
				unsigned int mod_num = tp->get_modifier_register_num(c, r);
				const std::string& script = tp->get_script(c, r);

				// get register information for texture location
				const Util::Point& location = Register::get_tilesheet_location(reg_num);

				// make a new tile
				OldTile t(reg_num, mod_num, script);
				t.setTexture(tile_sheet);
				t.setTextureRect(sf::IntRect(tile_size * (location.x * 2 + (m_bordered ? 1 : 0)), 0, tile_size, tile_size));
				t.setScale(scale, scale);
				t.setPosition(c * tile_size * scale, r * tile_size * scale);
				tile_col.push_back(t); // move semantics please
			}
			m_tiles.push_back(std::move(tile_col));
		}

		// free the tile package
		delete tp;
	}

	/* As of now updates the entities */
	void OldTileMap::update(const sf::Time& delta_time) {
		for (OldEntity* e : m_enties)
			(*e).update(delta_time);
	}

	/* Adds an entity to the tile map */
	void OldTileMap::add_entity(OldEntity* e) {
		m_enties.push_back(e);
	}

	/* Will reset all of the tile textures */
	void OldTileMap::set_tile_textures() {
		LOG_TRACE("Setting the tile textures");

		// get tile size (to locate texture)
		unsigned int tile_size = OldApplication::get_unscaled_tile_size();

		// loop though each tile by row
		for (unsigned int r = 0; r < m_rows; r++) {
			for (unsigned int c = 0; c < m_cols; c++) {
				// get the tile
				OldTile& t = m_tiles[r][c];

				// get it's texture location
				const Util::Point& location = Register::get_tilesheet_location(t.get_register_number());

				// set the tile's texture
				t.setTextureRect(
					sf::IntRect(tile_size * (location.x * 2 + (m_bordered ? 1 : 0)),
					0, tile_size, tile_size));
			}
		}
	}

	/* Toggles the m_bordered bool and resets the textures */
	void OldTileMap::toggle_borders() {
		LOG_TRACE("Toggling Borders!");
		m_bordered = !m_bordered;
		set_tile_textures();
	}

	/* ========================= Getters ========================= */

	OldTile& OldTileMap::get_tile(unsigned int row, unsigned int col) { return m_tiles[row][col]; }
	const OldTile& OldTileMap::get_tile(unsigned int row, unsigned int col) const { return m_tiles[row][col]; }

	unsigned int OldTileMap::get_rows() const { return m_rows; }
	unsigned int OldTileMap::get_cols() const { return m_cols; }

}