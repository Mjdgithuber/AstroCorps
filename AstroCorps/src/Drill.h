#ifndef DRILL__H
#define DRILL__H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Drill : public Object {
public:

	int type;
	sf::Texture drillTex;

	Drill(int t);

	void draw(sf::RenderWindow& window);

};


#endif
