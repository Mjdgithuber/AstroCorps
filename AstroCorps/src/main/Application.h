#ifndef __APPLICATION__H__
#define __APPLICATION__H__

namespace Application {
	void start_application(unsigned int unscaled_tile_size, float scale = 1.f);
	float get_scale();
	unsigned int get_unscaled_tile_size();
	unsigned int get_scaled_tile_size();
}

#endif