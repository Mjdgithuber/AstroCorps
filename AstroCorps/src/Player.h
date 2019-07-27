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

	bool isRotating = false;
	int frames = 0;

	int rotationInt;

	int generalOxygen = 4000;
	int oxygenAmount = 2000;
	int tempOxygenAmount = 2000;

	Rotation rotation;
	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;
	bool down = false;
	bool jetPack = false;
	sf::RectangleShape oxygenBar;
	sf::RectangleShape tempOxygenBar;

	std::vector<sf::RectangleShape> inventoryBoxes;



	sf::Texture playerTex;
	sf::Vector2f movement;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f gravity;

	Player();

	void checkRotation();

	void update(sf::RenderWindow& window);

	void stopPlayer();

	void draw(sf::RenderWindow& window);

	void drawInventory(sf::RenderWindow& window);

};

#endif