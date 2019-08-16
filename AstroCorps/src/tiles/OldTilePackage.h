#ifndef __OLD__TILE__PACKAGE__H__
#define	__OLD__TILE__PACKAGE__H__

#include <string>

namespace Tiles {

	class OldTilePackage {
	private:
		unsigned int m_rows;
		unsigned int m_cols;
		unsigned int** m_reg_numbers;
		unsigned int** m_modifier_reg_numbers;
		std::string** m_scripts;
	public:
		/* =========================================================== */
		/* ============== Constructors and Destructors =============== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// A TilePackage holds information on a map. It is basically
		/// a grouping of tiles that make up a given map. 
		////////////////////////////////////////////////////////////
		OldTilePackage(unsigned int width, unsigned int height);
		~OldTilePackage();


		/* =========================================================== */
		/* ======================== Functions ======================== */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// This function allows the modification of a specific tile
		/// contained within the package. All the information about 
		/// the tile must be passed in.
		/// Params:
		/// x & y- the location of the tile you want to modify
		/// reg_num - the register number of the tile
		/// modifier_reg_num - the register number of the modifier
		/// script - the script that is assocaited with the tile
		////////////////////////////////////////////////////////////
		void modify_tile(unsigned int x, unsigned int y, unsigned int reg_num,
			             unsigned int modifier_reg_num, const std::string& script);


		/* =========================================================== */
		/* ========================= Getters ========================= */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// Returns the number of rows the tile package contains.
		////////////////////////////////////////////////////////////
		unsigned int get_rows() const;

		////////////////////////////////////////////////////////////
		/// Returns the number of columns the tile package contains.
		////////////////////////////////////////////////////////////
		unsigned int get_cols() const;

		////////////////////////////////////////////////////////////
		/// Returns the register number with the assocaited tile at
		/// the x & y value sent in as params.
		/// Params:
		/// x & y - The tile you want the register number of
		////////////////////////////////////////////////////////////
		unsigned int get_register_num(unsigned int x, unsigned int y) const;

		////////////////////////////////////////////////////////////
		/// Returns the modifier's register number of the assocaited 
		/// tile at the x & y value sent in as params.
		/// Params:
		/// x & y - The tile you want the modifier's register number of
		////////////////////////////////////////////////////////////
		unsigned int get_modifier_register_num(unsigned int x, unsigned int y) const;

		////////////////////////////////////////////////////////////
		/// Returns the script of the assocaited tile at the x & y 
		/// value sent in as params.
		/// Params:
		/// x & y - The tile you want the script of
		////////////////////////////////////////////////////////////
		const std::string& get_script(unsigned int x, unsigned int y) const;
	};

}

#endif