#ifndef __LUA__XML__PARSER__H__
#define __LUA__XML__PARSER__H__

#include "XMLUtils.h"

class LuaXMLParser {
private:
	// these are for debugging mostly
	bool m_open;
	std::string m_name;
	std::string m_current_file;

	// core varibles	
	XML::XMLDocument m_doc;
	XML::XMLNode* m_parent_node;
	XML::XMLElement* m_current_element;

	bool check_if_open(const std::string& method_name);
	bool assert_current_element(XML::XMLElement* element, const std::string& caller);
public:
	LuaXMLParser(const std::string& name);

	bool open_doc(const char* filename);
	bool close_doc();

	bool find_element(const char* element);
	bool find_child_element(const char* child);
	bool find_next_sibling_element();
};

#endif