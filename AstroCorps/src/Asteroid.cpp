#include "Block.h"
#include "Asteroid.h"

#include <thread>
#include <chrono>

void Asteroid::makeBlock(int x, int y, Player& player) {
	blocks.emplace_back(x, y, player);
}


Asteroid::Asteroid(int x, int y, int radius, Player& player) {
	asteroidX = x;
	asteroidY = y;
	for (int r = -radius; r < radius; r++) {
		for (int c = -radius; c < radius; c++) {
			if (getDistance(r, c) < radius) {
				makeBlock(x - (BLOCK_SIZE / 2) + (c * BLOCK_SIZE), (y - (BLOCK_SIZE / 2) + (r * BLOCK_SIZE)), player);
			}
		}
	}
}


void Asteroid::getPlayerCollision() {
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].getPlayerCollision();
	}
}

void Asteroid::draw(sf::RenderWindow& window) {
	for (int d = 0; d < blocks.size(); d++) {

		//if (((blocks[d]..getPosition().x >= window.getView().getCenter().x - 165) && (blocks[d].object.getPosition().x <= window.getView().getCenter().x + 150)) && ((blocks[d].object.getPosition().y >= window.getView().getCenter().y - 165) && (blocks[d].object.getPosition().y <= window.getView().getCenter().y + 150)))
		window.draw(blocks[d]);
	}
}

void Asteroid::modifyPlayerGravity(Player& player) {
	float width = player.getGlobalBounds().width;
	float height = player.getGlobalBounds().height;

	double radius = getDistance(asteroidX, player.getPosition().x + width / 2, asteroidY, player.getPosition().y + height / 2);
	double force = (blocks.size() / std::pow(radius, 2)) * 10;

	double deltaX = asteroidX - (player.getPosition().x + width / 2);
	double deltaY = asteroidY - (player.getPosition().y + height / 2);

	//double xDistance = getDistance(player.playerSprite.getPosition().x + 7.5, asteroidX);
	//double yDistance = getDistance(player.playerSprite.getPosition().y + 15, asteroidY);

	//int modifierX = (player.playerSprite.getPosition().x > asteroidX) ? -1 : 1;
	//int modifierY = (player.playerSprite.getPosition().y > asteroidY) ? -1 : 1;
	player.acceleration += sf::Vector2f((force * (deltaX / radius)), (force * (deltaY / radius)));
}

double Asteroid::getDistance(int x, int y) {
	return std::sqrt((x * x) + (y*y));
}

double Asteroid::getDistance(int x1, int x2, int y1, int y2) {
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}