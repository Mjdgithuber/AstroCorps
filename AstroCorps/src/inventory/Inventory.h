#ifndef __INVENTORY__H__
#define __INVENTORY__H__

#include <vector>

#include <SFML/Graphics.hpp>

#include "Item.h"

class Inventory {
private:
	sf::Font m_text_font;
	sf::Text t;
	

	std::vector<Item> m_item_list;
	// selection variables
	unsigned int m_select_index;
	unsigned int m_select_offset;
public:
	Inventory(const std::string& filename);

	void draw(sf::RenderWindow& window);
};

#endif