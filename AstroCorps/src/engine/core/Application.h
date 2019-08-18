#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include "engine/main/tile_based/TileMap.h"

////////////////////////////////////////////////////////////
/// The application namespace holds all of the information
/// about the application. This is a namespace and not a 
/// class before there is no need to have more than one
/// application.
////////////////////////////////////////////////////////////
namespace Application {

	////////////////////////////////////////////////////////////
	/// This will both setup and star running the application.
	/// This method should be called directly by main and should
	/// one be called once.
	////////////////////////////////////////////////////////////
	void start_application(unsigned int unscaled_tile_size, float scale = 1.f);

	////////////////////////////////////////////////////////////
	/// This gets the tile scale for the entire game. NOTE: This 
	/// number cannot change during run-time.
	////////////////////////////////////////////////////////////
	float get_scale();

	////////////////////////////////////////////////////////////
	/// Gets the number of pixels per tile. This is unscaled and
	/// is guaranteed  to be the same for every tile
	////////////////////////////////////////////////////////////
	unsigned int get_unscaled_tile_size();

	////////////////////////////////////////////////////////////
	/// Gets the number of pixels per tile after being scaled. 
	/// This is guaranteed  to be the same for every tile
	////////////////////////////////////////////////////////////
	unsigned int get_scaled_tile_size();

	/* REGISTERED WITH LUA */
	void load_tile_map(TileMap* new_tile_map);
}

#endif