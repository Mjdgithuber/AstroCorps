#include "Util.h"

namespace util {
	bool colliding(const sf::Sprite& s1, const sf::Sprite& s2) {
		const sf::FloatRect& f1 = s1.getGlobalBounds();
		const sf::FloatRect& f2 = s2.getGlobalBounds();


		return f2.left <= f1.left + f1.width  && f2.left + f2.width >= f1.left &&
			f2.top <= f1.top + f1.height && f2.top + f2.height >= f1.top;

		//return f2.left <= f1.left + f1.width  && f2.left >= f1.left &&
			//f2.top <= f1.top + f1.height && f2.top >= f1.top;
	}
}