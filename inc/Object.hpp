#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2f.hpp"
#include "globalConsts.hpp"

namespace nf {
	class Object {
	protected:
		nf::Vector2f mPosition, mSpeed;
		float mRadius, mMass, mBounceCoefficient;
		sf::Sprite mSprite;
		const sf::Texture* mTexture;
	public:
		Object() = default;
		Object(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const float bounceCoefficient, const sf::Texture* texture);

		void setup(const nf::Vector2f& position, const nf::Vector2f& speed, const float radius,
			const float mass, const float bounceCoefficient, const sf::Texture* texture);

		void setPosition(const nf::Vector2f& position);
		void setSpeed(const nf::Vector2f& speed);
		void setRadius(const float radius);
		void setMass(const float mass);
		void setBounceCoefficient(const float bounceCoefficient);
		void setSprite(const sf::Sprite& sprite);
		void setTexture(const sf::Texture* texture);

		const nf::Vector2f& getPosition() const;
		const nf::Vector2f& getSpeed() const;
		const float getRadius() const;
		const float getMass() const;
		const float getBounceCoefficient() const;
		const sf::Sprite& getSprite() const;

		virtual void update(const sf::Time& deltaTime);

		virtual bool isColliding(const Object& other) const;
		void resolveCollision(Object& other);

		bool isColliding(const nf::Vector2f& a, const nf::Vector2f& b) const;
		void resolveCollision(const nf::Vector2f& a, const nf::Vector2f& b);
	};
}