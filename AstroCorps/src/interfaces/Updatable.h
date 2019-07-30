#ifndef __UPDATABLE__H__
#define __UPDATABLE__H__

#include <SFML/Graphics.hpp>

class Updatable {
public:
	/* Interface functions */
	virtual void update(const sf::Time& delta_time) = 0;
};

#endif
