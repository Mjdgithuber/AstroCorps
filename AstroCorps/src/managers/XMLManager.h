#ifndef __XML__MANAGER__H__
#define __XML__MANAGER__H__

#include <string>

#include "..\xml\tinyxml2.h"
#include "..\tiles\TileMap.h"

namespace XML {

	bool load_map_data(const char* map_filepath);

}

#endif