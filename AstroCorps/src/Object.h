#ifndef OBJECT__H
#define OBJECT__H

#include <SFML/Graphics.hpp>


class Object {
public:

	sf::Sprite object;
	void drawObject(sf::RenderWindow& window, int x, int y);

};


#endif
