#pragma once

#include "Object.hpp"

#include "Player.hpp"

namespace nf {
	class Ball : public Object {
	protected:
		nf::Player* mLastTouched;
	public:
		void setLastTouched(nf::Player* lastTouched);

		nf::Player* getLastTouched();

		void update(const sf::Time& deltaTime) override;
	};
}