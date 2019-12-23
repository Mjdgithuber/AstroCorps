#ifndef __LUA__MAIN__H__
#define __LUA__MAIN__H__

#include <SFML/Graphics.hpp>

namespace Lua {
	
	void init();
	void start(const char* path);
	void process_key(sf::Keyboard::Key code, bool pressed);
	void process_click(int type);
	void update();
	bool load_script(const std::string& script_file);
	void lost_focus();

}

#endif