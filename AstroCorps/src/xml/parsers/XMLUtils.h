#ifndef __XML__UTILS__H__
#define __XML__UTILS__H__

#include "Core.h"
#include "libs/tinyxml/tinyxml2.h"

////////////////////////////////////////////////////////////
/// The XML namespace serves as an API to allow easy 
/// interfacing with the TinyXML2 library, which is now
/// included as a source (cpp) file for better debugging.
/// NO other namespace should use TinyXML2 directly
////////////////////////////////////////////////////////////
namespace XML {
	using namespace tinyxml2;

	#ifndef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { LOG_ERROR("XML Error: {0}\n", a_eResult); return false; }
	#endif
	#ifndef XMLNullCheck
		#define XMLNullCheck(ptr, error) if(ptr == nullptr) { LOG_ERROR("XML Null Ptr Error: {0}\n", error); }
	#endif

	////////////////////////////////////////////////////////////
	/// Will attempt to open an XML document into the passed in
	/// XMLDocument. If the filepath is invalid it will return
	/// a null XMLNode
	/// Params:
	/// doc - XMLDocument you want to load into
	/// filepath - Path to an XML file you want to load
	////////////////////////////////////////////////////////////
	XMLNode* load_xml_file(XMLDocument& doc, const char* filepath);

	////////////////////////////////////////////////////////////
	/// Will attempt to load an attribute with the into the
	/// varible passed in with the given type.
	/// Params:
	/// element - The element that contains the attribute
	/// name - The name of the attribute
	/// var - The varible that you want the return value to be in
	////////////////////////////////////////////////////////////
	template <typename T>
	XMLError load_attribute(XMLElement* element, const char* name, T& var);

	////////////////////////////////////////////////////////////
	/// Explicit template specialization of load_attribute
	/// so that it works properly with std::string
	/// NOTE: this must be declared here to tell the compiler
	/// that it exists and to not use the general function for
	/// the typename std::string
	/// Params:
	/// element - The element that contains the string attribute
	/// name - The name of the string attribute
	/// var - The varible that you want the return value to be in
	////////////////////////////////////////////////////////////
	template <>
	XMLError load_attribute<std::string>(XMLElement* element, const char* name, std::string& var);
	
	////////////////////////////////////////////////////////////
	/// Will attempt to load in a size from an element. Returns 
	/// an indication of success
	/// Params:
	/// element - The size element
	/// width & height - The return value of the function
	////////////////////////////////////////////////////////////
	bool load_size_element(XMLElement* element, unsigned int& width, unsigned int& height);

	////////////////////////////////////////////////////////////
	/// Will attempt to load in a location from an element. 
	/// Returns an indication of success
	/// Params:
	/// element - The location element
	/// x & y - The return value of the function
	////////////////////////////////////////////////////////////
	bool load_location_element(XMLElement* element, unsigned int& x, unsigned int& y);
}

#include "XMLUtils.hpp"

#endif