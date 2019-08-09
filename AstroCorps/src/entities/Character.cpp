#include "Character.h"
#include "..\main\Application.h"
#include "..\managers\TextureManager.h"
#include <iostream>

Character::Character(float tile_x, float tile_y, unsigned int width, unsigned int height, float speed)
	: Entity(tile_x, tile_y, width, height), m_speed(speed), m_curr_dir(Util::STATIONARY), 
      m_next_dir(Util::STATIONARY) {
	// setup the sprite's texture and scale
	m_sprite.setTexture(TextureManager::get_entity_texture(Textures::Entity::TEST));
	float scale = ((float)Application::get_scaled_tile_size()) / m_sprite.getTexture()->getSize().x;
	m_sprite.setScale(sf::Vector2f(scale, scale));
}

/* Will update the final x & y baded on current direction */
void Character::update_destination() {
	// direction enum is contained within Util namespace
	using namespace Util;

	// calculate destination based on direction
	m_final_tile_x = m_tile_x + ((m_curr_dir == EAST) ? 1 : (m_curr_dir == WEST ? -1 : 0));
	m_final_tile_y = m_tile_y + ((m_curr_dir == SOUTH) ? 1 : (m_curr_dir == NORTH ? -1 : 0));
}

/* Will set the next direction the character will move in */
bool Character::set_movement(Util::Direction dir) {
	m_next_dir = dir;
	
	// only change direction if not moving
	using namespace Util;
	if (m_curr_dir == STATIONARY && m_next_dir != STATIONARY) {
		// update direction
		m_curr_dir = m_next_dir;
		update_destination();
		m_elap = m_elap.Zero; // restart movement's elasped time

		// movement has changed
		return true;
	}
	// movement hasn't changed
	return false;
}

/* This function will check to see if the percentage is over
   100% and if it is, this function will determine what to do.
   If the next movement direction is the same as the current
   direction then the character must not stop! */
bool Character::check_percentage(float& percentage) {
	/* The current x and y location only need to
	   update if the character has traversed at
	   least one tile in distance. */
	if (percentage >= 1.f) {
		/* this if-else statement ensures that smooth movement
		   occurs if the character is moving in the same
		   direction. If character is changing directions then
		   we want stop immediately and snap to the grid*/
		if (m_curr_dir != m_next_dir) {
			percentage = 1.f; // snap to grid
			m_curr_dir = m_next_dir; // update direction
			m_elap = m_elap.Zero; // reset elapsed time
		} else {
			/* this is the single most important line to this
			   function! Will reset the elapsed time to the # 
			   of seconds the character has moved over the 
			   expected amount. NOTE: the percentage isn't 
			   reset to 0 to ensure that the character doesn't 
			   appear to slow down*/
			m_elap = sf::seconds((percentage - 1.f) * m_speed);
		}
		// must signal for a location update
		return true;
	}
	// signal for no location update
	return false;
}

/* Will move the character in the correct direction if needed */
void Character::update(const sf::Time& delta_time) {
	// only move if not stationary
	if (m_curr_dir != Util::STATIONARY) {
		// add to elasped time since movement started
		m_elap += delta_time;

		/* calculate the percentage of the elapsed movement 
		   time over the character's speed (which is in seconds) */
		float percentage = m_elap.asSeconds() / m_speed;

		/* check to see if current and final x & y values need
		   to update. Additionally will adjust percentage to
		   ensure proper movement depending on m_next_dir */
		bool update_location_values = check_percentage(percentage);

		/* Calculate tile offset and new x & y locations. NOTE:
		   the (signed) cast is needed because an uint - unit will
		   produce another uint which therefore cannot be negative*/
		float x_offset = ((signed)(m_final_tile_x - m_tile_x)) * percentage;
		float y_offset = ((signed)(m_final_tile_y - m_tile_y)) * percentage;

		// convert tile x & y to x & y positions on the screen
		unsigned int x_loc = Application::get_scaled_tile_size() * (x_offset + m_tile_x);
		unsigned int y_loc = Application::get_scaled_tile_size() * (y_offset + m_tile_y);

		// update the actual position of the sprite
		m_sprite.setPosition(x_loc, y_loc);

		if (update_location_values) {
			// update actual tile location
			m_tile_x = m_final_tile_x;
			m_tile_y = m_final_tile_y;

			// update final x & y desitions
			update_destination();
		}
	}
}