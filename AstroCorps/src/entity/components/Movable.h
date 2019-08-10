#ifndef __MOVABLE__H__
#define __MOVABLE__H__

#include "Transform.h"
#include "util\Util.h"

class Movable : public Transform {
private:
	bool m_moving;
	float m_speed;

	Util::Direction m_curr_dir;
	Util::Direction m_next_dir;
	sf::Time m_elap; // elasped movement time

	unsigned int m_prev_x;
	unsigned int m_prev_y;

	int get_hor_offset(Util::Direction dir) const;
	int get_vert_offset(Util::Direction dir) const;
	bool check_percentage(float& percentage);
public:
	Movable(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float speed);

	Flag update(const sf::Time& delta_time) override;

	bool set_movement(Util::Direction dir = Util::STATIONARY);

	bool is_moving() const;
};

#endif