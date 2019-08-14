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

bool LuaXMLParser::valid_file_and_element(const std::string& method_name) {
	return (check_if_open(method_name) && 
		    assert_current_element(m_current_element, method_name));
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




bool LuaXMLParser::cache_element(const char* element) {
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

bool LuaXMLParser::cache_child_element() {
	return cache_child_element("");
}

bool LuaXMLParser::cache_child_element(const char* child) {
	// ensure there is an open file and valid element cached
	if (!valid_file_and_element("find_child_element(const char* child)"))
		return false;
	/*if (!check_if_open("find_child_element(const char* child)"))
		return false;

	// ensure there is currently an element loaded 
	if (!assert_current_element(m_current_element, "find_child_element(const char* child)"))
		return false; */

	// check if current element has a child
	XML::XMLElement* temp = (std::string(child) == "") ?
		(m_current_element->FirstChildElement()) :
		(m_current_element->FirstChildElement(child));
	if (temp == nullptr) return false;
	
	// return trues and assigns temp to current element
	return (m_current_element = temp);
}

bool LuaXMLParser::cache_next_sibling_element() {
	return false;
}

int LuaXMLParser::int_attribute(const std::string& attribute) {
	if (!valid_file_and_element("int_attribute(const std::string& attribute)"))
		return false;

	int i;
	XML::XMLError result = XML::load_int(m_current_element, attribute.c_str(), i);

	if (result != XML::XML_SUCCESS) {
		LOG_ERROR("Lua Parser \'{0}\' tried to load int called \'{1}\' from element \'{2}\' from file \'{3}\'",
			m_name, attribute, m_current_element->Name(), m_current_file);
		return -1;
	}

	return i;
}

float LuaXMLParser::float_attribute(const std::string& attribute) {
	if (!valid_file_and_element("float_attribute(const std::string& attribute)"))
		return false;

	float f;
	XML::XMLError result = XML::load_float(m_current_element, attribute.c_str(), f);
	
	if (result != XML::XML_SUCCESS) {
		LOG_ERROR("Lua Parser \'{0}\' tried to load float called \'{1}\' from element \'{2}\' from file \'{3}\'",
			      m_name, attribute, m_current_element->Name(), m_current_file);
		return -1;
	}

	return f;
}

std::string LuaXMLParser::string_attribute(const std::string& attribute) {
	if (!valid_file_and_element("string_attribute(const std::string& attribute)"))
		return false;

	std::string s;
	XML::XMLError result = XML::load_string(m_current_element, attribute.c_str(), s);

	if (result != XML::XML_SUCCESS) {
		LOG_ERROR("Lua Parser \'{0}\' tried to load string called \'{1}\' from element \'{2}\' from file \'{3}\'",
			m_name, attribute, m_current_element->Name(), m_current_file);
		return "ERROR";
	}

	return s;
}