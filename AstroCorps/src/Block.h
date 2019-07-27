#ifndef BLOCK__H
#define BLOCK__H

#include "Player.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

class Block : public sf::Sprite {
private:
	static sf::Texture m_block_textures[3];

public:
	enum BLOCK_TYPE {
		ASTRO_ROCK,
		COPPER,
		TIN
	};

	static void load_block_textures();

	Player& player;

	Block(int x, int y, Player& p1);

	void init_block(sf::Texture& text);

	void getPlayerCollision();
};



#endif