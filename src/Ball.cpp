#include "Ball.hpp"

namespace nf {
	void Ball::update(const sf::Time& deltaTime) {
		Object::update(deltaTime);
		mSpeed.y += DefaultGravity * deltaTime.asSeconds();
		mSprite.rotate((mSpeed.x * deltaTime.asSeconds() * 360) / (2 * pi * mRadius));
	}
}