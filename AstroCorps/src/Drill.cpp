#include "Drill.h"

Drill::Drill(int t) {
	type = t;
	if (type == 0) {
		drillTex.loadFromFile("Textures/BasicDrill.png");
	}
	else if (type == 1) {
		drillTex.loadFromFile("Textures/AluminumDrill.png");
	}
	object.setTexture(drillTex);
}

void Drill::draw(sf::RenderWindow& window) {
	if (type == 0) {
		drillTex.loadFromFile("Textures/BasicDrill.png");
	}
	else if (type == 1) {
		drillTex.loadFromFile("Textures/AluminumDrill.png");
	}
	object.setTexture(drillTex);
	window.draw(object);
}