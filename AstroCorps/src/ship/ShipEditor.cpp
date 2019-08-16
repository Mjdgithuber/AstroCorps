#include "ShipEditor.h"

namespace ShipEditor {
	/* Anon namespace for private defintions */
	namespace {
		struct Unit {
			unsigned int m_tile_x, m_tile_y;
			Tiles::OldTile* m_tile;
			
			/* Constructors */
			Unit(unsigned int tile_x, unsigned int tile_y)
				: Unit(tile_x, tile_y, nullptr) {}

			Unit(unsigned int tile_x, unsigned int tile_y, Tiles::OldTile* tile)
				: m_tile_x(tile_x), m_tile_y(tile_y), m_tile(tile) {}
		};

		/* Anon Varibles */
		bool is_open = false;
		std::vector<Unit> units;
	}

	bool is_editor_open() {
		return is_open;
	}

	bool open_editor(const Tiles::OldTileMap& tm) {
		if (is_open) return false;

		for (unsigned int row = 0; row < tm.get_rows(); row++) {
			for (unsigned int col = 0; col < tm.get_cols(); col++) {

			}
		}

		return true;
	}

	bool close_editor() {
		if (!is_open) return false;

		return true;
	}

	bool output_to_tilemap(Tiles::OldTileMap& tm) {
		if (is_open) return false;

		return true;
	}

	bool save_editor_to_file(const std::string& filename) {
		if (is_open) return false;

		return true;
	}
}