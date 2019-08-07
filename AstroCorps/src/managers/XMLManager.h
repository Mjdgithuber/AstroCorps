#ifndef __XML__MANAGER__H__
#define __XML__MANAGER__H__

#include <string>

#include "..\xml\tinyxml2.h"
#include "..\tiles\TilePackage.h"

namespace XML {

	Tiles::TilePackage* load_map(const char* map_filepath);

}

#endif