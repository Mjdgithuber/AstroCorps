#include "Entity.h"
#include "engine/common.h"
#include "engine/tools/xml/Register.h"

namespace Lua {
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */

	/* Just makes a new entity */
	Entity::Entity(const std::string& name, unsigned int entry_no, int x, int y, int width, int height)
		: m_sprite(), m_name(name), m_entry_no(entry_no), m_x(x), m_y(y), m_width(width), m_height(height),
		m_moving(false), m_speed(.33f), m_x_offset(0.f), m_y_offset(0.f) {

		// Need to remove, just for testing ********************************
		m_sprite.setTexture(Engine::Register::get_texture(0));
		//m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
		m_sprite.setScale(Application::get_scale(), Application::get_scale());
		m_sprite.setPosition((float)Application::get_scaled_tile_size() * x, (float)Application::get_scaled_tile_size() * y);
	}


	/* =========================================================== */
	/* ================= Private Helper Functions ================ */
	/* =========================================================== */

	/* Will update m_sprite's position based on it's
	   x & y value + their respective offsets */
	void Entity::update_sprite_position() {
		/* get position (in tiles) accounting for
		   any current movement */
		float x_pos = m_x + m_x_offset;
		float y_pos = m_y + m_y_offset;

		// turn tile position into pixel position
		x_pos *= Application::get_scaled_tile_size();
		y_pos *= Application::get_scaled_tile_size();

		// update sprite position
		m_sprite.setPosition(x_pos, y_pos);
	}

	/* Will update x & y of entity (note sprite)
	   based on current direction */
	void Entity::adjust_tile_position() {
		m_x += get_hor_offset(m_curr_dir);
		m_y += get_vert_offset(m_curr_dir);
	}

	/* Will return the horizontal component of a
	   given direction */
	int Entity::get_hor_offset(Direction dir) const {
		return ((m_curr_dir == Engine::Util::EAST) ? 1 
			: (m_curr_dir == Engine::Util::WEST ? -1 : 0));
	}

	/* Will return the vertical component of a
	   given direction */
	int Entity::get_vert_offset(Direction dir) const {
		return ((m_curr_dir == Engine::Util::SOUTH) ? 1 : 
			(m_curr_dir == Engine::Util::NORTH ? -1 : 0));
	}

	/* Will adjust the percentage as needed */
	void Entity::check_percentage(float& percentage) {
		if (percentage >= 1.f) {
			// if changing direction
			if (m_curr_dir != m_next_dir) {
				// snap to grid
				percentage = 0.f;
				// update to new direction
				m_curr_dir = m_next_dir;
				// reset elapsed time
				m_elap = m_elap.Zero;
			}
			else { // if no direction change
			 /* will reset the elapsed time to the # of
				seconds the entity has surpassed the expected
				tile by. NOTE: the percentage isn't reset to 0
				to ensure that the entity has smooth movement
				and doesn't appear to slow down */
				percentage -= 1.f;
				m_elap = sf::seconds(percentage * m_speed);
			}
			// update tile location of entity
			adjust_tile_position();
		}
	}


	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */

	/* Sets the next movement direction to the passed
	   in direction. Will also start movement if
	   currently STATIONARY */
	void Entity::set_movement(Direction dir) {
		m_next_dir = dir;

		// only change direction if not moving
		if (m_curr_dir == Engine::Util::STATIONARY && m_next_dir 
			!= Engine::Util::STATIONARY) {
			// update current direction & location
			m_curr_dir = m_next_dir;
			adjust_tile_position();

			// restart movement's elasped time
			m_elap = m_elap.Zero;
		}
	}

	/* Will move the entity if it is currently moving */
	void Entity::update(const sf::Time& delta_time) {
		if (m_curr_dir != Engine::Util::STATIONARY) {
			// caculate how much to offset by
			m_elap += delta_time;
			float percentage = m_elap.asSeconds() / m_speed;

			/* adjust percentage to either snap to
			   grid or to smoothly continue depending
			   on next direction */
			check_percentage(percentage);

			// find offset
			m_x_offset = -1.f * get_hor_offset(m_curr_dir) * (1.f - percentage);
			m_y_offset = -1.f * get_vert_offset(m_curr_dir) * (1.f - percentage);

			// set postion of this entity's sprite
			update_sprite_position();
		}
	}

	/* draws this entity's sprite to the window */
	void Entity::draw(sf::RenderWindow& window) {
		window.draw(m_sprite);
	}


	/* =========================================================== */
	/* ========================= Getters ========================= */
	/* =========================================================== */

	/* Gets this entity's x position in tiles */
	int Entity::get_x() const {
		return m_x;
	}

	/* Gets this entity's y position in tiles */
	int Entity::get_y() const {
		return m_y;
	}

	/* Returns true if the entity is moving */
	bool Entity::is_moving() const {
		return m_moving;
	}

	/* Returns the name of the entity */
	const std::string& Entity::get_name() const {
		return m_name;
	}

	/* =========================================================== */
	/* ==================== Static Functions ===================== */
	/* =========================================================== */

	/* Register functions with Lua state */
	void Entity::register_with_lua(sol::state& state) {
		// register type with lua
		sol::usertype<Entity> entity_type = state.new_usertype<Entity>("Entity");

		// register functions
		entity_type["set_movement"] = &Entity::set_movement;

		// register getters
		entity_type["get_name"] = &Entity::get_name;
		entity_type["get_x"] = &Entity::get_x;
		entity_type["get_y"] = &Entity::get_y;
	}
}