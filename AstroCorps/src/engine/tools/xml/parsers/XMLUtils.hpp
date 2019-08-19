#ifndef __XML__UTILS__HPP__
#define __XML__UTILS__HPP__

namespace XML {

	/* Gets the attribute from the element with the given name,
	   and stores it in var */
	template <typename T>
	XMLError load_attribute(XMLElement* element, const char* name, T& var) {
		// get attribute and load it into var
		return element->QueryAttribute(name, &var);
	}

}

#endif