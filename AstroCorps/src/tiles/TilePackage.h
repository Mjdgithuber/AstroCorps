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

		/* Functions */
		void modify_tile(unsigned int x, unsigned int y, unsigned int reg_num,
			unsigned int modifier_reg_num, const std::string& script);

		/* Getters */
		unsigned int get_rows() const;
		unsigned int get_cols() const;

		unsigned int get_register_num(unsigned int x, unsigned int y) const;
		unsigned int get_modifier_register_num(unsigned int x, unsigned int y) const;
		const std::string& get_script(unsigned int x, unsigned int y) const;
	};

}

#endif