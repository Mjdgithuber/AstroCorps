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

	/* Assuming the element contains a float, this will load
	   that float with the passed in attribute name */
	XMLError load_float(XMLElement* element, const char* f_name, float& f) {
		// get the width and height from the size element
		return element->QueryFloatAttribute(f_name, &f);
		//XMLCheckResult(element->QueryFloatAttribute(f_name, &f));

		//return true;
	}

	XMLError load_int(XMLElement* element, const char* i_name, int& i) {
		// get the width and height from the size element
		return element->QueryIntAttribute(i_name, &i);
		//XMLCheckResult(element->QueryFloatAttribute(f_name, &f));

		//return true;
	}

	XMLError load_string(XMLElement* element, const char* s_name, std::string& s) {
		// get the width and height from the size element

		const char* raw_string;
		XMLError result = element->QueryStringAttribute(s_name, &raw_string);
		
		s = std::string(raw_string);

		return result;
		//XMLCheckResult(element->QueryFloatAttribute(f_name, &f));

		//return true;
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