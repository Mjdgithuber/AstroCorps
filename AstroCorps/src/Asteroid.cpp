#include "Block.h"
#include "Asteroid.h"

#include <thread>
#include <chrono>

void Asteroid::makeBlock(int x, int y, Player& player) {
	//Block block(x, y, player);
	//std::cout << "DF\n";
	blocks.emplace_back(x, y, player);
	//blocks.push_back(Block(x, y, player));
	//blocks[blocks.size() - 1].init_block();
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//blocks.push_back(block);
}


Asteroid::Asteroid(int x, int y, int radius, Player& player) {
	femma.loadFromFile("Textures/Block.png");
	asteroidX = x;
	asteroidY = y;
	int xx = 0;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	for (int r = -radius; r < radius; r++) {
		for (int c = -radius; c < radius; c++) {
			if (getDistance(r, c) < radius) {
				makeBlock(x - (BLOCK_SIZE / 2) + (c * BLOCK_SIZE), (y - (BLOCK_SIZE / 2) + (r * BLOCK_SIZE)), player);
				//std::cout << blocks.size() - 1 << "\n";
				blocks[xx++ ].init_block(femma);
			}
		}
	}

	for (int i = 0; i < blocks.size(); i++) {
		//std::cout << "Inited: " << blocks[i].inited << "\n";
		//blocks[i].init_block();
	}
}


void Asteroid::getPlayerCollision() {
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].getPlayerCollision();
	}
}

void Asteroid::draw(sf::RenderWindow& window) {
	for (int d = 0; d < blocks.size(); d++) {

		//if (((blocks[d].object.getPosition().x >= window.getView().getCenter().x - 165) && (blocks[d].object.getPosition().x <= window.getView().getCenter().x + 150)) && ((blocks[d].object.getPosition().y >= window.getView().getCenter().y - 165) && (blocks[d].object.getPosition().y <= window.getView().getCenter().y + 150)))
		window.draw(blocks[d]);
		//blocks[d].draw(window);
	}
}

void Asteroid::modifyPlayerGravity(Player& player) {
	double radius = getDistance(asteroidX, player.playerSprite.getPosition().x + 7.5, asteroidY, player.playerSprite.getPosition().y + 15);
	double force = (blocks.size() / std::pow(radius, 2)) * 10;

	double deltaX = asteroidX - (player.playerSprite.getPosition().x + 7.5);
	double deltaY = asteroidY - (player.playerSprite.getPosition().y + 15);

	//double xDistance = getDistance(player.playerSprite.getPosition().x + 7.5, asteroidX);
	//double yDistance = getDistance(player.playerSprite.getPosition().y + 15, asteroidY);

	//int modifierX = (player.playerSprite.getPosition().x > asteroidX) ? -1 : 1;
	//int modifierY = (player.playerSprite.getPosition().y > asteroidY) ? -1 : 1;
	player.gravity = sf::Vector2f((force * (deltaX / radius)), (force * (deltaY / radius)));
	player.acceleration += player.gravity;
}

double Asteroid::getDistance(int x, int y) {
	return std::sqrt((x * x) + (y*y));
}

double Asteroid:: getDistance(int x1, int x2, int y1, int y2) {
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}