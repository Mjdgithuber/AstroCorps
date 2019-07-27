#include <iostream>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include "Asteroid.h"
#include "Player.h"

#define DEBUG 0

std::vector< sf::Sprite > oxygens;

int wait = 0;
int waitCounter = 100;

void generateOxygen(std::vector<Asteroid>& asteroids) {
	std::uniform_int_distribution<int> random(0, 1001);
	std::random_device randDevice;
	int x = random(randDevice);
	int y = random(randDevice);
	if (wait >= waitCounter) {
		sf::Sprite oxygen;
		
		oxygen.setPosition(x, y);

		oxygens.push_back(oxygen);

		waitCounter++;
		wait = 0;

	}
	else {
		wait++;
	}
}

void collectOxygen(Player& player) {
	for (int i = 0; i < oxygens.size(); i++) {
		if (((player.getPosition().x  < oxygens[i].getPosition().x + 15) && (player.getPosition().x + player.getGlobalBounds().width > oxygens[i].getPosition().x )) && ((player.getPosition().y < oxygens[i].getPosition().y + 15) && (player.getPosition().y + player.getGlobalBounds().height > oxygens[i].getPosition().y))) {
			oxygens.erase(oxygens.begin() + i);
			if (player.oxygenAmount < 1500) {
				player.oxygenAmount += 500;
			}
			else {
				player.oxygenAmount = 2000;
			}
			
		}
	}
	player.generalOxygen = player.tempOxygenAmount + player.oxygenAmount;
}

void drawOxygen(sf::RenderWindow& window) {
	for (int i = 0; i < oxygens.size(); i++) {
		sf::Texture oTex;
		oTex.loadFromFile("Textures/Oxygen.png");
		oxygens[i].setTexture(oTex);
		window.draw(oxygens[i]);
	}
}

int main() {
	// load all of the block textures
	Block::load_block_textures();

	// make a new window
	sf::RenderWindow window(sf::VideoMode(600, 600), "Astro Corps");
	window.setFramerateLimit(60);

	sf::Texture backTex;
	backTex.loadFromFile("Textures/Background.png");

	//Sprites
	sf::Sprite backSprite;
	backSprite.setTexture(backTex);

	//Camera
	sf::View camera(sf::FloatRect(50, 50, 150, 150));
	camera.setSize(300, 300);
	camera.setCenter(150, 150);
	window.setView(camera);


	sf::Clock timer;

	sf::Sprite deathScreen;
	sf::Texture deathTex;
	deathTex.loadFromFile("Textures/DeathScreen.png");
	deathScreen.setTexture(deathTex);

	Player player;
	player.moveLeft = false;
	player.moveRight = false;
	player.jump = false;
	player.setPosition(500, 150);
	std::vector<Asteroid> asteroids;

	sf::Clock profiler;

	for (int i = 0; i < 1; i++)
		asteroids.emplace_back(150, 150, 15, player);

	while (window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::D)
					player.moveRight = true;
				if (event.key.code == sf::Keyboard::A)
					player.moveLeft = true;
				if (event.key.code == sf::Keyboard::W)
					player.jump = true;
				if (event.key.code == sf::Keyboard::S)
					player.down = true;
				if (event.key.code == sf::Keyboard::Space)
					player.jetPack = true;
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::D) 
					player.moveRight = false;
				if (event.key.code == sf::Keyboard::A)
					player.moveLeft = false;
				if (event.key.code == sf::Keyboard::W)
					player.jump = false;
				if (event.key.code == sf::Keyboard::S)
					player.down = false;
				if (event.key.code == sf::Keyboard::Space)
					player.jetPack = false;
			}
		}

		//std::cout << player.playerSprite.getGlobalBounds().left << "\n";

		profiler.restart();
		for (int i = 0; i < asteroids.size(); i++)
			asteroids[i].modifyPlayerGravity(player);
		if(DEBUG) std::cout << "Modify Player Gravity: " << profiler.getElapsedTime().asSeconds() << "\n";


		profiler.restart();
		player.checkRotation();
		if (DEBUG) std::cout << "Check Rotation:        " << profiler.getElapsedTime().asSeconds() << "\n";


		profiler.restart();
		for (int i = 0; i < asteroids.size(); i++)
			asteroids[i].getPlayerCollision();
		if (DEBUG) std::cout << "Player Collision:      " << profiler.getElapsedTime().asSeconds() << "\n";
		

		window.clear();

		profiler.restart();
		player.update(window);
		if (DEBUG) std::cout << "Player Update:         " << profiler.getElapsedTime().asSeconds() << "\n";



		window.draw(backSprite);			

		profiler.restart();
		for (int i = 0; i < asteroids.size(); i++)
			asteroids[i].draw(window);
		if (DEBUG) std::cout << "Draw Astro:            " << profiler.getElapsedTime().asSeconds() << "\n";

		profiler.restart();
		player.draw(window);
		if (DEBUG) std::cout << "Draw Player:           " << profiler.getElapsedTime().asSeconds() << "\n";
		if (DEBUG) std::cout << "---------------------------------------------------------------------------\n";

		window.display();
	}
}

