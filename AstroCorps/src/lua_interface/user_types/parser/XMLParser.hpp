#ifndef __LUA__XML__PARSER__HPP__
#define __LUA__XML__PARSER__HPP__

namespace Lua {
	/* Gets an attribute from the current element with the
	   given name */
	template <typename T>
	T XMLParser::get_attribute(const std::string& attribute) {
		// ensure there is an open file and valid element cached
		if (!valid_file_and_element("get_attribute(const std::string& attribute)"))
			return T(); // don't crash just return default T()

		// makes a new T and attempts to load the attribute into it
		T to_read;
		Engine::XML::XMLError result = Engine::XML::load_attribute(m_cached_element, attribute.c_str(), to_read);

		// check if error occured
		if (result != Engine::XML::XML_SUCCESS) {
			// logs error to console
			LOG_ERROR("Lua Parser '{0}' called 'get_attribute()' and failed to find '{1}' from element '{2}' from file '{3}'",
				m_name, attribute, m_cached_element->Name(), m_current_file);
			return T(); // dont crash instead return default T() to hopefully aid in debugging process
		}
		// return loaded attribute
		return to_read;
	}
}

#endif