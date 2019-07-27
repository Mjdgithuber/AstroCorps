#ifndef PLAYER__H
#define PLAYER__H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

#include "Object.h"
#include "Drill.h"

class Player {
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

	std::vector<Object> inventory;
	std::vector<sf::RectangleShape> inventoryBoxes;



	sf::Texture playerTex;
	sf::Sprite playerSprite;
	sf::Vector2f movement;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f gravity;

	Player();

	void checkRotation();

	void update(sf::RenderWindow& window);

	void stopPlayer();

	void setPosition(int x, int y);

	void draw(sf::RenderWindow& window);

	void drawInventory(sf::RenderWindow& window);

};

#endif