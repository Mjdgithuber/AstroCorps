#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <SFML/Graphics.hpp>

#include "Player.h"


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

	Block(int x, int y);

	void init_block();

	bool getPlayerCollision(Player& player);
};



#endif