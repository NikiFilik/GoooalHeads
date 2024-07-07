#pragma once

#include <SFML/System.hpp>

namespace nf {
	const float pi = 3.14159f;

	enum class GameMode {PvP, P2vP2, PvE};

	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	const std::string BackgroundTextureName = "media/textures/background.png";

	const nf::Vector2f DefaultGravity(0.f, 1000.f);

	const nf::Vector2f BallStartPosition(960.f, 540.f), BallStartSpeed(0.f, 0.f);
	const float BallDefaultRadius = 25.f, BallDefaultMass = 1.f, BallDefaultBounceCoefficient = 0.8f;
	const std::string BallTextureName = "media/textures/ball.png";

	enum class PlayerSide {Left, Right};
	const float PlayerDefaultMaxXSpeed = 600.f;
	const float PlayerDefaultBoost = 2000.f;
	const float PlayerDefaultJumpForce = 500.f;
	const nf::Vector2f LeftPlayerStartPosition(540.f, 810.f), RightPlayerStartPosition(1380.f, 810.f);
	const nf::Vector2f PlayerStartSpeed(0.f, 0.f);
	const float PlayerDefaultRadius = 50.f, PlayerDefaultMass = 4.f, PlayerDefaultBounceCoefficient = 0.f;
	const std::string LeftPlayerTextureName = "media/textures/playerLeft.png", RightPlayerTextureName = "media/textures/playerRight.png";
}