#pragma once

#include <SFML/System.hpp>

namespace nf {
	const float pi = 3.14159f;

	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	const std::string BackgroundTextureName = "media/textures/background.png";

	const float DefaultGravity = 1000.f;

	const nf::Vector2f BallStartPosition(960.f, 540.f), BallStartSpeed(1500.f, 1500.f);
	const float BallDefaultRadius = 25.f, BallDefaultMass = 1.f, BallDefaultBounceCoefficient = 0.8f;
	const std::string BallTextureName = "media/textures/ball.png";

	enum class PlayerSide {Left, Right};
}