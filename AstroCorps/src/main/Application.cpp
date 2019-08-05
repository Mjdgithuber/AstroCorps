#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"
#include "..\tiles\TileMap.h"

#include "..\entities\SingleFrameEntity.h"

#include "..\managers\TextureManager.h"

namespace Application {
	static void init() {
		std::cout << "Init Called!\n";
		TextureManager::init();
	}

	static void application_loop(sf::RenderWindow& window) {
		Tiles::TileMap tm("Spritesheets/mapsheet.png", 10, 10, 3);
		tm.load_map("Maps/map1.txt");
		tm.toggle_borders();
		
		tm.add_entity(new SingleFrameEntity(36 * 3, 5, 3, "Textures/testentity.png"));

		sf::Clock frame_timer;

		// main loop
		while (window.isOpen()) {
			sf::Time delta_time = frame_timer.restart();

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			tm.update(delta_time);

			window.clear();

			tm.draw_map(window);

			window.display();
		}
	}

	static void run() {
		std::cout << "Run Called!\n";

		sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps");
		window.setFramerateLimit(60);

		application_loop(window);
	}

	void start_application() {
		init();
		run();
	}
}
 