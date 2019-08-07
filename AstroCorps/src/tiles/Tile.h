#ifndef __TILE__H__
#define __TILE__H__

#include <string>

#include <SFML/Graphics.hpp>

namespace Tiles {

	/*unsigned int** m_modifier_reg_numbers;
	std::string** m_scripts; */

	class Tile : public sf::Sprite {
	private:
		unsigned int m_reg_num;
		unsigned int m_modifier_reg_num;
		std::string m_script;
	public:
		/* Constructor */
		Tile(unsigned int reg_num, unsigned int modifier_reg_num, const std::string& script);

		/* Getters */
		unsigned int get_register_number() const;
		unsigned int get_modifier_register_number() const;
		const std::string& get_script() const;
	};

}

#endif