#include "TimeDependent.h"

float TimeDependent::get_frame_adj(const sf::Time& delta_time) const {
	return delta_time.asSeconds() / EXPECTED_FRAME_TIME;
}