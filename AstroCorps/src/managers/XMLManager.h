#ifndef __XML__MANAGER__H__
#define __XML__MANAGER__H__

#include <vector>

#include "..\xml\tinyxml2.h"
#include "..\tiles\TilePackage.h"
#include "..\util\Util.h"

////////////////////////////////////////////////////////////
/// The XML namespace serves as an API to allow easy 
/// interfacing with the TinyXML2 library, which is now
/// included as a source (cpp) file for better debugging.
/// NO other file should use TinyXML2 directly
////////////////////////////////////////////////////////////
namespace XML {

	////////////////////////////////////////////////////////////
	/// This function returns a TilePackage which has all the 
	/// information about the map that was passed in. NOTE:
	/// this function returns a pointer that MUST be deleted
	/// (freed) otherwise it will leak which can be very 
	/// significant depending on how big the map file is!
	////////////////////////////////////////////////////////////
	Tiles::TilePackage* load_map(const char* map_filepath);

	////////////////////////////////////////////////////////////
	/// This will load the Tile part of the Registry file. The
	/// registry allows the map files to be appropriately loaded
	/// in a flexible manner.
	////////////////////////////////////////////////////////////
	bool load_tile_register(std::vector<Util::Point>& locations, const char* register_path);

}

#endif