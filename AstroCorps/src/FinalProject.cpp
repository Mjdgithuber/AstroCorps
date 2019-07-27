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
		
		oxygen.setPosition(x * 1.0f, y * 1.0f);

		oxygens.push_back(oxygen);

		waitCounter++;
		wait = 0;

	}
	else {
		wait++;
	}
}

void drawOxygen(sf::RenderWindow& window) {
	for (int i = 0; i < oxygens.size(); i++) {
		sf::Texture oTex;
		oTex.loadFromFile("Textures/Oxygen.png");
		oxygens[i].setTexture(oTex);
		window.draw(oxygens[i]);
	}
}

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.
	// A new view (with a new viewport set) is returned.

	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}

int main() {
	// load all of the block textures
	Block::load_block_textures();

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps", sf::Style::Fullscreen);

	//int width = 500;
	//int height = 500;

	int width = window.getSize().x / 2;
	int height = window.getSize().y / 2;

	//double sfx = (float) width

	window.setFramerateLimit(60);

	sf::Texture backTex;
	backTex.loadFromFile("Textures/Background.png");

	//Sprites
	sf::Sprite backSprite;
	backSprite.setTexture(backTex);

	//Camera
	sf::View main_camera(sf::FloatRect(0, 0, width * 1.0f, height * 1.0f));
	//camera.setSize(300, 300);
	main_camera.setCenter(150, 150);
	//camera = getLetterboxView(camera, window.getSize().x, window.getSize().y);


	window.setView(main_camera);

	// mini map
	sf::View mini_map = main_camera;
	mini_map.zoom(.5f);
	mini_map.setViewport(sf::FloatRect(.8f, 0, .2f, .15f));


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
		asteroids.emplace_back(150, 150, 15);

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
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		for (int i = 0; i < asteroids.size(); i++)
			asteroids[i].modifyPlayerGravity(player);
		
		player.checkRotation();

		for (int i = 0; i < asteroids.size(); i++)
			asteroids[i].chekCollision(player);

		player.update(window);

		window.clear();

		for (int i = 0; i < 2; i++) {
			window.draw(backSprite);

			for (int i = 0; i < asteroids.size(); i++)
				asteroids[i].draw(window);

			player.draw(window);

		}
		window.setView(main_camera);

		window.display();



		//std::cout << player.playerSprite.getGlobalBounds().left << "\n";

		/*profiler.restart();
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
		
		//std::cout << player.get_acceleration() << "\n";

		profiler.restart();
		player.update(window);
		if (DEBUG) std::cout << "Player Update:         " << profiler.getElapsedTime().asSeconds() << "\n";

		window.clear();

		for (int i = 0; i < 2; i++) {
			//sf::View& curr_view = i == 0 ? main_camera : mini_map;
			//window.setView(curr_view);

			window.draw(backSprite);			

			profiler.restart();
			for (int i = 0; i < asteroids.size(); i++)
				asteroids[i].draw(window);
			if (DEBUG) std::cout << "Draw Astro:            " << profiler.getElapsedTime().asSeconds() << "\n";

			profiler.restart();
			player.draw(window);
			if (DEBUG) std::cout << "Draw Player:           " << profiler.getElapsedTime().asSeconds() << "\n";
			if (DEBUG) std::cout << "---------------------------------------------------------------------------\n";

		}
		window.setView(main_camera);
		
		window.display(); */
	}

	std::cin.get();
}

