#ifndef __SINGLE__FRAME__ENTITY__
#define __SINGLE__FRAME__ENTITY__

#include "Entity.h"

class SingleFrameEntity : public Entity {
public:
	SingleFrameEntity(unsigned int entity_size, float tile_x, float tile_y, 
					  const std::string& filename, float speed = 0.0f);
};

#endif