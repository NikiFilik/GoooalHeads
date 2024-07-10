#pragma once

#include <SFML/System.hpp>

namespace nf {
	const float pi = 3.14159f;

	enum class GameMode {PvP, P2vP2, PvE};

	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	const std::string BackgroundTextureName = "media/textures/background.png";

	const nf::Vector2f DefaultGravity(0.f, 1000.f);
	const float TimeAfterGoal = 1.5f;

	const nf::Vector2f BallStartPosition(960.f, 540.f), BallStartSpeed(0.f, 0.f);
	const float BallDefaultRadius = 25.f, BallDefaultMass = 10.f, BallDefaultBounceCoefficient = 0.6f;
	const std::string BallTextureName = "media/textures/ball.png";

	enum class PlayerSide {Left, Right};
	const float PlayerDefaultMaxXSpeed = 600.f;
	const float PlayerDefaultBoost = 2000.f;
	const float PlayerDefaultJumpForce = 500.f;
	const nf::Vector2f LeftPlayerStartPosition(540.f, 910.f), RightPlayerStartPosition(1380.f, 910.f);
	const nf::Vector2f PlayerStartSpeed(0.f, 0.f);
	const float PlayerDefaultRadius = 50.f, PlayerDefaultMass = 40.f, PlayerDefaultBounceCoefficient = 0.f;
	const std::string LeftPlayerTextureName = "media/textures/playerLeft.png", RightPlayerTextureName = "media/textures/playerRight.png";

	const float LegDefaulRadius = 20.f;
	const float LegDefaultMass = 1.f;
	const float LegDefaultBounceCoefficient = 1.f;
	const float LegDefautKickSpeed = 1000.f;
	const std::string LeftLegTextureName = "media/textures/legLeft.png", RightLegTextureName = "media/textures/legRight.png";

	const sf::Time TimePerBonusSpawn = sf::seconds(5.f);
	const float BonusRadius = 50.f;
	enum class BonusType {LowGravity = 0, BouncyBall = 1, DeflatedBall = 2, HighJump = 3, LowJump = 4, HighSpeed = 5, LowSpeed = 6, SmallGates = 7, BigGates = 8, Count = 9};

	const nf::Vector2f LowGravity(0.f, 500.f);
	const sf::Time LowGravityTime = sf::seconds(15.f);
	const std::string LowGravityTextureName = "media/textures/bonusLowGravity.png";

	const float BouncyBallBounceCoefficient = 0.9;
	const sf::Time BouncyBallTime = sf::seconds(7.f);
	const std::string BouncyBallTextureName = "media/textures/bonusBouncyBall.png";

	const float DeflatedBallBounceCoefficient = 0.3;
	const sf::Time DeflatedBallTime = sf::seconds(7.f);
	const std::string DeflatedBallTextureName = "media/textures/bonusDeflatedBall.png";

	const float HighJumpForce = 700.f;
	const sf::Time HighJumpTime = sf::seconds(7.f);
	const std::string HighJumpTextureName = "media/textures/bonusHighJump.png";

	const float LowJumpForce = 300.f;
	const sf::Time LowJumpTime = sf::seconds(7.f);
	const std::string LowJumpTextureName = "media/textures/bonusLowJump.png";

	const float HighSpeed = 900.f;
	const sf::Time HighSpeedTime = sf::seconds(7.f);
	const std::string HighSpeedTextureName = "media/textures/bonusHighSpeed.png";

	const float LowSpeed = 300.f;
	const sf::Time LowSpeedTime = sf::seconds(7.f);
	const std::string LowSpeedTextureName = "media/textures/bonusLowSpeed.png";

	const sf::Time SmallGatesTime = sf::seconds(7.f);
	const std::string SmallGatesTextureName = "media/textures/bonusSmallGates.png";

	const sf::Time BigGatesTime = sf::seconds(7.f);
	const std::string BigGatesTextureName = "media/textures/bonusBigGates.png";

}