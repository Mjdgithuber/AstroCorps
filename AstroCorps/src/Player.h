#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

#include "Updatable.h"
#include "TimeDependent.h"

class Player : public sf::Sprite, public Updatable, private TimeDependent {
private:
	bool m_left;
	bool m_right;
	bool m_up;
	bool m_down;
	bool m_jetpack;

	bool m_on_surface;

	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	/* Private helper functions */
	void reset_acceleration();
	sf::Vector2f jetpack_acceleration();
	sf::Vector2f surface_velocity();
	float get_rotation(const sf::Vector2f& force);
public:
	/* Constructors & destructors */
	Player();
	~Player() = default;

	/* Functions */
	void update(sf::Time delta_time) override;
	void add_force(const sf::Vector2f& force);
	void draw(sf::RenderWindow& window);
	void process_key(sf::Keyboard::Key key, bool pressed = true);

	/* Setters */
	void set_on_surface(bool on_surface);

	/* Getters */
	float get_acceleration() const;
	sf::Vector2f get_player_center() const;	
};

#endif