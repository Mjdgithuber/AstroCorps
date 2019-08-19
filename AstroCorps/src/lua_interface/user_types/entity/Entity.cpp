#include "Entity.h"
#include "engine/common.h"
#include "engine/tools/managers/TextureManager.h"

Entity::Entity(const std::string& name, unsigned int entry_no, int x, int y, int width, int height)
	: m_sprite(), m_name(name), m_entry_no(entry_no), m_x(x), m_y(y), m_width(width), m_height(height) {
	
	// Need to remove, just for testing
	m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
	m_sprite.setScale(Application::get_scale(), Application::get_scale());
	m_sprite.setPosition(Application::get_scaled_tile_size() * x, Application::get_scaled_tile_size() * y);

	m_speed = .33f;
}

Entity::~Entity() {
	LOG_DEBUG("Destructor for '{0}' called!\n", m_name);
}

void Entity::update_sprite_position() {
	float x_pos = m_x + m_x_offset;
	float y_pos = m_y + m_y_offset;
	x_pos *= Application::get_scaled_tile_size();
	y_pos *= Application::get_scaled_tile_size();
	m_sprite.setPosition(x_pos, y_pos);
}

void Entity::update(const sf::Time& delta_time) {
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

		update_sprite_position();
	}
}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

const std::string& Entity::get_name() const {
	return m_name;
}

int Entity::get_x() const {
	return m_x;
}

int Entity::get_y() const {
	return m_y;
}

int Entity::get_hor_offset(Util::Direction dir) const {
	return ((m_curr_dir == Util::EAST) ? 1 : (m_curr_dir == Util::WEST ? -1 : 0));
}

int Entity::get_vert_offset(Util::Direction dir) const {
	return ((m_curr_dir == Util::SOUTH) ? 1 : (m_curr_dir == Util::NORTH ? -1 : 0));
}

bool Entity::check_percentage(float& percentage) {
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

bool Entity::is_moving() const {
	return m_moving;
}

bool Entity::set_movement(Util::Direction dir) {
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

bool Entity::set_movement_dir(int dir) {
	return set_movement(static_cast<Util::Direction>(dir));
}