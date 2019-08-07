#ifndef __REGISTER__H__
#define __REGISTER__H__

#include "..\util\Util.h"

namespace Register {
	void init();

	const Util::Point& get_tilesheet_location(unsigned int reg_num);
}

#endif