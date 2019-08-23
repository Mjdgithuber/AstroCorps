#include "TilePackage.h"

namespace Engine {
	/* Makes a new tile package given a width & height */
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

	/* Frees all resources used by the package */
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

	/* Modifies the information of a specific tile. NOTE:
	   by default the tile information is uninitalized! */
	void TilePackage::modify_tile(unsigned int x, unsigned int y, unsigned int reg_num,
		unsigned int modifier_reg_num, const std::string& script) {
		// save tile info
		m_reg_numbers[y][x] = reg_num;
		m_modifier_reg_numbers[y][x] = modifier_reg_num;
		m_scripts[y][x] = script;
	}

	/* ========================= Getters ========================= */

	unsigned int TilePackage::get_rows() const {
		return m_rows;
	}

	unsigned int TilePackage::get_cols() const {
		return m_cols;
	}

	unsigned int TilePackage::get_register_num(unsigned int x, unsigned int y) const {
		return m_reg_numbers[y][x];
	}

	unsigned int TilePackage::get_modifier_register_num(unsigned int x, unsigned int y) const {
		return m_modifier_reg_numbers[y][x];
	}

	const std::string& TilePackage::get_script(unsigned int x, unsigned int y) const {
		return m_scripts[y][x];
	}
}