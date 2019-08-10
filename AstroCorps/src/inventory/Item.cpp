#include "Item.h"

Item::Item(const std::string& name)
	: m_name(name) {}

const std::string& Item::get_name() const {
	return m_name;
}