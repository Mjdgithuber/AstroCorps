#ifndef __TILE__MAP__H__
#define __TILE__MAP__H__

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tile.h"
#include "..\interfaces\Updatable.h"
#include "..\entities\Entity.h"
#include "..\entities\SingleFrameEntity.h"

namespace Tiles {

	class TileMap : public Updatable {
	private:
		unsigned int m_spritesheet_rows;
		unsigned int m_spritesheet_cols;
		unsigned int m_rows;
		unsigned int m_cols;
		unsigned int m_tile_size;
		float m_scale;
		bool m_bordered;

		std::vector<std::vector<Tile>> m_tiles;
		std::vector<Entity*> m_enties;
		sf::Texture m_mapsheet;

		void set_tile_textures();
	public:
		TileMap(const std::string& mapsheet, unsigned int rows, unsigned int cols, float scale = 1.f);

		Tile& get_tile(unsigned int row, unsigned int col);

		void draw_map(sf::RenderWindow& window);
		void toggle_borders();

		unsigned int get_rows() const;
		unsigned int get_cols() const;

		void load_map(const std::string& map_file);
		void add_entity(Entity* e);

		void update(const sf::Time& delta_time) override;
	};

}

#endif