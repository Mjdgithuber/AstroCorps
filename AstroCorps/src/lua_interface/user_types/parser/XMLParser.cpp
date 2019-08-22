#include "engine/common.h"
#include "XMLParser.h"

namespace Lua {
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */

	/* Just inits name and everything is default or null */
	XMLParser::XMLParser(const std::string& name)
		: m_open(false), m_name(name), m_current_file("null"),
		m_doc(), m_root_node(nullptr), m_cached_element(nullptr) {}


	/* =========================================================== */
	/* ================= Private Helper Functions ================ */
	/* =========================================================== */

	/* Checks to see if a document is currently open, otherwise
	   it will print a warning to the console and return false */
	bool XMLParser::check_if_open(const std::string& caller) {
		if (!m_open) {
			// print warning
			LOG_WARN("Lua Parser '{0}' attempted to call '{1}' without an open file",
				m_name, caller);
			return false; // indicate no document is open
		}
		// indicate a document is open
		return true;
	}

	/* Checks to see if there is a currently cached element, i.e.
	   checks to see if m_current element != nullptr. Will print
	   a warning if there is no cached element */
	bool XMLParser::assert_current_element(const std::string& caller) {
		if (m_cached_element == nullptr) {
			// print warning
			LOG_WARN("Lua Parser '{0}' attempted to call '{1}' without an element currently loaded",
				m_name, caller);
			return false; // indicate that there is no cached element
		}
		// indicate there is a cached element
		return true;
	}

	/* Checks to see if a document is open and if an element
	   is currently cahced */
	bool XMLParser::valid_file_and_element(const std::string& caller) {
		// checks both
		return (check_if_open(caller) &&
			assert_current_element(caller));
	}


	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */

	/* Loads a xml document into m_doc */
	bool XMLParser::open_doc(const char* filename) {
		// check if another file is open
		if (m_open) {
			LOG_WARN("Lua Parser '{0}' attempted to open '{1}' before closing previous file '{2}'",
				m_name, filename, m_current_file);
			return false; // indicate failure
		}

		// attempt to load file
		m_root_node = XML::load_xml_file(m_doc, filename);
		if (!m_root_node) {
			LOG_ERROR("Lua Parser '{0}' attempted to open a malformed file '{1}'",
				m_name, filename);
			return false;
		}

		// save filename for debugging purposes
		m_current_file = filename;

		// set open to true for debugging purposes
		return (m_open = true);
	}

	bool XMLParser::cache_root_element(const char* element) {
		// ensure there is an open file
		if (!check_if_open("cache_root_element(const char* element)"))
			return false;
		// return true
		return (m_cached_element = m_root_node->ToElement());
	}

	/* Attempts to cache an element relative to the root
	   node. Only overrides m_cached_element if a non-null
	   element was located */
	bool XMLParser::cache_element(const char* element) {
		// ensure there is an open file
		if (!check_if_open("cache_element(const char* element)"))
			return false;

		/* attempt to grab element while using temp to avoid
		   overriding m_cached_element will a nullptr */
		XML::XMLElement* temp = m_root_node->FirstChildElement(element);
		m_cached_element = (temp ? temp : m_cached_element);

		// indicate no element was found
		if (!temp) return false;

		// element was found
		return true;
	}

	/* Will attempt to find and cache a child of the current
	   cached element */
	bool XMLParser::cache_child_element(const char* child) {
		// ensure there is an open file and valid element cached
		if (!valid_file_and_element("find_child_element(const char* child)"))
			return false;

		// check if current element has a child with the passed in name
		XML::XMLElement* temp = (std::string(child) == "") ?
			(m_cached_element->FirstChildElement()) : // first child
			(m_cached_element->FirstChildElement(child)); // child with given name
		if (temp == nullptr) return false; // indicate no element was found

		// return true and assigns temp to current element
		return (m_cached_element = temp);
	}

	/* Just calls the primary cache_child_element with ""
	   NOTE: using this instead of default parameter
	   because sol doesn't understand default params */
	bool XMLParser::cache_child_element() {
		return cache_child_element("");
	}


	/* =========================================================== */
	/* =================== Attribute Retriever =================== */
	/* =========================================================== */

	/* Check if attribute exists in cached element */
	bool XMLParser::check_attribute(const std::string& attribute) {
		// return false if no file/element is loaded
		if (!m_open || !m_cached_element) return false;

		// check by attempting to load into temp
		XML::XMLError result = XML::load_attribute(m_cached_element, attribute.c_str(),
			std::string());

		// if == success return true;
		return result == XML::XML_SUCCESS;
	}


	/* =========================================================== */
	/* ==================== Static Functions ===================== */
	/* =========================================================== */

	/* Register functions with Lua state */
	void XMLParser::register_with_lua(sol::state& state) {
		// allow the parser class to be accessed by scripts
		sol::usertype<XMLParser> parser_type = state.new_usertype<XMLParser>("Parser",
			// send in the usable constructors
			sol::constructors<XMLParser(std::string)>());

		// register parser's main functions
		parser_type["open_document"] = &XMLParser::open_doc;
		parser_type["cache_root_element"] = &XMLParser::cache_root_element;
		parser_type["cache_element"] = &XMLParser::cache_element;

		// overloading cache_child_element
		bool (XMLParser::*default_child)(void) = &XMLParser::cache_child_element;
		bool (XMLParser::*search_child)(const char*) = &XMLParser::cache_child_element;
		parser_type["cache_child_element"] = sol::overload(search_child, default_child);

		// register attribute checker
		parser_type["check_attribute"] = &XMLParser::check_attribute;

		// register attribute getters
		parser_type["float_attribute"] = &XMLParser::get_attribute<float>;
		parser_type["int_attribute"] = &XMLParser::get_attribute<int>;
		parser_type["string_attribute"] = &XMLParser::get_attribute<std::string>;

		//parser_type["cach_next_sibling_element"] = &LuaXMLParser::cache_next_sibling_element;
	}
}