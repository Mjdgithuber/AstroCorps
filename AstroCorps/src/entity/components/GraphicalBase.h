#ifndef __GRAPHICAL__BASE__H__
#define __GRAPHICAL__BASE__H__

#include "Component.h"

class GraphicalBase : public Component {
private:
	sf::Sprite m_sprite;
public:
	Flag update(const sf::Time& delta_time) override;
	std::string get_base_name() final;

	void set_position(float x, float y);
	void set_scale(float x_sf, float y_sf);
	
	sf::Sprite& get_sprite();
};

#endif