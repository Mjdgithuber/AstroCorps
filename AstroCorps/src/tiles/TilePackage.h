#ifndef __TILE__PACKAGE__H__
#define	__TILE__PACKAGE__H__

#include <string>

namespace Tiles {

	class TilePackage {
	private:
		unsigned int m_rows;
		unsigned int m_cols;
		unsigned int** m_reg_numbers;
		unsigned int** m_modifier_reg_numbers;
		std::string** m_scripts;
	public:
		TilePackage(unsigned int width, unsigned int height);
		~TilePackage();

		void modify_tile(unsigned int x, unsigned int y, unsigned int reg_num,
			unsigned int modifier_reg_num, const std::string& script);
	};

}

#endif