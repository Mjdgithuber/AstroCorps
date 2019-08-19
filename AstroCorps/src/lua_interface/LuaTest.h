#ifndef ______TEST______
#define ______TEST______

#include <SFML/Graphics.hpp>

namespace Lua {
	
	void init();
	void start(const char* path);
	void process_key(sf::Keyboard::Key code, bool pressed);
	void update();

}

#endif