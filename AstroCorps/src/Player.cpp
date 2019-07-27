#include "Player.h"

/* Sets the players acceleration to 0, 0 */
void Player::reset_acceleration() {
	m_acceleration = sf::Vector2f(0, 0);
}

/* This method gets the jetpack's acceleration if it is on */
void Player::jetpack_acceleration() {
	if (m_jetpack) {
		float jetpack_multipler = 2;
		float x_dir = 0;
		float y_dir = 0;

		// detect up/down + left/right movement
		x_dir = m_left ^ m_right ? (m_left ? -1 : 1) : 0;
		y_dir = m_down ^ m_up ? (m_up ? -1 : 1) : 0;

		// ensure that diagnoal movement isn't more powerful
		x_dir *= y_dir ? .3 : 1;
		y_dir *= x_dir ? .3 : 1;

		// add to acceleration
		m_acceleration += sf::Vector2f(.05f * jetpack_multipler * x_dir, 0.05f * jetpack_multipler * y_dir);
	}
}

/* Makes a new player */
Player::Player() 
	: m_left(false), m_right(false), m_up(false), m_down(false),
	m_jetpack(false), m_on_surface(false) {

	m_acceleration = sf::Vector2f(0, 0);
}

/* This method takes in a key and a bool and processes them */
void Player::process_key(sf::Keyboard::Key key, bool pressed) {
	switch (key) {
	case sf::Keyboard::D:
		m_right = pressed;
		break;
	case sf::Keyboard::A:
		m_left = pressed;
		break;
	case sf::Keyboard::W:
		m_up = pressed;
		break;
	case sf::Keyboard::S:
		m_down = pressed;
		break;
	case sf::Keyboard::Space:
		m_jetpack = pressed;
		break;
	}
}

/* This method will updates the players position */
void Player::update(sf::RenderWindow& window) {
	// determine the players movement
	if (m_on_surface)
		walk_on_surface();
	else
		jetpack_acceleration();	

	// add player's acceleration to velocity and move by velocity
	m_velocity += m_acceleration;
	move(m_velocity);

	// ensure that acceleration is set to zero every frame
	reset_acceleration();
}

void Player::set_on_surface(bool on_surface) {
	m_on_surface = on_surface;
}

/* Allows the player to move on a surface */
void Player::walk_on_surface() {
	// ensure that velocity & acceleration is 0
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);

	int x_dir = 0;
	int y_dir = 0;

	// detect up/down + left/right movement
	x_dir = m_left ^ m_right ? (m_left ? -1 : 1) : 0;
	y_dir = m_down ^ m_up ? (m_up ? -1 : 1) : 0;

	m_velocity = sf::Vector2f(2.75 * x_dir, 2.75 * y_dir);
}

/* Soon to be removed */
void Player::draw(sf::RenderWindow& window) {
	if (m_jetpack) {
		m_texture.loadFromFile("Textures/CharacterSideOn1.png");
	}
	else {
		m_texture.loadFromFile("Textures/CharacterSide.png");
	}
	setTexture(m_texture);
	window.draw(*this);
}

void Player::add_force(const sf::Vector2f& force) {
	m_acceleration += force;
}

/* This method gets the magnitude of the player's acceleration */
float Player::get_acceleration() const {
	return std::sqrt(std::pow(m_acceleration.x, 2) + std::pow(m_acceleration.y, 2));
}

/* This methods get the player's center coordinates */
sf::Vector2f Player::get_player_center() const {
	return sf::Vector2f(getPosition().x + getGlobalBounds().width / 2, 
		                getPosition().y + getGlobalBounds().height / 2);
}