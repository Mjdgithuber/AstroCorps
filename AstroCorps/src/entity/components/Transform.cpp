#include "Transform.h"

std::string Transform::get_base_name() {
	return "Transform";
}

Transform::Transform(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_x_offset(0.f), m_y_offset(0.f) {}

unsigned int Transform::get_x() const {
	return m_x;
}

unsigned int Transform::get_y() const {
	return m_y;
}

unsigned int Transform::get_width() const {
	return m_width;
}

unsigned int Transform::get_height() const {
	return m_height;
}

float Transform::get_x_offset() const {
	return m_x_offset;
}

float Transform::get_y_offset() const {
	return m_y_offset;
}

std::string Transform::get_name() {
	return "Transform";
}