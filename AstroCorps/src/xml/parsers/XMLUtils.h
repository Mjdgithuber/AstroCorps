#ifndef __XML__UTILS__H__
#define __XML__UTILS__H__

#include "Core.h"
#include "xml\tinyxml2.h"

////////////////////////////////////////////////////////////
/// The XML namespace serves as an API to allow easy 
/// interfacing with the TinyXML2 library, which is now
/// included as a source (cpp) file for better debugging.
/// NO other namespace should use TinyXML2 directly
////////////////////////////////////////////////////////////
namespace XML {
	using namespace tinyxml2;

	#ifndef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { LOG_ERROR("XML Error: %i\n", a_eResult); return false; }
	#endif
	#ifndef XMLNullCheck
		#define XMLNullCheck(ptr, error) if(ptr == nullptr) { LOG_ERROR("XML Null Ptr Error: %i\n", error); }
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
	/// Will attempt to load a floating point number into the 
	/// passed in float. Returns an indication of success
	/// Params:
	/// element - The element that contains the attribute
	/// f_name - The name of the float attribute
	/// f - The float that you want the return value to be in
	////////////////////////////////////////////////////////////
	bool load_float(XMLElement* element, const char* f_name, float& f);
	
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

#endif