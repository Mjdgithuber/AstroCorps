#ifndef __UPDATABLE_H__
#define __UPDATABLE_H__

#include <SFML/Graphics.hpp>

class Updatable {
public:
	/* Interface functions */
	virtual void update(sf::Time delta_time) = 0;
};

#endif
