#include "TilePackage.h"

namespace Tiles {

	TilePackage::TilePackage(unsigned int width, unsigned int height) {
		// save width and height
		m_rows = height;
		m_cols = width;

		// setup rows
		m_reg_numbers = new unsigned int*[height];
		m_modifier_reg_numbers = new unsigned int*[height];
		m_scripts = new std::string*[height];

		// setup cols
		for (unsigned int row = 0; row < height; row++) {
			m_reg_numbers[row] = new unsigned int[width];
			m_modifier_reg_numbers[row] = new unsigned int[width];
			m_scripts[row] = new std::string[width];
		}
	}

	TilePackage::~TilePackage() {
		// delete all cols
		for (unsigned int row = 0; row < m_rows; row++) {
			delete[] m_reg_numbers[row];
			delete[] m_modifier_reg_numbers[row];
			delete[] m_scripts[row];
		}

		// delete rows
		delete[] m_reg_numbers;
		delete[] m_modifier_reg_numbers;
		delete[] m_scripts;
	}

	void TilePackage::modify_tile(unsigned int x, unsigned int y, unsigned int reg_num,
		unsigned int modifier_reg_num, const std::string& script) {
		// save tile info
		m_reg_numbers[y][x] = reg_num;
		m_modifier_reg_numbers[y][x] = modifier_reg_num;
		m_scripts[y][x] = script;
	}

}