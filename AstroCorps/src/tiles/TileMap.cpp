#include <iostream>
#include <fstream>

#include "TileMap.h"

namespace Tiles {

	TileMap::TileMap(const std::string& mapsheet, unsigned int rows, unsigned int cols, float scale)
		: m_spritesheet_rows(rows), m_spritesheet_cols(cols), m_rows(0), m_cols(0), m_scale(scale), m_bordered(false) {

		m_mapsheet.loadFromFile(mapsheet);
		//m_mapsheet.setSmooth(true);
		m_tile_size = m_mapsheet.getSize().x / cols; // size is assumed to be square
	}

	void TileMap::draw_map(sf::RenderWindow& window) {
		for (unsigned int row = 0; row < m_rows; row++) {
			for (unsigned int col = 0; col < m_cols; col++) {
				window.draw(m_tiles[row][col]);
			}
		}

		// draw entites
		for (MovableEntity& e : m_enties)
			e.draw(window);
	}

	void TileMap::load_map(const std::string& map_file) {
		std::ifstream file(map_file);

		file >> m_rows >> m_cols;
		//std::cout << "Rows: " << m_rows << " Cols: " << m_cols << "\n";

		m_tiles.reserve(m_rows);

		for (unsigned int r = 0; r < m_rows; r++) {
			std::vector<Tile> tile_col;
			tile_col.reserve(m_cols);
			for (unsigned int c = 0; c < m_cols; c++) {
				int tile_no;
				file >> tile_no;

				Tile t(BLOCKED, Point(tile_no, 0));
				t.setTexture(m_mapsheet);
				t.setTextureRect(sf::IntRect(m_tile_size * (tile_no * 2 + (m_bordered ? 1 : 0)), 0, m_tile_size, m_tile_size));
				t.setScale(m_scale, m_scale);
				t.setPosition(c * m_tile_size * m_scale, r * m_tile_size * m_scale);
				tile_col.push_back(t); // move semantics please
			}
			m_tiles.push_back(std::move(tile_col));
		}
	}

	void TileMap::update(const sf::Time& delta_time) {
		for (MovableEntity& e : m_enties)
			e.update(delta_time);
	}

	void TileMap::add_entity(const MovableEntity& e) {
		m_enties.push_back(e);
		m_enties[0].move_horizontally(false, .5f);
	}

	void TileMap::set_tile_textures() {
		std::cout << "Setting the tile textures!\n";
		for (unsigned int r = 0; r < m_rows; r++) {
			for (unsigned int c = 0; c < m_cols; c++) {
				Tile& t = m_tiles[r][c];
				t.setTextureRect(
					sf::IntRect(m_tile_size * (t.get_texture_location().x * 2 + (m_bordered ? 1 : 0)),
						0, m_tile_size, m_tile_size));
			}
		}
	}

	void TileMap::toggle_borders() {
		std::cout << "Toggling Borders!\n";
		m_bordered = !m_bordered;
		set_tile_textures();
	}

	Tile& TileMap::get_tile(unsigned int row, unsigned int col) { return m_tiles[row][col]; }

	unsigned int TileMap::get_rows() const { return m_rows; }
	unsigned int TileMap::get_cols() const { return m_cols; }

}