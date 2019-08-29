#ifndef __ENTITY__H__
#define __ENTITY__H__

#include <SFML/Graphics.hpp>

#include "engine/tools/util/Util.h"
#include "engine/tools/libs/lua/include/sol.hpp"


/* Vector of different movement states and what not each holding some frams ADD*** */
namespace Lua {
	class Entity {
	private:
		/* sprite to be drawn to window */
		sf::Sprite m_sprite;

		/* general entity information */
		std::string m_name;
		unsigned int m_entry_no;
		int m_x;
		int m_y;
		int m_width;
		int m_height;

		/* for movement of sprite */
		bool m_moving;
		float m_speed;
		float m_x_offset;
		float m_y_offset;
		sf::Time m_elap; // elasped movement time

		/* holds information about where the sprite is
		   moving. NOTE: we are typedefing unsigned int
		   as Direction instead of directly using
		   Util::Direction for lua compatibility*/
		typedef unsigned int Direction;
		Direction m_curr_dir;
		Direction m_next_dir;


		/* =========================================================== */
		/* ================= Private Helper Functions ================ */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// This will update m_sprite's current position based on
		/// m_x & m_y ad well as m_x_offset & m_y_offset.
		////////////////////////////////////////////////////////////
		void update_sprite_position();

		////////////////////////////////////////////////////////////
		/// This will update the entity's m_x & m_y varibles based
		/// on m_curr_direction. NOTE: this will not update the 
		/// sprites position, use update_sprite_position() for that
		////////////////////////////////////////////////////////////
		void adjust_tile_position();

		////////////////////////////////////////////////////////////
		/// Based on a given direction, this method will calculate
		/// the horizontal offset of the direction. For example if
		/// Util::WEST is passed in this will evaluate to -1 and 0
		/// for Util::NORTH
		/// Params:
		/// dir - The direction you want to get the offset of
		////////////////////////////////////////////////////////////
		int get_hor_offset(Direction dir) const;

		////////////////////////////////////////////////////////////
		/// Based on a given direction, this method will calculate
		/// the vertical offset of the direction. For example if
		/// Util::WEST is passed in this will evaluate to 0 and -1
		/// for Util::NORTH
		/// Params:
		/// dir - The direction you want to get the offset of
		////////////////////////////////////////////////////////////
		int get_vert_offset(Direction dir) const;

		////////////////////////////////////////////////////////////
		/// This method handles the next movement after the current
		/// movement is complete. If percentage is < 1.f then this 
		/// method returns false and does nothing. Otherwise, this
		/// ensures proper stopping & adjusting of movement (if the
		/// sprite is stopping or changing direction) or smooth
		/// movement (if the sprite is continuing in it's current
		/// direction)
		/// Params:
		/// percentage - The percentage of the current movement's
		/// completion
		////////////////////////////////////////////////////////////
		void check_percentage(float& percentage);

	public:
		/* =========================================================== */
		/* ============== Constructors and Destructors =============== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// Makes a new entity given some basic information. This
		/// will also set the sprites position to be correct given
		/// the x and y values, and will do the appropriate scaling
		/// based on width & height
		/// Params:
		/// name - The name of the entity
		/// entry_no - The number of the entity. This should be 
		/// unique for every entity
		/// x & y - The position of this entity (in tiles)
		/// width & height - The size of this entity (in tiles)
		////////////////////////////////////////////////////////////
		Entity(const std::string& name, unsigned int entry_no, int x, int y, int width, int height);
		~Entity() = default;


		/* =========================================================== */
		/* ======================== Functions ======================== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// In order for an entity to render to the window it must
		/// be associated with a texture sheet. A texture sheet is
		/// a texture that holds everything needed to render a 
		/// specific entity, for example it could hold every frame
		/// for movement in each direction as well as a firing 
		/// animation. The register file holds all the needed info
		/// on how to interpret each texture sheet
		/// Params:
		/// reg_num - The register number of the texture sheet
		////////////////////////////////////////////////////////////
		void set_texture_sheet(unsigned int reg_num);		
		
		////////////////////////////////////////////////////////////
		/// Will save the direction passed in as the next movement.
		/// If this entity isn't moving and a non-STATIONARY direction 
		/// is passed in then this will also start the movement.
		/// Params:
		/// dir - The direction this entity should move in next
		////////////////////////////////////////////////////////////
		void set_movement(Direction dir = Engine::Util::STATIONARY);

		////////////////////////////////////////////////////////////
		/// Will update the position of the sprite if it is currently
		/// moving.
		/// Params:
		/// delta_time - time since last frame
		////////////////////////////////////////////////////////////
		void update(const sf::Time& delta_time);

		////////////////////////////////////////////////////////////
		/// Draws this entity's sprite to the passed in window
		/// Params:
		/// window - the window you want to render to
		////////////////////////////////////////////////////////////
		void draw(sf::RenderWindow& window);


		/* =========================================================== */
		/* ========================= Getters ========================= */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// Gets this entity's x position in tiles
		////////////////////////////////////////////////////////////
		int get_x() const;

		////////////////////////////////////////////////////////////
		/// Gets this entity's y position in tiles
		////////////////////////////////////////////////////////////
		int get_y() const;

		////////////////////////////////////////////////////////////
		/// Returns true if the entity is moving
		////////////////////////////////////////////////////////////
		bool is_moving() const;

		////////////////////////////////////////////////////////////
		/// Returns the name of this entity, which is not necessarily
		/// unique
		////////////////////////////////////////////////////////////
		const std::string& get_name() const;


		/* =========================================================== */
		/* ==================== Static Functions ===================== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// Will register all necessary functions with the main Lua
		/// state to allow their use
		/// Params:
		/// state- The main Lua state
		////////////////////////////////////////////////////////////
		static void register_with_lua(sol::state& state);
	};
}

#endif