#include "OldTile.h"

namespace Tiles {
	/* ============== Constructors and Destructors =============== */

	/* Makes a new tile */
	OldTile::OldTile(unsigned int reg_num, unsigned int modifier_reg_num, const std::string& script)
		: m_reg_num(reg_num), m_modifier_reg_num(modifier_reg_num), m_script(script) {}


	/* ========================= Getters ========================= */

	unsigned int OldTile::get_register_number() const { return m_reg_num; }
	unsigned int OldTile::get_modifier_register_number() const { return m_modifier_reg_num; }
	const std::string& OldTile::get_script() const { return m_script; }

}
