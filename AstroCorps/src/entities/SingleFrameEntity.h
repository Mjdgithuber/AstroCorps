#ifndef __SINGLE__FRAME__ENTITY__
#define __SINGLE__FRAME__ENTITY__

#include "MovableEntity.h"

class SingleFrameEntity : public MovableEntity {
protected:
	sf::Texture m_static_texture;
public:
	SingleFrameEntity(unsigned int entity_size, unsigned int tile_x, 
		              unsigned int tile_y, const std::string& filename);
};

#endif