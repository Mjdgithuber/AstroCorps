#ifndef __COMPONENT__H__
#define __COMPONENT__H__

#include <SFML/Graphics.hpp>

class Component {
public:
	enum Flag { NIL, UPDATE_POS };

	virtual ~Component() = default;

	virtual Flag update(const sf::Time& delta_time) = 0;
};

#endif