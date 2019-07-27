#include "Block.h"
#include "Asteroid.h"

#include <thread>
#include <chrono>

void Asteroid::makeBlock(int x, int y) {
	blocks.emplace_back(x, y);
}


Asteroid::Asteroid(int x, int y, int radius) {
	asteroidX = x;
	asteroidY = y;
	for (int r = -radius; r < radius; r++) {
		for (int c = -radius; c < radius; c++) {
			if (getDistance((float) r, (float) c) < radius) {
				makeBlock(x - (BLOCK_SIZE / 2) + (c * BLOCK_SIZE), (y - (BLOCK_SIZE / 2) + (r * BLOCK_SIZE)));
			}
		}
	}
}


void Asteroid::chekCollision(Player& player) {
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].getPlayerCollision(player);
	}
}

void Asteroid::draw(sf::RenderWindow& window) {
	for (int d = 0; d < blocks.size(); d++) {
		window.draw(blocks[d]);
		//if (((blocks[d]..getPosition().x >= window.getView().getCenter().x - 165) && (blocks[d].object.getPosition().x <= window.getView().getCenter().x + 150)) && ((blocks[d].object.getPosition().y >= window.getView().getCenter().y - 165) && (blocks[d].object.getPosition().y <= window.getView().getCenter().y + 150)))
		
	}
}

void Asteroid::modifyPlayerGravity(Player& player) {
	// get the width and height of the player
	float width = player.getGlobalBounds().width;
	float height = player.getGlobalBounds().height;

	// gets the radius from the center of the player to the center of the astroid
	float radius = getDistance((float) asteroidX, player.getPosition().x + width / 2.0f, (float)asteroidY, player.getPosition().y + height / 2.0f);


	// calculates the force of gravity on player based on radius and asteroid size
	float force = (blocks.size() / std::pow(radius, 2)) * 20;

	float deltaX = asteroidX - (player.getPosition().x + width / 2);
	float deltaY = asteroidY - (player.getPosition().y + height / 2);

	//double xDistance = getDistance(player.playerSprite.getPosition().x + 7.5, asteroidX);
	//double yDistance = getDistance(player.playerSprite.getPosition().y + 15, asteroidY);

	//int modifierX = (player.playerSprite.getPosition().x > asteroidX) ? -1 : 1;
	//int modifierY = (player.playerSprite.getPosition().y > asteroidY) ? -1 : 1;
	player.acceleration += sf::Vector2f((force * (deltaX / radius)), (force * (deltaY / radius)));
}

float Asteroid::getDistance(float x, float y) {
	return std::sqrt((x * x) + (y*y));
}

float Asteroid::getDistance(float x1, float x2, float y1, float y2) {
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}