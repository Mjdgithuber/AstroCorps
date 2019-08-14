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
	/// Will attempt to load a floating point number into the 
	/// passed in float. Returns the status of the read
	/// Params:
	/// element - The element that contains the attribute
	/// f_name - The name of the float attribute
	/// f - The float that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_float(XMLElement* element, const char* f_name, float& f);

	////////////////////////////////////////////////////////////
	/// Will attempt to load a integer number into the passed
	/// in int. Returns the status of the read
	/// Params:
	/// element - The element that contains the attribute
	/// i_name - The name of the int attribute
	/// i - The int that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_int(XMLElement* element, const char* i_name, int& i);

	////////////////////////////////////////////////////////////
	/// Will attempt to load a string into the passed in string.
	/// Returns the status of the read
	/// Params:
	/// element - The element that contains the attribute
	/// s_name - The name of the string attribute
	/// s - The string that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_string(XMLElement* element, const char* s_name, std::string& s);

	////////////////////////////////////////////////////////////
	/// Wrapper for load_float function to allow for calling
	/// from a templated function. 
	/// Params:
	/// element - The element that contains the attribute
	/// name - The name of the attribute
	/// f - The float that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_attribute(XMLElement* element, const char* name, float& f);

	////////////////////////////////////////////////////////////
	/// Wrapper for load_int function to allow for calling
	/// from a templated function. 
	/// Params:
	/// element - The element that contains the attribute
	/// name - The name of the attribute
	/// i - The int that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_attribute(XMLElement* element, const char* name, int& i);

	////////////////////////////////////////////////////////////
	/// Wrapper for load_string function to allow for calling
	/// from a templated function. 
	/// Params:
	/// element - The element that contains the attribute
	/// name - The name of the attribute
	/// s - The string that you want the return value to be in
	////////////////////////////////////////////////////////////
	XMLError load_attribute(XMLElement* element, const char* name, std::string& s);
	
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