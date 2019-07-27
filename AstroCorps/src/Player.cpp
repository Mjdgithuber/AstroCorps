#include "Player.h"


Player::Player() {
	rotation = NORTH;
	acceleration = sf::Vector2f(0, 0);

}

void Player::checkRotation() {
	
	/*
	double x = gravity.x;
	double y = gravity.y;

	if (x > 0) {
		if (y > 0) {
			if (x < y) {
				rotation = NORTH;
			}
			else {
				rotation = EAST;
			}
		}
		else {
			if (x < y) {
				rotation = SOUTH;
			}
			else {
				rotation = EAST;
			}
		}
	}
	else {
		if (y > 0) {
			if (x < y) {
				rotation = NORTH;
			}
			else {
				rotation = WEST;
			}
		}
		else {
			if (x < y) {
				rotation = WEST;
			}
			else {
				rotation = SOUTH;
			}
		}
	}

	if (rotation == NORTH) {
		rotationInt = 0;
		setRotation(0);
	}
	else if (rotation == EAST) {
		rotationInt = 1;
		setRotation(-90);
	}
	else if (rotation == SOUTH) {
		rotationInt = 2;
		setRotation(180);
	}
	else if (rotation == WEST) {
		rotationInt = 3;
		setRotation(90);
	}

	*/
}

void Player::update(sf::RenderWindow& window) {
	sf::View newView = window.getView();
	newView.setCenter(sf::Vector2f(getPosition().x + getGlobalBounds().width / 2, getPosition().y + getGlobalBounds().height / 2));

	float jetpack_multipler = 2;
	float x_dir = 0;
	float y_dir = 0;
	if (jetPack) {
		if (moveLeft)
			x_dir = -1;		
		if (moveRight)
			x_dir = 1;
		if (down)
			y_dir = 1;
		if (jump)
			y_dir = -1;

		x_dir *= y_dir ? 0.70710678 : 1;
		y_dir *= x_dir ? 0.70710678 : 1;

		acceleration += sf::Vector2f(.05f * jetpack_multipler * x_dir, 0.05f * jetpack_multipler * y_dir);

		if (!moveLeft && !moveRight && !jump && !down)
			acceleration += sf::Vector2f(0.f, -0.05f);
	}

	velocity += acceleration;
	move(velocity);

	acceleration = sf::Vector2f(0, 0);

	window.setView(newView);
}

void Player::stopPlayer() {
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	if (moveLeft) {
		velocity = sf::Vector2f(-2.75, velocity.y);
		setTextureRect(sf::IntRect(0, 0, 15, 30));
	}
	else if (moveRight) {
		velocity = sf::Vector2f(2.75, velocity.y);
		setTextureRect(sf::IntRect(15, 0, -15, 30));
	}
	if (jump) {
		velocity = sf::Vector2f(velocity.x, -2.75);
	}
	else if (down) {
		velocity = sf::Vector2f(velocity.x, 2.75);
	}
}

void Player::draw(sf::RenderWindow& window) {
	if (jetPack) {
		playerTex.loadFromFile("Textures/CharacterSideOn1.png");
	}
	else {
		playerTex.loadFromFile("Textures/CharacterSide.png");
	}
	setTexture(playerTex);
	window.draw(*this);
	window.draw(oxygenBar);
	window.draw(tempOxygenBar);
	//drawInventory(window);
}

double Player::get_acceleration() const {
	return std::sqrt(std::pow(acceleration.x, 2) + std::pow(acceleration.y, 2));
}