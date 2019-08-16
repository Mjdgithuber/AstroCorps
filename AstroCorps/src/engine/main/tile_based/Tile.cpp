#include "Tile.h"

/* =========================================================== */
/* ============== Constructors and Destructors =============== */
/* =========================================================== */

/* Makes a new tile */
Tile::Tile(unsigned int reg_num, unsigned int modifier_reg_num, const std::string& script)
	: m_sprite(), m_reg_num(reg_num), m_modifier_reg_num(modifier_reg_num), m_script(script) {}


/* =========================================================== */
/* ========================= Getters ========================= */
/* =========================================================== */

sf::Sprite& Tile::get_sprite() { return m_sprite; }
unsigned int Tile::get_register_number() const { return m_reg_num; }
unsigned int Tile::get_modifier_register_number() const { return m_modifier_reg_num; }
const std::string& Tile::get_script() const { return m_script; }