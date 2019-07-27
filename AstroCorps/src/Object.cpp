#include "Object.h"

void Object::drawObject(sf::RenderWindow& window, int x, int y) {
	object.setPosition(sf::Vector2f(x, y));
	window.draw(object);
}