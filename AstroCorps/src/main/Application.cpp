#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"
#include "..\tiles\TileMap.h"

#include "..\entities\SingleFrameEntity.h"

#include "..\managers\TextureManager.h"

namespace Application {

	////////////////////////////////////////STATIC METHODS////////////////////////////////////////
	static void init() {
		std::cout << "Init Called!\n";
		TextureManager::init();
	}
	
	static void application_loop(sf::RenderWindow& window) {
		Tiles::TileMap tm("assets/spritesheets/mapsheet.png", 10, 10, 3);
		tm.load_map("assets/maps/map1.txt");
		//tm.toggle_borders();

		SingleFrameEntity* player = new SingleFrameEntity(36 * 3, 2, 3, 5);
		
		tm.add_entity(player);

		sf::Clock frame_timer;
		sf::Clock ttt;

		// main loop
		while (window.isOpen()) {
			sf::Time delta_time = frame_timer.restart();
			//std::cout << 1.f / delta_time.asSeconds() << "\n";

			sf::Event event;
			while (window.pollEvent(event)) {
				// closed button was clicked
				if (event.type == sf::Event::Closed)
					window.close();
			}

			// process keys
			bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			player->set_horizontal_movement(A ^ D, D);
			player->set_vertical_movement(W ^ S, S);

			ttt.restart();
			tm.update(delta_time);

			sf::View v = window.getView();
			v.setCenter(player->get_center());
			window.setView(v);

			window.clear();

			tm.draw_map(window);

			window.display();
		}
	}

	static void run() {
		std::cout << "Run Called!\n";

		sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		//window.setFramerateLimit(200);

		application_loop(window);
	}

	////////////////////////////////////APPLICATION DEFINTIONS////////////////////////////////////

	// application wide constants
	namespace {
		float scale;
		unsigned int tile_size;
		unsigned int scaled_tile_size;
	}

	float get_scale() {
		return scale;
	}

	unsigned int get_unscaled_tile_size() {
		return tile_size;
	}

	unsigned int get_scaled_tile_size() {
		return scaled_tile_size;
	}

	void start_application(unsigned int unscaled_tile_size, float sc) {
		// setup global vars
		scale = sc;
		tile_size = unscaled_tile_size;
		scaled_tile_size = tile_size * scale;

		init();
		run();
	}
}
 