#include "Block.h"
#include "Player.h"
#include "Util.h"

// define static texture array
sf::Texture Block::m_block_textures[3];

Block::Block(int x, int y) {
	setPosition((float) x, (float) y);
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
	//std::cout << "Femma: " << getGlobalBounds().height << "\n";
}

bool Block::getPlayerCollision(Player& player) {
	sf::Vector2f stoppedMovement = sf::Vector2f(0, 0);
	sf::Vector2f playerPosition = player.getPosition();
	sf::Vector2f blockPosition = getPosition();

	return util::colliding(player, *this);
}
