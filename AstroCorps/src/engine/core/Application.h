#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include <string>

#include "lua_interface/user_types/tile_map/TileMap.h"

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
	void load_tile_map(Lua::TileMap* new_tile_map);

	////////////////////////////////////////////////////////////
	/// Stops the application as soon as possible. This flag
	/// is checked multiple times through out the application
	/// cycle to ensure fast responce time. NOTE: This is only
	/// to be used in the case of a fatal error in the game's
	/// execution
	////////////////////////////////////////////////////////////
	void signal_abort(const std::string& reason);
}

#endif