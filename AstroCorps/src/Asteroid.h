#ifndef ASTEROID__H
#define ASTEROID__H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.h"
class Asteroid {
private:
	sf::Texture m_block_textures[3];
public:
	void load_block_textures();

	const int BLOCK_SIZE = 15;
	sf::Texture femma;
	std::vector<Block> blocks;

	void makeBlock(int x, int y, Player& player);
	int asteroidX;
	int asteroidY;

	Asteroid(int x, int y, int radius, Player& player);


	void getPlayerCollision();

	void draw(sf::RenderWindow& window);

	void modifyPlayerGravity(Player& player);

	double getDistance(int x, int y);
	double getDistance(int x1, int x2, int y1, int y2);
};



#endif