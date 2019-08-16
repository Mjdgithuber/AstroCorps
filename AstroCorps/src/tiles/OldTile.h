#ifndef __OLD__TILE__H__
#define __OLD__TILE__H__

#include <string>

#include <SFML/Graphics.hpp>

namespace Tiles {

	class OldTile : public sf::Sprite {
	private:
		unsigned int m_reg_num;
		unsigned int m_modifier_reg_num;
		std::string m_script;
	public:
		/* =========================================================== */
		/* ============== Constructors and Destructors =============== */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// Constructs a new tile given all of its information
		/// Params:
		/// reg_num - The register number of the tile
		/// modifier_reg_num - The register number of the tile's modifer
		/// script - The script associated with this tile
		////////////////////////////////////////////////////////////
		OldTile(unsigned int reg_num, unsigned int modifier_reg_num, const std::string& script);


		/* =========================================================== */
		/* ========================= Getters ========================= */
		/* =========================================================== */

		////////////////////////////////////////////////////////////
		/// Returns the register number of the tile
		////////////////////////////////////////////////////////////
		unsigned int get_register_number() const;

		////////////////////////////////////////////////////////////
		/// Returns the modifier's register number
		////////////////////////////////////////////////////////////
		unsigned int get_modifier_register_number() const;

		////////////////////////////////////////////////////////////
		/// Returns the filepath to the script of the tile
		////////////////////////////////////////////////////////////
		const std::string& get_script() const;
	};

}

#endif