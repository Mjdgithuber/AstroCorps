#include "Tile.h"

namespace Tiles {
	Point::Point(unsigned int x, unsigned int y) : x(x), y(y) {}

	Tile::Tile(TileState state, Point texture_loc) 
		: m_state(state), m_texture_loc(texture_loc) {}

	TileState Tile::get_state() const { return m_state; }
	Point Tile::get_texture_location() const { return m_texture_loc; }
}
