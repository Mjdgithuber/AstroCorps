#ifndef __SINGLE__FRAME__ENTITY__
#define __SINGLE__FRAME__ENTITY__

#include "Entity.h"

class SingleFrameEntity : public Entity {
public:
	SingleFrameEntity(unsigned int entity_size, unsigned int tile_x, 
		              unsigned int tile_y, const std::string& filename);
};

#endif