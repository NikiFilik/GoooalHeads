#pragma once

#include "Object.hpp"

namespace nf {
	class Ball : public Object {
	protected:

	public:
		void update(const sf::Time& deltaTime) override;
	};
}