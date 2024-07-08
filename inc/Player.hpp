#pragma once

#include "Object.hpp"

namespace nf {
	class Player : public Object {
	protected:
		nf::PlayerSide mSide;
		sf::Keyboard::Key mMoveLeftKey, mMoveRightKey, mJumpKey, mKickKey;
		bool mIsMovingLeft = false, mIsMovingRight = false, mIsJumping = false, mIsKicking = false;
		float mMaxXSpeed = PlayerDefaultMaxXSpeed, mBoost = PlayerDefaultBoost, mJumpForce = PlayerDefaultJumpForce;

		nf::Object mLeg;
		float mLegAngle = 90.f;
		float mLegKickSpeed = LegDefautKickSpeed;

	public:
		void setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, const float bounceCoefficient, const sf::Texture* texture,
			const nf::PlayerSide side, const sf::Keyboard::Key moveLeftKey, const sf::Keyboard::Key moveRightKey, const sf::Keyboard::Key jumpKey, const sf::Keyboard::Key kickKey, const sf::Texture* legTexture);

		void setMoveLeftKey(const sf::Keyboard::Key& moveLeftKey);
		void setMoveRightKey(const sf::Keyboard::Key& moveRightKey);
		void setJumpKey(const sf::Keyboard::Key& jumpKey);
		void setKickKey(const sf::Keyboard::Key& kickKey);
		void setIsMovingLeft(const bool isMovingLeft);
		void setIsMovingRight(const bool isMovingRight);
		void setIsJumping(const bool isJumping);
		void setIsKicking(const bool isKicking);
		void setMaxXSpeed(const float maxXSpeed);
		void setBoost(const float boost);
		void setJumpForce(const float jumpForce);

		const sf::Keyboard::Key getMoveLeftKey() const;
		const sf::Keyboard::Key getMoveRightKey() const;
		const sf::Keyboard::Key getJumpKey() const;
		const sf::Keyboard::Key getKickKey() const;
		const bool getIsMovingLeft() const;
		const bool getIsMovingRight() const;
		const bool getIsJumping() const;
		const bool getIsKickng() const;
		const float getMaxXSpeed() const;
		const float getBoost() const;
		const float getJumpForce() const;
		nf::Object getLeg();

		void update(const sf::Time& deltaTime) override;

		void legUpdate();

		void moveLeft(const sf::Time& deltaTime);
		void moveRight(const sf::Time& deltaTime);
		void doJump();
		void doKick(const sf::Time& deltaTime);
	};
}