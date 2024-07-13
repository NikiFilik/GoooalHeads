#include "Player.hpp"

namespace nf {
	void Player::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, const float bounceCoefficient, const sf::Texture* texture, 
		const nf::PlayerSide side, const sf::Keyboard::Key moveLeftKey, const sf::Keyboard::Key moveRightKey, const sf::Keyboard::Key jumpKey, const sf::Keyboard::Key kickKey, const sf::Texture* legTexture) {
		Object::setup(position, speed, radius, mass, bounceCoefficient, texture);
		mSide = side;
		mMoveLeftKey = moveLeftKey;
		mMoveRightKey = moveRightKey;
		mJumpKey = jumpKey;
		mKickKey = kickKey;

		mLeg.setPosition(mPosition);
		mLeg.setSpeed(mSpeed);
		mLeg.setRadius(LegDefaulRadius);
		mLeg.setMass(LegDefaultMass);
		mLeg.setBounceCoefficient(LegDefaultBounceCoefficient);
		mLeg.setTexture(legTexture);
		mLeg.setOrigin(nf::Vector2f(LegDefaulRadius, LegDefaulRadius));
	}

	void Player::setMoveLeftKey(const sf::Keyboard::Key& moveLeftKey) { mMoveLeftKey = moveLeftKey; }
	void Player::setMoveRightKey(const sf::Keyboard::Key& moveRightKey) { mMoveRightKey = moveRightKey; }
	void Player::setJumpKey(const sf::Keyboard::Key& jumpKey) { mJumpKey = jumpKey; }
	void Player::setKickKey(const sf::Keyboard::Key& kickKey) { mKickKey = kickKey; }
	void Player::setIsMovingLeft(const bool isMovingLeft) { mIsMovingLeft = isMovingLeft; }
	void Player::setIsMovingRight(const bool isMovingRight) { mIsMovingRight = isMovingRight; }
	void Player::setIsJumping(const bool isJumping) { mIsJumping = isJumping; }
	void Player::setIsKicking(const bool isKicking) { mIsKicking = isKicking; }
	void Player::setMaxXSpeed(const float maxXSpeed) { mMaxXSpeed = maxXSpeed; }
	void Player::setBoost(const float boost) { mBoost = boost; }
	void Player::setJumpForce(const float jumpForce) { mJumpForce = jumpForce; }

	const sf::Keyboard::Key Player::getMoveLeftKey() const { return mMoveLeftKey; }
	const sf::Keyboard::Key Player::getMoveRightKey() const { return mMoveRightKey; }
	const sf::Keyboard::Key Player::getJumpKey() const { return mJumpKey; }
	const sf::Keyboard::Key Player::getKickKey() const { return mKickKey; }
	const bool Player::getIsMovingLeft() const { return mIsMovingLeft; }
	const bool Player::getIsMovingRight() const { return mIsMovingRight; }
	const bool Player::getIsJumping() const { return mIsJumping; }
	const bool Player::getIsKickng() const { return mIsKicking; }
	const float Player::getMaxXSpeed() const { return mMaxXSpeed; }
	const float Player::getBoost() const { return mBoost; }
	const float Player::getJumpForce() const { return mJumpForce; }
	nf::Object Player::getLeg() { return mLeg;  }
	nf::PlayerSide Player::getSide() { return mSide; }
	const float Player::getLegAngle() { return mLegAngle; }

	void Player::update(const sf::Time& deltaTime) {
		Object::update(deltaTime);
		legUpdate();

		if (mSpeed.x > 0.f) {
			mSpeed.x = std::max(0.f, mSpeed.x - mBoost * deltaTime.asSeconds());
		}
		if (mSpeed.x < 0.f) {
			mSpeed.x = std::min(0.f, mSpeed.x + mBoost * deltaTime.asSeconds());
		}

		if (mSide == nf::PlayerSide::Left) {
			mLegAngle += mLegKickSpeed * deltaTime.asSeconds();
		}
		else {
			mLegAngle -= mLegKickSpeed * deltaTime.asSeconds();
		}

		if (mIsMovingLeft == true) {
			moveLeft(deltaTime);
		}
		if (mIsMovingRight == true) {
			moveRight(deltaTime);
		}
		if (mIsKicking == true) {
			doKick(deltaTime);
		}

		if (mSide == nf::PlayerSide::Right) {
			if (mLegAngle <= 60.f) {
				mLegAngle = 60.f;
				mLeg.setSpeed(mSpeed);
			}
			if (mLegAngle >= 179.f) {
				mLegAngle = 179.f;
				mLeg.setSpeed(mSpeed);
			}
		}
		if (mSide == nf::PlayerSide::Left) {
			if (mLegAngle <= 1.f) {
				mLegAngle = 1.f;
				mLeg.setSpeed(mSpeed);
			}
			if (mLegAngle >= 120.f) {
				mLegAngle = 120.f;
				mLeg.setSpeed(mSpeed);
			}
		}

		if (mSpeed.x != 0.f) {
			mSprite.setRotation(mSpeed.x / mMaxXSpeed * -15.f);
		}
		else {
			mSprite.setRotation(0.f);
		}

		mSprite.setScale(1.f, 1.f + std::abs(mSpeed.y) / 3000.f);
	}

	void Player::legUpdate() {
		mLeg.setPosition(mPosition + nf::Vector2f((mRadius + mLeg.getRadius()) * std::cos(mLegAngle / 180.f * pi), (mRadius + mLeg.getRadius()) * std::sin(mLegAngle / 180.f * pi)));
		mLeg.setRotation(mLegAngle + 270.f);
		if (mSide == nf::PlayerSide::Right) {
			if (mIsKicking == true) {
				mLeg.setSpeed(mSpeed + nf::Vector2f(mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::cos((mLegAngle + 90.f) / 180.f * pi), mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::sin((mLegAngle + 90.f) / 180.f * pi)));
			}
			else {
				mLeg.setSpeed(mSpeed + nf::Vector2f(mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::cos((mLegAngle - 90.f) / 180.f * pi), mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::sin((mLegAngle - 90.f) / 180.f * pi)));
			}
		}
		if (mSide == nf::PlayerSide::Left) {
			if (mIsKicking == true) {
				mLeg.setSpeed(mSpeed + nf::Vector2f(mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::cos((mLegAngle - 90.f) / 180.f * pi), mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::sin((mLegAngle - 90.f) / 180.f * pi)));
			}
			else {
				mLeg.setSpeed(mSpeed + nf::Vector2f(mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::cos((mLegAngle + 90.f) / 180.f * pi), mLegKickSpeed * pi * (mRadius + mLeg.getRadius()) / 180.f * std::sin((mLegAngle + 90.f) / 180.f * pi)));
			}
		}
		if (mLegAngle > 360.f) {
			mLegAngle -= 360.f;
		}
		if (mLegAngle < 0.f) {
			mLegAngle += 360.f;
		}

	}

	void Player::moveLeft(const sf::Time& deltaTime) {
		mSpeed.x = std::max(-mMaxXSpeed, mSpeed.x - 2 * mBoost * deltaTime.asSeconds());
	}
	void Player::moveRight(const sf::Time& deltaTime) {
		mSpeed.x = std::min(mMaxXSpeed, mSpeed.x + 2 * mBoost * deltaTime.asSeconds());
	}
	void Player::doJump() {
		mSpeed.y -= mJumpForce;
	}
	void Player::doKick(const sf::Time& deltaTime) {
		if (mSide == nf::PlayerSide::Left) {
			mLegAngle -= 2 * mLegKickSpeed * deltaTime.asSeconds();
		}
		else {
			mLegAngle += 2 * mLegKickSpeed * deltaTime.asSeconds();
		}
	}
}