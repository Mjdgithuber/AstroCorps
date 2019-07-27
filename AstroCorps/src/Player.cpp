#include "Player.h"


Player::Player() {
	rotation = NORTH;
	movement = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);

	inventory.push_back(Drill(0));
	gravity = sf::Vector2f(0, 0);
	inventoryBoxes.push_back(sf::RectangleShape());
	inventoryBoxes.push_back(sf::RectangleShape());
	inventoryBoxes.push_back(sf::RectangleShape());
	inventoryBoxes.push_back(sf::RectangleShape());
	inventory.push_back(Drill(0));
}

void Player::checkRotation() {
	double x = gravity.x;
	double y = gravity.y;
	Rotation lastRotation;

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
		playerSprite.setRotation(0);
	}
	else if (rotation == EAST) {
		rotationInt = 1;
		playerSprite.setRotation(-90);
	}
	else if (rotation == SOUTH) {
		rotationInt = 2;
		playerSprite.setRotation(180);
	}
	else if (rotation == WEST) {
		rotationInt = 3;
		playerSprite.setRotation(90);
	}


}

void Player::update(sf::RenderWindow& window) {

	sf::View newView = window.getView();
	newView.setCenter(sf::Vector2f(playerSprite.getPosition().x + 7, playerSprite.getPosition().y + 15));

	if (frames != 0) {
		frames += frames < 0 ? 1 : -1;
		newView.rotate(frames < 0 ? -1 : 1);

	}


	if (jetPack) {
		generalOxygen -= 4;
		if (moveLeft) {
			velocity += sf::Vector2f(-0.05, 0);
		}
		else if (moveRight) {
			velocity += sf::Vector2f(0.05, 0);
		}if (down) {
			velocity += sf::Vector2f(0, 0.05);
		}
		else  if (jump) {
			velocity += sf::Vector2f(0, -0.05);
		}
		if (!moveLeft && !moveRight && !jump && !down) {
			velocity += sf::Vector2f(0, -0.05);
		}
	}
	velocity += acceleration;
	movement += velocity;
	playerSprite.move(movement);
	acceleration = sf::Vector2f(0, 0);
	movement = sf::Vector2f(0, 0);
	generalOxygen--;



	if (oxygenAmount < 0) {
		tempOxygenAmount = generalOxygen;
	}
	else {
		oxygenAmount = generalOxygen - tempOxygenAmount;
	}
	tempOxygenBar.setPosition(sf::Vector2f(newView.getCenter().x - 50, newView.getCenter().y + 115));
	tempOxygenBar.setSize(sf::Vector2f(tempOxygenAmount / 10, 10));

	oxygenBar.setPosition(sf::Vector2f(newView.getCenter().x - 50, newView.getCenter().y + 125));
	oxygenBar.setSize(sf::Vector2f(oxygenAmount / 10, 25));

	if (oxygenAmount > 500) {
		oxygenBar.setFillColor(sf::Color::Blue);
	}
	else if (oxygenAmount > 200) {
		oxygenBar.setFillColor(sf::Color::Yellow);
	}
	else {
		oxygenBar.setFillColor(sf::Color::Red);
	}
	tempOxygenBar.setFillColor(sf::Color(0, 255, 255));


	window.setView(newView);
}

void Player::stopPlayer() {
	movement = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	if (moveLeft) {
		velocity = sf::Vector2f(-2.75, velocity.y);
		playerSprite.setTextureRect(sf::IntRect(0, 0, 15, 30));
	}
	else if (moveRight) {
		velocity = sf::Vector2f(2.75, velocity.y);
		playerSprite.setTextureRect(sf::IntRect(15, 0, -15, 30));
	}
	if (jump) {
		velocity = sf::Vector2f(velocity.x, -2.75);
	}
	else if (down) {
		velocity = sf::Vector2f(velocity.x, 2.75);
	}
}

void Player::setPosition(int x, int y) {
	playerSprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) {
	if (jetPack) {
		playerTex.loadFromFile("Textures/CharacterSideOn1.png");
	}
	else {
		playerTex.loadFromFile("Textures/CharacterSide.png");
	}
	playerSprite.setTexture(playerTex);
	window.draw(playerSprite);
	window.draw(oxygenBar);
	window.draw(tempOxygenBar);
	//drawInventory(window);
}

void Player::drawInventory(sf::RenderWindow& window) {

	for (int i = 0; i < 4; i++) {
		inventoryBoxes[i].setFillColor(sf::Color::Transparent);
		inventoryBoxes[i].setSize(sf::Vector2f(16, 16));
		inventoryBoxes[i].setOutlineThickness(2);
		inventoryBoxes[i].setOutlineColor(sf::Color::Yellow);
		inventoryBoxes[i].setPosition(sf::Vector2f(window.getView().getCenter().x - (30 - (i * 17)), window.getView().getCenter().y + 95));
		window.draw(inventoryBoxes[i]);
	}

	for (int i = 0; i < ((inventory.size() < 4) ? inventory.size() : 4); i++) {
		inventory[i].drawObject(window, window.getView().getCenter().x - (30 - (i * 15)), window.getView().getCenter().y + 95);
	}


}