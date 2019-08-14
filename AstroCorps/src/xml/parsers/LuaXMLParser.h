#ifndef __LUA__XML__PARSER__H__
#define __LUA__XML__PARSER__H__

#include "XMLUtils.h"

////////////////////////////////////////////////////////////
/// This is a parser for XML specifically made to be used
/// from within a Lua script with an appropriate level of
/// abtraction from tinyxml. Every instance of this parser
/// has a name (for debugging). 
/// Varibles:
/// m_doc - The currently opened document
/// m_root_node - The root node of the document
/// m_cached_element - The currently cached element
////////////////////////////////////////////////////////////
class LuaXMLParser {
private:
	// these are for debugging mostly
	bool m_open;
	std::string m_name;
	std::string m_current_file;

	// core document varibles	
	XML::XMLDocument m_doc;
	XML::XMLNode* m_root_node;
	XML::XMLElement* m_cached_element;

	/* =========================================================== */
	/* ================= Private Helper Functions ================ */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Will check to see if a document is currently open. If
	/// not, this method will print a warning to the console
	/// and return false. 
	/// Params:
	/// caller - The method calling this (for warning log)
	////////////////////////////////////////////////////////////
	bool check_if_open(const std::string& caller);

	////////////////////////////////////////////////////////////
	/// Will check to see if m_cached_element is not equal to 
	/// nullptr. If it is equal to nullptr, it will print a
	/// wanring.
	/// Params:
	/// element - The element you want to check
	/// caller - The method calling this (for warning log)
	////////////////////////////////////////////////////////////
	bool assert_current_element(const std::string& caller);

	////////////////////////////////////////////////////////////
	/// Will check to see this instance of the parser has a doc
	/// currently open, and check if m_cached_element is not
	/// equal to null. Returns true for a valid doc & element
	/// Params:
	/// caller - The method calling this (for warning log)
	////////////////////////////////////////////////////////////
	bool valid_file_and_element(const std::string& caller);
public:
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Makes a new LuaXMLParser with a given name. The name
	/// is mostly for debugging purposes so that you can check
	/// what parser had a certain issue. If possible the name
	/// should be unique from all other parsers.
	/// Params:
	/// name - The name of the parser (nothing to do with the
	///	       file it will be parsing)
	////////////////////////////////////////////////////////////
	LuaXMLParser(const std::string& name);


	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Attempts to open a document into DOM format. If the
	/// file doesn't exist it will return false and will
	/// print a warning.
	/// Params:
	/// filename - The path to the file to be opened
	////////////////////////////////////////////////////////////
	bool open_doc(const char* filename);

	////////////////////////////////////////////////////////////
	/* Needs to be implemented */
	////////////////////////////////////////////////////////////
	bool close_doc();

	////////////////////////////////////////////////////////////
	/// Attempts to cache an element of the given element name.
	/// This will get the first element with the given name. 
	/// This will NOT override the currently cached node if
	/// the element can't be found! Will return true if the 
	/// element was found
	/// NOTE: This attempts to cache from the root node, 
	/// meaning that it doesn't search realtive to the currently 
	/// cached node. 
	/// Params:
	/// element - The name of the element to be cached
	////////////////////////////////////////////////////////////
	bool cache_element(const char* element);

	////////////////////////////////////////////////////////////
	/// Attempts to cache an element that is a child of the 
	/// currently cached element. An element must already be
	/// cached in order for this method to load it's child.
	/// If successful this will cache the first child with 
	/// the given name. Returns true if child was found
	/// NOTE: This attempts to cache from the currently cached 
	///	node and therefore is not realtive to the root node.
	/// Params:
	/// child - The name of child element to be cached
	////////////////////////////////////////////////////////////
	bool cache_child_element(const char* child);

	////////////////////////////////////////////////////////////
	/// See documentation for:
	/// 'cache_child_element(const char* child)' for info
	/// The only difference is this method will load the first
	/// child instead of looking up a child by name
	////////////////////////////////////////////////////////////
	bool cache_child_element();

	////////////////////////////////////////////////////////////
	/* Needs to be implemented */
	////////////////////////////////////////////////////////////
	bool cache_next_sibling_element();


	/* =========================================================== */
	/* =================== Attribute Retrievers ================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Attempts to load an int attribute, with the given name, 
	/// from the currently cached element. Will return the 
	/// loaded int. 
	/// NOTE: If the attribute doesn't exist or can't be
	/// converted to an integer an error will print to the
	/// console and -1 will be returned
	/// Params:
	/// attribute - The attribute name containing the integer
	////////////////////////////////////////////////////////////
	int int_attribute(const std::string& attribute);

	////////////////////////////////////////////////////////////
	/// Attempts to load a float attribute, with the given name, 
	/// from the currently cached element. Will return the 
	/// loaded float. 
	/// NOTE: If the attribute doesn't exist or can't be
	/// converted to an float an error will print to the console
	/// and -1.f will be returned
	/// Params:
	/// attribute - The attribute name containing the float
	////////////////////////////////////////////////////////////
	float float_attribute(const std::string& attribute);

	////////////////////////////////////////////////////////////
	/// Attempts to load a string attribute, with the given name, 
	/// from the currently cached element. Will return the 
	/// loaded string. 
	/// NOTE: If the attribute doesn't exist or can't be
	/// converted to an string, I'd pay good money to see an 
	/// attribute that can't be converted to a string given they
	/// are stored as strings :), an error will print to the console
	/// and "ERROR" will be returned to aid debugging.
	/// Params:
	/// attribute - The attribute name containing the string
	////////////////////////////////////////////////////////////
	std::string string_attribute(const std::string& attribute);
};

#endif