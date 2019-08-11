#ifndef __TRANSFORM__H__
#define __TRANSFORM__H__

#include "Component.h"

class Transform : public Component {
protected:
	// tranform data (in tiles)
	unsigned int m_x;
	unsigned int m_y;
	unsigned int m_width;
	unsigned int m_height;
	float m_x_offset;
	float m_y_offset;
public:
	std::string get_base_name() final;

	Transform(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	unsigned int get_x() const;
	unsigned int get_y() const;
	unsigned int get_width() const;
	unsigned int get_height() const;
	float get_x_offset() const;
	float get_y_offset() const;
};

#endif