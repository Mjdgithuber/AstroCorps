#include <iostream>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include "Asteroid.h"
#include "Player.h"

#define DEBUG 0

int main() {
	// load all of the block textures
	Block::load_block_textures();

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps");//, sf::Style::Fullscreen

	int width = window.getSize().x / 2;
	int height = window.getSize().y / 2;

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
	

	// mini map
	sf::View mini_map = main_camera;
	mini_map.zoom(5.f);
	mini_map.setViewport(sf::FloatRect(.8f, 0, .2f, .15f));


	sf::Clock timer;

	sf::Sprite deathScreen;
	sf::Texture deathTex;
	deathTex.loadFromFile("Textures/DeathScreen.png");
	deathScreen.setTexture(deathTex);

	Player player;
	player.setPosition(500, 150);
	std::vector<Asteroid> asteroids;

	sf::Clock profiler;
	

	for (int i = 0; i < 1; i++)
		asteroids.emplace_back(500, 500, 15);

	// Delta time init
	sf::Clock frame_timer;
	sf::Time delta_time;

	while (window.isOpen()) {
		delta_time = frame_timer.restart();
		std::cout << "Last Frame Time: " << delta_time.asSeconds() << "\n";

		sf::Event event;

		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				player.process_key(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				player.process_key(event.key.code, false);

				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		// Check if player is colliding with an astroid
		bool on_surface = false;
		for (int i = 0; i < asteroids.size(); i++)
			if (asteroids[i].chekCollision(player))
				on_surface = true;
		player.set_on_surface(on_surface);

		// only modify gravity if player isn't on an asteroid
		if (!on_surface) {
			for (int i = 0; i < asteroids.size(); i++)
				asteroids[i].modifyPlayerGravity(player, delta_time);
		}

		// will move the player
		player.update(delta_time);

		// clears the screen
		window.clear();

		for (int i = 0; i < 1; i++) {
			// set the correct camera
			sf::View& camera = i == 0 ? main_camera : mini_map;
			camera.setCenter(player.get_player_center());
			window.setView(camera);
			
			// draw back ground
			window.draw(backSprite);

			// draw all asteroids
			for (int i = 0; i < asteroids.size(); i++)
				asteroids[i].draw(window);

			// draw player
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

