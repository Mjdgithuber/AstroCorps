#include "XMLUtils.h"

namespace XML {

	/* Given a filepath it will attempt (if filepath is valid)
	   to load it into the passed in XMLDocument. It will also
	   get the root node and return it. NOTE: all XML files
	   must have a node otherwise it is malformed*/
	XMLNode* load_xml_file(XMLDocument& doc, const char* filepath) {
		// attempt to load file
		XMLError eResult = doc.LoadFile(filepath);
		XMLCheckResult(eResult);

		// get the root of the document
		XMLNode* root = doc.FirstChild();
		XMLNullCheck(root, XML_ERROR_FILE_READ_ERROR);

		// return the node
		return root;
	}

	/* Specialization of load_attribute for strings because
	   tinyxml doesn't know what a string is. So this uses
	   c-strings instead and just wraps it in std::string */
	template <>
	XMLError load_attribute<std::string>(XMLElement* element, const char* name, std::string& var) {
		const char* raw_string = nullptr;
		XMLError result = element->QueryStringAttribute(name, &raw_string);

		// safely wrap the c string into a c++ string
		var = std::string(raw_string ? raw_string : "");

		// return the error code (or success code)
		return result;
	}

	/* Assuming the element passed in does contain
	   a size element, this will load the width 
	   and height with the values of the element */
	bool load_size_element(XMLElement* element, unsigned int& width, unsigned int& height) {
		// get the width and height from the size element
		XMLCheckResult(element->QueryUnsignedAttribute("width", &width));
		XMLCheckResult(element->QueryUnsignedAttribute("height", &height));

		return true;
	}

	/* Assuming the element passed in does contain
	   a location element, this will load the x
	   and y with the values of the element */
	bool load_location_element(XMLElement* element, unsigned int& x, unsigned int& y) {
		// get the width and height from the size element
		XMLCheckResult(element->QueryUnsignedAttribute("x", &x));
		XMLCheckResult(element->QueryUnsignedAttribute("y", &y));

		return true;
	}
}