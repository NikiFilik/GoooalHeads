#include "Object.hpp"

#include "functions.hpp"

namespace nf {
	Object::Object(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, const float bounceCoefficient, const sf::Texture* texture): 
		mPosition(position), mSpeed(speed), mRadius(radius), mMass(mass), mBounceCoefficient(bounceCoefficient), mTexture(texture) {
		mSprite.setTexture(*mTexture);
		mSprite.setOrigin(mRadius, mRadius);
		mSprite.setPosition(mPosition);
	}

	void Object::setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius, const float mass, const float bounceCoefficient, const sf::Texture* texture) {
		mPosition = position;
		mSpeed = speed;
		mRadius = radius;
		mMass = mass;
		mBounceCoefficient = bounceCoefficient;
		mTexture = texture;
		mSprite.setTexture(*mTexture);
		mSprite.setOrigin(mRadius, mRadius);
		mSprite.setPosition(mPosition);
	}

	void Object::setPosition(const nf::Vector2f& position) {
		mPosition = position;
		mSprite.setPosition(mPosition);
	}
	void Object::setSpeed(const nf::Vector2f& speed) {
		mSpeed = speed;
	}
	void Object::setRadius(const float radius) {
		mRadius = radius;
	}
	void Object::setMass(const float mass) {
		mMass = mass;
	}
	void Object::setBounceCoefficient(const float bounceCoefficient) {
		mBounceCoefficient = bounceCoefficient;
	}
	void Object::setSprite(const sf::Sprite& sprite) {
		mSprite = sprite;
	}
	void Object::setTexture(const sf::Texture* texture) {
		mTexture = texture;
		mSprite.setTexture(*mTexture);
	}

	const nf::Vector2f& Object::getPosition() const {
		return mPosition;
	}
	const nf::Vector2f& Object::getSpeed() const {
		return mSpeed;
	}
	const float Object::getRadius() const {
		return mRadius;
	}
	const float Object::getMass() const {
		return mMass;
	}
	const float Object::getBounceCoefficient() const {
		return mBounceCoefficient;
	}
	const sf::Sprite& Object::getSprite() const {
		return mSprite;
	}

	void Object::update(const sf::Time& deltaTime) {
		mPosition += mSpeed * deltaTime.asSeconds();
		mSprite.setPosition(mPosition);
	}

	bool Object::isColliding(const Object& other) const {
		nf::Vector2f deltaPosition = mPosition - other.getPosition();
		if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(mRadius + other.getRadius(), 2.f)) {
			nf::Vector2f deltaSpeed = mSpeed - other.getSpeed();
			if (deltaPosition.x * deltaSpeed.x + deltaPosition.y * deltaSpeed.y <= 0) {
				return true;
			}
		}
		return false;
	}
	void Object::resolveCollision(Object& other) {
		//https://www.vobarian.com/collisions/2dcollisions2.pdf

		nf::Vector2f deltaPosition = other.getPosition() - mPosition;

		float distance = deltaPosition.length();
		float requiredDistance = mRadius + other.getRadius();

		nf::Vector2f unitNormalVector = deltaPosition.normalized();
		nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

		mPosition -= unitNormalVector * ((requiredDistance - distance) / 2.f);
		other.setPosition(other.getPosition() + unitNormalVector * ((requiredDistance - distance) / 2.f));

		float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, mSpeed);
		float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, mSpeed);
		float otherNormalSpeed = nf::scalarMultiplication(unitNormalVector, other.getSpeed());
		float otherTangentSpeed = nf::scalarMultiplication(unitTangentVector, other.getSpeed());

		float newThisNormalSpeed, newOtherNormalSpeed;
		nf::resolveOneDimensionalCollision(mMass, other.getMass(), thisNormalSpeed, otherNormalSpeed, newThisNormalSpeed, newOtherNormalSpeed);

		mSpeed = unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed;
		other.setSpeed(unitNormalVector * newOtherNormalSpeed + unitTangentVector * otherTangentSpeed);
	}

	bool Object::isColliding(const nf::Vector2f& a, const nf::Vector2f& b) const {
		float A = b.y - a.y, B = a.x - b.x, C = (a.y - b.y) * a.x + (b.x - a.x) * a.y;
		float distance = std::abs(A * mPosition.x + B * mPosition.y + C) / std::sqrt(A * A + B * B);

		if (distance < mRadius && ((mPosition.x < a.x && mPosition.x > b.x) || (mPosition.x > a.x && mPosition.x < b.x) || (mPosition.y < a.y && mPosition.y > b.y) || (mPosition.y > a.y && mPosition.y < b.y))) {
			return true;
			/*if (A != 0.f) {
				float D = std::pow(((2.f * B * C) / (A * A)) + ((2.f * B * mPosition.x) / A) - (2.f * mPosition.y), 2) - 4.f * (((B * B) / (A * A)) + 1.f) * (((C * C) / (A * A)) + ((2.f * C * mPosition.x) / A) + (mPosition.x * mPosition.x) + (mPosition.y * mPosition.y) - (mRadius * mRadius));
				if (D >= 0.f) {
					float Y1 = (-((2.f * B * C) / (A * A)) + ((2.f * B * mPosition.x) / A) - (2.f * mPosition.y) + std::sqrt(D)) / (2.f * (((B * B) / (A * A)) + 1.f) * (((C * C) / (A * A))));
					float Y2 = (-((2.f * B * C) / (A * A)) + ((2.f * B * mPosition.x) / A) - (2.f * mPosition.y) - std::sqrt(D)) / (2.f * (((B * B) / (A * A)) + 1.f) * (((C * C) / (A * A))));
					float X1 = -((B * Y1 + C) / A);
					float X2 = -((B * Y2 + C) / A);
					if ((X1 < a.x && X1 > b.x && Y1 < a.y && Y1 > b.y) || (X1 > a.x && X1 < b.x && Y1 > a.y && Y1 < b.y) || (X2 < a.x && X2 > b.x && Y2 < a.y && Y2 > b.y) || (X2 > a.x && X2 < b.x && Y2 > a.y && Y2 < b.y)) {
						return true;
					}
				}
			}*/
		}
		return false;
	}
	void Object::resolveCollision(const nf::Vector2f& a, const nf::Vector2f& b) {
		float A = b.y - a.y, B = a.x - b.x, C = (a.y - b.y) * a.x + (b.x - a.x) * a.y;
		float distance = std::abs(A * mPosition.x + B * mPosition.y + C) / std::sqrt(A * A + B * B);

		nf::Vector2f unitNormalVector = nf::Vector2f(b - a).normalized();
		nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

		float normalSpeed = nf::scalarMultiplication(unitNormalVector, mSpeed);
		float tangentSpeed = nf::scalarMultiplication(unitTangentVector, mSpeed);

		if (std::abs(A * (mPosition.x + unitTangentVector.x) + B * (mPosition.y + unitTangentVector.y) + C) / std::sqrt(A * A + B * B) > distance) {
			mPosition += unitTangentVector * (mRadius - distance);
		}
		else {
			mPosition -= unitTangentVector * (mRadius - distance);
		}
		mSpeed = unitNormalVector * normalSpeed - unitTangentVector * tangentSpeed * mBounceCoefficient;
	}
}