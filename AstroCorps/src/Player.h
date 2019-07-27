#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

class Player : public sf::Sprite {
public:
	enum Rotation {
		NORTH, EAST, SOUTH, WEST
	};

	int rotationInt;

	Rotation rotation;
	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;
	bool down = false;
	bool jetPack = false;
	sf::RectangleShape oxygenBar;
	sf::RectangleShape tempOxygenBar;

	sf::Texture playerTex;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	Player();

	void checkRotation();

	void update(sf::RenderWindow& window);

	void stopPlayer();

	void draw(sf::RenderWindow& window);

};

#endif