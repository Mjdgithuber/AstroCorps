#ifndef __UTIL__H__
#define __UTIL__H__

namespace Engine {
	////////////////////////////////////////////////////////////
	/// The Util namespace has various useful utilities for use
	/// thoughout the program.
	////////////////////////////////////////////////////////////
	namespace Util {

		////////////////////////////////////////////////////////////
		/// A point holds an x and y value. NOTE: x and y are 
		/// unsigned integer values.
		////////////////////////////////////////////////////////////
		struct Point {
			unsigned int x;
			unsigned int y;

			////////////////////////////////////////////////////////////
			/// Constructs a point given a pair of unsigned ints
			/// Params:
			/// x & y - unsigned integers to be stored in the point
			////////////////////////////////////////////////////////////
			Point(unsigned int x, unsigned int y);
		};

		enum Direction {
			STATIONARY = 0,
			NORTH,
			EAST,
			SOUTH,
			WEST
		};

		enum MOUSE_BUTTON {
			LEFT_MOUSE_BUTTON = 0,
			RIGHT_MOUSE_BUTTON
		};

	}
}

#endif