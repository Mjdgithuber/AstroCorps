#include "GraphicalBase.h"

Component::Flag GraphicalBase::update(const sf::Time& delta_time) {
	return NIL;
}

void GraphicalBase::set_position(float x, float y) {
	m_sprite.setPosition(x, y);
}

void GraphicalBase::set_scale(float x_sf, float y_sf) {
	m_sprite.setScale(x_sf, y_sf);
}

sf::Sprite& GraphicalBase::get_sprite() {
	return m_sprite;
}