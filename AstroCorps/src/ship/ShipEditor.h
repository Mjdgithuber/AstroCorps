#ifndef __SHIP__EDITOR__H__
#define __SHIP__EDITOR__H__

#include <vector>
#include <string>

#include "tiles/OldTile.h"
#include "tiles/OldTileMap.h"

namespace ShipEditor {
	bool is_editor_open();

	bool open_editor(const Tiles::OldTileMap& tm);
	bool close_editor();

	bool output_to_tilemap(Tiles::OldTileMap& tm);

	bool save_editor_to_file(const std::string& filename);
}

#endif