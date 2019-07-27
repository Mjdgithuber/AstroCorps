#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <vector>

#include <SFML/Graphics.hpp>

#include "Block.h"

class Asteroid {
private:
	sf::Texture m_block_textures[3];
public:
	const int BLOCK_SIZE = 15;
	std::vector<Block> blocks;

	void makeBlock(int x, int y);
	int asteroidX;
	int asteroidY;

	Asteroid(int x, int y, int radius);


	void chekCollision(Player& player);

	void draw(sf::RenderWindow& window);

	void modifyPlayerGravity(Player& player);

	float getDistance(float x, float y);
	float getDistance(float x1, float x2, float y1, float y2);
};



#endif