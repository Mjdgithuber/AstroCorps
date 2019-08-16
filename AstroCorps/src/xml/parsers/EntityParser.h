#ifndef __ENTITY__PARSER__H__
#define __ENTITY__PARSER__H__

#include "XMLUtils.h"
#include "entity/components/IncludeComponents.h"

/* Forward declaration instead of including Entity.h
   is needed because Entity.h includes this header.
   This file cannot include Entity.h directly because 
   it would produce a circular dependency. */
class OldEntity;

namespace XML {

	////////////////////////////////////////////////////////////
	/// This will attempt to read a movable component from an
	/// xml element. It will return a new pointer to the component,
	/// if it wasn't able to be create it will return a nullptr
	/// Params:
	/// comp - The element with the movable component
	////////////////////////////////////////////////////////////
	Movable* read_movable_component(XMLElement* comp);

	////////////////////////////////////////////////////////////
	/// This will attempt to read a GraphicalBase component from 
	/// an xml element. It will return a new pointer to the 
	/// component, if it wasn't able to be create it will return 
	/// a nullptr
	/// Params:
	/// comp - The element with the GraphicalBase component
	////////////////////////////////////////////////////////////
	GraphicalBase* read_graphical_base_component(XMLElement* comp);

	////////////////////////////////////////////////////////////
	/// This will attempt to read a Transform component from 
	/// an xml element. It will return a new pointer to the 
	/// component, if it wasn't able to be create it will return
	/// a nullptr
	/// Params:
	/// comp - The element with the Transform component
	////////////////////////////////////////////////////////////
	Transform* read_transform_component(XMLElement* comp);


	////////////////////////////////////////////////////////////
	/// This will attempt to load an entity from an xml file
	/// containing its component information.
	/// Params:
	/// entity - The entity you want to add components to
	/// filepath - The xml file containing the components
	////////////////////////////////////////////////////////////
	bool load_entity(OldEntity* entity, const char* filepath);

}

#endif