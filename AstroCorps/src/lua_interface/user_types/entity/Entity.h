#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

class Entity {
private:
	// sprite to be drawn
	sf::Sprite m_sprite;

	std::string m_name;
	unsigned int m_entry_no;
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	

	/*std::string m_name;

	void update_sprite_position();

	bool m_moving;*/
public:
	Entity(const std::string& name, unsigned int entry_no, int x, int y, int width, int height);
	~Entity();

	void draw(sf::RenderWindow& window);
	void update(const sf::Time& delta_time);
	/*void set_position(unsigned int x, unsigned int y);
	void draw(sf::RenderWindow& window);
	void move(int x_off, int y_off);
	void set_speed();
	
	bool is_moving();*/

	int get_x() const;
	int get_y() const;
	const std::string& get_name() const;
	/*int get_width() const;
	int get_height() const;
	float get_x_offset() const;
	float get_y_offset() const;*/
};

#endif