#ifndef __ITEM__H__
#define __ITEM__H__

#include <string>

#include <SFML/Graphics.hpp>

class Item {
private:
	std::string m_name;

public:
	Item(const std::string& name);

	const std::string& get_name() const;
};

#endif