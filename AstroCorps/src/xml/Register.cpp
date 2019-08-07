#include <vector>

#include "Register.h"
#include "..\util\Util.h"
#include "..\managers\XMLManager.h"

namespace Register {
	// anonymous namespace to provide static encapsulation
	namespace {
		std::vector<Util::Point> tilesheet_locations;
	}

	void init() {
		XML::load_tile_register(tilesheet_locations, "assets/register/register.xml");
	}

	const Util::Point& get_tilesheet_location(unsigned int reg_num) {
		return tilesheet_locations[reg_num];
	}
}