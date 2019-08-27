#include "XMLUtils.h"

namespace Engine {
	namespace XML {

		/* Given a filepath it will attempt (if filepath is valid)
		   to load it into the passed in XMLDocument. It will also
		   get the root node and return it. NOTE: all XML files
		   must have a node otherwise it is malformed*/
		XMLNode* load_xml_file(XMLDocument& doc, const char* filepath) {
			// attempt to load file
			XMLError eResult = doc.LoadFile(filepath);
			LOG_IF_AR(CRIT_LEVEL, eResult != XML_SUCCESS, "Failed to load XML Doc '{0}'",
				filepath);

			// get the root of the document
			XMLNode* root = doc.FirstChild();
			LOG_IF_AR(CRIT_LEVEL, root == nullptr, "Failed to get root of XML file '{0}'",
				filepath);

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
			LOG_IF_AR(CRIT_LEVEL, element->QueryUnsignedAttribute("width", &width) != XML_SUCCESS,
				"Attempted To Load Size Element With No width Tag");
			LOG_IF_AR(CRIT_LEVEL, element->QueryUnsignedAttribute("height", &height) != XML_SUCCESS,
				"Attempted To Load Size Element With No height Tag");

			return true;
		}

		/* Assuming the element passed in does contain
		   a location element, this will load the x
		   and y with the values of the element */
		bool load_location_element(XMLElement* element, unsigned int& x, unsigned int& y) {
			// get the width and height from the size element
			LOG_IF_AR(CRIT_LEVEL, element->QueryUnsignedAttribute("x", &x) != XML_SUCCESS,
				"Attempted To Load Location Element With No x Tag");
			LOG_IF_AR(CRIT_LEVEL, element->QueryUnsignedAttribute("y", &y) != XML_SUCCESS,
				"Attempted To Load Location Element With No y Tag");

			return true;
		}
	}
}