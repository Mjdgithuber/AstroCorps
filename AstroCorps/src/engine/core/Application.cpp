#include <SFML/Graphics.hpp>

#include "engine/common.h"
#include "engine/main/tile_based/TileMap.h"
#include "xml/Register.h"
#include "managers/TextureManager.h"

namespace Application {
	/* Prototypes */
	static void init();
	static void cleanup();
	Util::Direction process_direction_keys();
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
		scaled_tile_size = (unsigned)(tile_size * scale);

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

	static void application_loop(sf::RenderWindow& window) {
		LOG_DEBUG("Application Loop Started");

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

			window.clear();

			// draw the current tile map

			window.display();
		}
	}

	static void run() {
		LOG_DEBUG("Run Called");

		//sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		//(*global_window).setFramerateLimit(10);

		application_loop(*global_window);
	}
}