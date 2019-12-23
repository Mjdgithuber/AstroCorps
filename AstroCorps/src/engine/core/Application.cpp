#include <SFML/Graphics.hpp>

#include "engine/common.h"
#include "engine/tools/xml/Register.h"
#include "lua_interface/LuaMain.h"

namespace Application {
	/* Prototypes */
	static bool init();
	static void cleanup();
	static void application_loop(sf::RenderWindow& window);
	static void run();

	/* application wide constants */
	namespace {
		// abort signal
		bool abort;

		// size of tiles
		float scale;
		unsigned int tile_size;
		unsigned int scaled_tile_size;

		// main window
		sf::RenderWindow* global_window = nullptr;

		// current tile map
		Lua::TileMap* current_tile_map;
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

		// don't run if not inited correctly
		if (init()) {
			// run application
			run();
		}

		// clean all memory
		cleanup();

		LOG_INFO("Application Ended");
	}



	////////////////////////////////////////STATIC/PRIVATE METHODS////////////////////////////////////////
	static bool init() {
		// resets abort flag
		abort = false;

		Engine::Log::init();
		LOG_INFO("Initializing System");

		if (!Engine::Register::init("assets/register/register.xml")) return false;

		global_window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		LOG_INFO("System Initialization Complete");

		/* make tile map null to make sure we don't
		   draw it until it is loaded */
		current_tile_map = nullptr;

		/* Init and start Lua */
		Lua::init();
		Lua::start("main.lua");

		return true;
	}

	static void cleanup() {
		delete global_window;

		LOG_DEBUG("Application Cleaned Up");
	}

	void load_tile_map(Lua::TileMap* new_tile_map) {
		current_tile_map = new_tile_map;
	}

	static void application_loop(sf::RenderWindow& window) {
		LOG_DEBUG("Application Loop Started");

		sf::Clock frame_timer;

		// main loop
		while (window.isOpen()) {
			// end game in case of error
			if (abort) break;

			sf::Time delta_time = frame_timer.restart();
			//std::cout << 1.f / delta_time.asSeconds() << "\n";

			sf::Event event;
			while (window.pollEvent(event)) {
				// closed button was clicked
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::KeyPressed)
					Lua::process_key(event.key.code, true);
				else if (event.type == sf::Event::KeyReleased)
					Lua::process_key(event.key.code, false);
				else if (event.type == sf::Event::LostFocus)
					Lua::lost_focus();
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						int x = event.mouseButton.x;
						int y = event.mouseButton.y;

						int tile_x = x / scaled_tile_size;
						int tile_y = y / scaled_tile_size;

						LOG_DEBUG("Click: {0}, {1}", tile_x, tile_y);
						Lua::process_click(Engine::Util::LEFT_MOUSE_BUTTON);
						
					} else {
						Lua::process_click(Engine::Util::RIGHT_MOUSE_BUTTON);
					}
				}
			}

			if (current_tile_map != nullptr)
				current_tile_map->update(delta_time);
			Lua::update();

			window.clear();

			if (current_tile_map != nullptr)
				current_tile_map->draw_map(window);

			window.display();
		}

		LOG_DEBUG("Application Loop Ended");
	}

	static void run() {
		LOG_DEBUG("Run Called");

		//sf::RenderWindow window(sf::VideoMode(1000, 800), "Astro Corps"); //, sf::Style::Fullscreen
		//(*global_window).setFramerateLimit(10);

		application_loop(*global_window);
	}

	/* Used to stop the application. NOTE: this will signal
	   an abort instead of just exiting, so things should
	   still get cleaned up depending on the error */
	void signal_abort(const std::string& reason) {
		abort = true;

		LOG_CRITICAL("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
			"\nABORT SIGNALED!\nA FATAL ERROR HAS OCCURRED!\nSTOPPING "
			"APPLICATION IMMEDIATELY!\nREASON: '{0}'\n"
			"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", reason);
	}
}