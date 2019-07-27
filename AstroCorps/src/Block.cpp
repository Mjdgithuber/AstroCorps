#include "Block.h"
#include "Player.h"

// define static texture array
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

bool Block::colliding(const sf::Sprite& s1, const sf::Sprite& s2) {
	const sf::FloatRect& f1 = s1.getGlobalBounds();
	const sf::FloatRect& f2 = s2.getGlobalBounds();
	return f2.left <= f1.left + f1.width  && f2.left >= f1.left && 
		   f2.top  <= f1.top  + f1.height && f2.top  >= f1.top;
}

void Block::getPlayerCollision() {
	sf::Vector2f stoppedMovement = sf::Vector2f(0, 0);
	sf::Vector2f playerPosition = player.getPosition();
	sf::Vector2f blockPosition = getPosition();

	if (colliding(player, *this)) {
		player.stopPlayer();
	}
}
