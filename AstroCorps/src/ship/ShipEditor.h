#ifndef __SHIP__EDITOR__H__
#define __SHIP__EDITOR__H__

#include <vector>
#include <string>

#include "tiles\Tile.h"
#include "tiles\TileMap.h"

namespace ShipEditor {
	bool is_editor_open();

	bool open_editor(const Tiles::TileMap& tm);
	bool close_editor();

	bool output_to_tilemap(Tiles::TileMap& tm);

	bool save_editor_to_file(const std::string& filename);
}

#endif