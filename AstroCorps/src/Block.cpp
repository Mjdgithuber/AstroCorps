#include "Block.h"
#include "Player.h"

sf::Texture Block::m_block_textures[3];

Block::Block(int x, int y, Player& p1) : player(p1) {
	setPosition(x, y);
	init_block();
}

void Block::load_block_textures() {
	m_block_textures[ASTRO_ROCK].loadFromFile("Textures/Blocks/AstroRock.png");
	m_block_textures[TIN].loadFromFile("Textures/Blocks/Tin.png");
	m_block_textures[COPPER].loadFromFile("Textures/Blocks/Copper.png");
}

void Block::init_block() {
	BLOCK_TYPE b;
	std::uniform_int_distribution<int> generator(0, 201);
	std::random_device randDevice;
	if (generator(randDevice) == 0)
		b = COPPER;
	else if (generator(randDevice) < 15)
		b = TIN;
	else
		b = ASTRO_ROCK;
	
	setTexture(m_block_textures[b], true);
}

void Block::getPlayerCollision() {
	sf::Vector2f stoppedMovement = sf::Vector2f(0, 0);
	sf::Vector2f playerPosition = player.playerSprite.getPosition();
	sf::Vector2f blockPosition = getPosition();

	if (player.rotationInt == 0) {
		if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y + 0))) {
			player.stopPlayer();
		}
		else if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
			player.stopPlayer();
		}
		//right & left
		if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 0)) && ((playerPosition.y + 30 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
			player.stopPlayer();
		}
		else if (((playerPosition.x + 0 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 30 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
			player.stopPlayer();

		}
	}
	else if (player.rotationInt == 2) {
		//bottom & top
		if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 30 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
			player.stopPlayer();
		}

	}
	if (player.rotationInt == 1) {
		//bottom & top
		if (((playerPosition.x + 30 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
			player.stopPlayer();
		}
	}
	else if (player.rotationInt == 3) {
		//bottom & top
		if (((playerPosition.x + 30 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y))) {
			player.stopPlayer();
		}
	}

	//bottom & top
	if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y + 0))) {
		player.stopPlayer();
	}
	else if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 15 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
		player.stopPlayer();
	}
	//right & left
	if (((playerPosition.x + 15 > blockPosition.x) && (playerPosition.x < blockPosition.x + 0)) && ((playerPosition.y + 30 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
		player.stopPlayer();
	}
	else if (((playerPosition.x + 0 > blockPosition.x) && (playerPosition.x < blockPosition.x + 15)) && ((playerPosition.y + 30 > blockPosition.y) && (playerPosition.y < blockPosition.y + 15))) {
		player.stopPlayer();

	}
}
