#ifndef __MAP__PARSER__H__
#define __MAP__PARSER__H__

#include "XMLUtils.h"
#include "tiles/TilePackage.h"

namespace XML {

	////////////////////////////////////////////////////////////
	/// This function returns a TilePackage which has all the 
	/// information about the map that was passed in. NOTE:
	/// this function returns a pointer that MUST be deleted
	/// (freed) otherwise it will leak which can be very 
	/// significant depending on how big the map file is!
	////////////////////////////////////////////////////////////
	Tiles::TilePackage* load_map(const char* map_filepath);

}

#endif