#include <iostream>

#include <SFML/Graphics.hpp>

#include "Core.h"
#include "tiles/TileMap.h"
#include "xml/Register.h"
#include "managers/TextureManager.h"

namespace Application {

	/* Prototypes */
	static void init();
	static void cleanup();
	Util::Direction process_direction_keys();
	static void setup_inventory();
	static void draw_inventory(sf::RenderWindow& window);
	static void application_loop(sf::RenderWindow& window);
	static void run();

	/* application wide constants */
	namespace {
		// size of tiles
		float scale;
		unsigned int tile_size;
		unsigned int scaled_tile_size;

		// main window
		sf::RenderWindow* global_window;
	}

	////////////////////////////////////PUBLIC DEFINTIONS////////////////////////////////////

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
		scaled_tile_size = (unsigned) (tile_size * scale);

		if (scaled_tile_size != tile_size * scale)
			LOG_ERROR("Scaled Tile Size ({0}) must equal {1}", scaled_tile_size, (scale));

		init();
		run();
		cleanup();
	}



	////////////////////////////////////////STATIC/PRIVATE METHODS////////////////////////////////////////
	static void init() {
		Log::init();
		LOG_INFO("Initializing System");

		Register::init();
		TextureManager::init();

		global_window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		LOG_INFO("System Initialization Complete");
	}

	static void cleanup() {
		delete global_window;
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

	sf::Texture main_pane_texture;
	sf::Sprite main_pain;
	static void setup_inventory() {
		main_pane_texture.loadFromFile("assets/testing/panel.png");
		main_pain.setTexture(main_pane_texture);
		
	}

	static void draw_inventory(sf::RenderWindow& window) {
		sf::View v(sf::FloatRect(0, 0, 242, 302));

		float perx = (242.f / window.getSize().x);
		float pery = (302.f / window.getSize().y);

		v.setViewport(sf::FloatRect(1.f - perx - .05f, 0 + .05f, perx, pery));

		window.setView(v);
		window.draw(main_pain);

		window.setView(window.getDefaultView());
	}

	static void application_loop(sf::RenderWindow& window) {
		LOG_DEBUG("Application Loop Started");

		setup_inventory();

		Tiles::TileMap tm;
		tm.load_map("assets/maps/xmltest.xml");
		tm.toggle_borders();
		
		Entity* player = new Entity("assets/entities/tester.xml");
		Movable* player_movement = player->get_component<Movable>();

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

			// process keys+

			player_movement->set_movement(process_direction_keys());
			//player->mov->set_movement(process_direction_keys());

			tm.update(delta_time);

			//sf::View v = window.getView();
			//v.setCenter(player->get_center());
			//window.setView(v);

			window.clear();

			tm.draw_map(window);

			//draw_inventory(window);

			window.display();
		}

		delete player;
	}

	static void run() {
		LOG_DEBUG("Run Called");

		//sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		//(*global_window).setFramerateLimit(10);

		application_loop(*global_window);
	}
}
 