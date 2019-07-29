#ifndef __TIME_DEPENDENT_H__
#define __TIME_DEPENDENT_H__

#include <SFML/Graphics.hpp>

class TimeDependent {
private:
	const float EXPECTED_FRAME_TIME = 1.f / 60.f;
protected:
	/* Helper functions */
	float get_frame_adj(const sf::Time& delta_time) const;
};

#endif
