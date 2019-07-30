#ifndef __TILE__H__
#define __TILE__H__

#include <SFML/Graphics.hpp>

namespace Tiles {

	enum TileState {
		NULL_T,
		BLOCKED,
		WALKABLE,
		INTERACT
	};

	struct Point {
	public:
		unsigned int x, y;

		/* Constructors */
		Point(unsigned int x, unsigned int y);
		Point(const Point& p) = default;
	};

	class Tile : public sf::Sprite {
	private:
		TileState m_state;
		Point m_texture_loc;
	public:
		/* Constructor */
		Tile(TileState state, Point texture_loc);

		/* Getters */
		TileState get_state() const;
		Point get_texture_location() const;
	};

}

#endif