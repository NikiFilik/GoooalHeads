#pragma once

#include "Object.hpp"

namespace nf {
	class Player : public Object {
	protected:
		nf::PlayerSide mSide;
		sf::Keyboard::Key mLeftKey, mRightKey, mJumpKey, mKickKey;

		//nf::Object mLeg;
	public:
	};
}