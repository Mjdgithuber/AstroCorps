#include "Core.h"
#include "LuaXMLParser.h"
#include "XMLUtils.h"

LuaXMLParser::LuaXMLParser(const std::string& name)
	: m_open(false), m_name(name), m_current_file("null"), 
	  m_doc(), m_parent_node(nullptr), m_current_element(nullptr) {}

bool LuaXMLParser::check_if_open(const std::string& method_name) {
	if (!m_open) {
		LOG_WARN("Lua Parser \'{0}\' attempted to call \'{1}\' without an open file",
				 m_name, method_name);
		return false;
	}
	return true;
}

bool LuaXMLParser::assert_current_element(XML::XMLElement* element, const std::string& caller) {
	if (element == nullptr) {
		LOG_WARN("Lua Parser \'{0}\' attempted to call \'{1}\' without an element currently loaded",
			m_name, caller);
		return false;
	}
	return true;
}

bool LuaXMLParser::open_doc(const char* filename) {
	// check if another file is open
	if (m_open) {
		LOG_WARN("Lua Parser \'{0}\' attempted to open \'{1}\' before closing previous file \'{2}\'",
				 m_name, filename, m_current_file);
		return false;
	}
	
	// attempt to load file
	m_parent_node = XML::load_xml_file(m_doc, filename);
	if (!m_parent_node) {
		LOG_ERROR("Lua Parser \'{0}\' attempted to open a malformed file \'{1}\'",
				  m_name, filename);
		return false;
	}

	// save filename for debugging purposes
	m_current_file = filename;

	// set open to true for debugging purposes
	return (m_open = true);
}


/*
	Should be load element and what not
	there should be a prevoius loaded 
	element as well!!!
*/




bool LuaXMLParser::find_element(const char* element) {
	// ensure there is an open file
	if (!check_if_open("find_element(const char* element)")) 
		return false;

	// attempt to grab element
	m_current_element = m_parent_node->FirstChildElement(element);

	// indicate no element was found
	if (!m_current_element) return false;

	// element was found
	return true;
}

bool LuaXMLParser::find_child_element(const char* child) {
	// ensure there is an open file
	if (!check_if_open("find_child_element(const char* child)"))
		return false;

	// ensure there is currently an element loaded 
	if (!assert_current_element(m_current_element, "find_child_element(const char* child)"))
		return false;



	return false;
}

bool LuaXMLParser::find_next_sibling_element() {
	return false;
}