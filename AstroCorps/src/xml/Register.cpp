#include <vector>

#include "Register.h"
#include "..\util\Util.h"
#include "..\managers\XMLManager.h"

namespace Register {
	/* anonymous namespace to provide static encapsulation */
	namespace {
		bool inited = false;
		std::vector<Util::Point> tilesheet_locations;
	}

	/* Load the registry */
	void init() {
		if(!inited)
			XML::load_tile_register(tilesheet_locations, "assets/register/register.xml");
		inited = true;
	}

	/* Returns the location of the tile's texture */
	const Util::Point& get_tilesheet_location(unsigned int reg_num) {
		return tilesheet_locations[reg_num];
	}
}