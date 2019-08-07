#ifndef __XML__MANAGER__H__
#define __XML__MANAGER__H__

#include <vector>

#include "..\xml\tinyxml2.h"
#include "..\tiles\TilePackage.h"
#include "..\util\Util.h"

namespace XML {

	Tiles::TilePackage* load_map(const char* map_filepath);
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path);

}

#endif