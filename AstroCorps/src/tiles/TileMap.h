#ifndef __TILE__MAP__H__
#define __TILE__MAP__H__

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tile.h"
#include "..\interfaces\Updatable.h"
#include "..\entity\Entity.h"

namespace Tiles {

	class TileMap : public Updatable {
	private:
		unsigned int m_rows;
		unsigned int m_cols;
		bool m_bordered;

		std::vector<std::vector<Tile>> m_tiles;
		std::vector<Entity*> m_enties;

		////////////////////////////////////////////////////////////
		/// Goes through each tile and sets its texture. This method
		/// is curretnly used only for toggling on and off the borders
		/// on each tile.
		////////////////////////////////////////////////////////////
		void set_tile_textures();
	public:
		/* =========================================================== */
		/* ============== Constructors and Destructors =============== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// Makes a new tile map that has no associated map with it.
		/// A map must be loaded into it by using the load_map() 
		/// function.
		////////////////////////////////////////////////////////////
		TileMap();


		/* =========================================================== */
		/* ======================== Functions ======================== */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// Renders the tile map to a window.
		/// Params:
		/// window - The window that you want the map rendered to
		////////////////////////////////////////////////////////////
		void draw_map(sf::RenderWindow& window);

		////////////////////////////////////////////////////////////
		/// This method will either turn on or turn off borders on
		/// each one of the tiles of the map. This is to make testing
		/// of certain aspects of the game easy.
		////////////////////////////////////////////////////////////
		void toggle_borders();

		////////////////////////////////////////////////////////////
		/// This method will load a map (xml format) into the tile
		/// map.
		/// Params:
		/// map_file - The xml file you want loaded into the tile map
		////////////////////////////////////////////////////////////
		void load_map(const char* map_file);

		////////////////////////////////////////////////////////////
		/// Adds an entity into the tile map.
		/// Params:
		/// e - The location of the entity you want to add
		////////////////////////////////////////////////////////////
		void add_entity(Entity* e);

		////////////////////////////////////////////////////////////
		/// Performs all of the needed logic for everything dealing
		/// with this tile map. This should be called every frame 
		/// for every tile map that is being rendered.
		/// Params:
		/// delta_time - The time it took to render last frame
		////////////////////////////////////////////////////////////
		void update(const sf::Time& delta_time) override;


		/* =========================================================== */
		/* ========================= Getters ========================= */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// Returns a tile, by reference, at the given position
		/// Params:
		/// row & col - The row and column of the desired tile
		////////////////////////////////////////////////////////////
		Tile& get_tile(unsigned int row, unsigned int col);

		////////////////////////////////////////////////////////////
		/// Returns a const tile, by reference, at the given position
		/// Params:
		/// See non-const get_tile for information
		////////////////////////////////////////////////////////////
		const Tile& get_tile(unsigned int row, unsigned int col) const;
		
		////////////////////////////////////////////////////////////
		/// Returns the number of rows contained in this tile map
		////////////////////////////////////////////////////////////
		unsigned int get_rows() const;

		////////////////////////////////////////////////////////////
		/// Returns the number of rows contained in this tile map
		////////////////////////////////////////////////////////////
		unsigned int get_cols() const;
	};

}

#endif