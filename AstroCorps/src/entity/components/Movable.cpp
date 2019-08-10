#include "Movable.h"

int Movable::get_hor_offset(Util::Direction dir) const {
	return ((m_curr_dir == Util::EAST) ? 1 : (m_curr_dir == Util::WEST ? -1 : 0));
}

int Movable::get_vert_offset(Util::Direction dir) const {
	return ((m_curr_dir == Util::SOUTH) ? 1 : (m_curr_dir == Util::NORTH ? -1 : 0));
}

bool Movable::set_movement(Util::Direction dir) {
	m_next_dir = dir;

	// only change direction if not moving
	if (m_curr_dir == Util::STATIONARY && m_next_dir != Util::STATIONARY) {
		// update current direction
		m_curr_dir = m_next_dir;

		// update location
		m_x += get_hor_offset(m_curr_dir);
		m_y += get_vert_offset(m_curr_dir);

		// restart movement's elasped time
		m_elap = m_elap.Zero;

		// movement has changed
		return true;
	}
	// movement hasn't changed
	return false;
}

bool Movable::check_percentage(float& percentage) {
	if (percentage >= 1.f) {
		if (m_curr_dir != m_next_dir) {
			percentage = 0.f; // snap to grid
			m_curr_dir = m_next_dir; // update direction
			m_x += get_hor_offset(m_curr_dir);
			m_y += get_vert_offset(m_curr_dir);
			m_elap = m_elap.Zero; // reset elapsed time
		}
		else {
			m_elap = sf::seconds((percentage - 1.f) * m_speed);
			percentage -= 1.f;
			// signal for x & y update
			return true;
		}
	}
	// signal for no location update
	return false;
}

Movable::Movable(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float speed) 
	: Transform(x, y, width, height), m_moving(false), m_speed(speed), m_curr_dir(Util::STATIONARY),
	  m_next_dir(Util::STATIONARY) {}

Component::Flag Movable::update(const sf::Time& delta_time) {
	if (m_curr_dir != Util::STATIONARY) {
		m_elap += delta_time;

		float percentage = m_elap.asSeconds() / m_speed;

		bool update_location_values = check_percentage(percentage);

		m_x_offset = -1.f * get_hor_offset(m_curr_dir) * (1.f - percentage);
		m_y_offset = -1.f * get_vert_offset(m_curr_dir) * (1.f - percentage);

		if (update_location_values) {
			// update location
			m_x += get_hor_offset(m_curr_dir);
			m_y += get_vert_offset(m_curr_dir);
		}

		return Component::UPDATE_POS;
	}

	return Component::NIL;
}

bool Movable::is_moving() const {
	return m_moving;
}