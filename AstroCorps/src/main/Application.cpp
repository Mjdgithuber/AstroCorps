#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"
#include "..\tiles\TileMap.h"
#include "..\xml\Register.h"
#include "..\managers\TextureManager.h"
#include "..\entities\Character.h"
#include "..\util\Util.h"

namespace Application {

	////////////////////////////////////////STATIC METHODS////////////////////////////////////////
	static void init() {
		std::cout << "Init Called!\n";
		Register::init();
		TextureManager::init();
	}
	
	Util::Direction process_direction_keys() {
		using namespace Util;
		bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		if (A ^ D) {
			if (A) return WEST;
			else return EAST;
		}

		if (W ^ S) {
			if (W) return NORTH;
			else return SOUTH;
		}

		return STATIONARY;
	}

	static void application_loop(sf::RenderWindow& window) {
		std::cout << "Application Loop Started!\n";

		Tiles::TileMap tm;
		tm.load_map("assets/maps/xmltest.xml");
		//tm.toggle_borders();
		
		Character* player = new Character(2, 2, 1, 1, 0.33f);
		
		tm.add_entity(player);

		sf::Clock frame_timer;

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
			player->set_movement(process_direction_keys());

			tm.update(delta_time);

			sf::View v = window.getView();
			v.setCenter(player->get_center());
			window.setView(v);

			window.clear();

			tm.draw_map(window);

			window.display();
		}

		delete player;
	}

	static void run() {
		std::cout << "Run Called!\n";

		sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		//window.setFramerateLimit(30);

		application_loop(window);
	}

	////////////////////////////////////APPLICATION DEFINTIONS////////////////////////////////////

	/* application wide constants */
	namespace {
		float scale;
		unsigned int tile_size;
		unsigned int scaled_tile_size;
	}

	/* Get the global scale factor of the tiles */
	float get_scale() {
		return scale;
	}

	/* Get the unscaled size of a tile */
	unsigned int get_unscaled_tile_size() {
		return tile_size;
	}

	/* Get the scaled size of a tile */
	unsigned int get_scaled_tile_size() {
		return scaled_tile_size;
	}

	/* Setup and run the application */
	void start_application(unsigned int unscaled_tile_size, float sc) {
		// setup global vars that will never change
		scale = sc;
		tile_size = unscaled_tile_size;
		scaled_tile_size = tile_size * scale;

		if (scaled_tile_size != tile_size * scale)
			std::cout << "\n\n=================\nERRRRRROORRRR!\n\nScaled Tile Size doesn't produce whole #\n";

		init();
		run();
	}
}
 