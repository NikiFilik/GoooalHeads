#pragma once

#include <SFML/System.hpp>

namespace nf {
	const float pi = 3.14159f;

	enum class GameMode {PvP = 1, P2vP2 = 2, PvE = 3};

	const int WindowWidth = 1920, WindowHeight = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	const std::string FontName = "media/fonts/PIXY.ttf";
	const std::string BackgroundTextureName = "media/textures/background.png";
	const std::string LeftGatesTextureName = "media/textures/gatesLeft.png";
	const std::string RightGatesTextureName = "media/textures/gatesRight.png";

	const nf::Vector2f DefaultGravity(0.f, 900.f);
	const sf::Time TimeAfterGoal = sf::seconds(3.f);

	const nf::Vector2f BallStartPosition(960.f, 540.f), BallStartSpeed(0.f, 0.f);
	const float BallDefaultRadius = 40.f, BallDefaultMass = 10.f, BallDefaultBounceCoefficient = 0.6f;
	const std::string BallTextureName = "media/textures/ball.png";

	enum class PlayerSide {Left, Right};
	const float PlayerDefaultMaxXSpeed = 500.f;
	const float PlayerDefaultBoost = 2000.f;
	const float PlayerDefaultJumpForce = 500.f;
	const nf::Vector2f LeftPlayerStartPosition(540.f, 910.f), RightPlayerStartPosition(1380.f, 910.f);
	const nf::Vector2f PlayerStartSpeed(0.f, 0.f);
	const float PlayerDefaultRadius = 75.f, PlayerDefaultMass = 40.f, PlayerDefaultBounceCoefficient = 0.f;
	const std::string LeftPlayerTextureName = "media/textures/playerLeft.png", RightPlayerTextureName = "media/textures/playerRight.png";
	const std::string LeftLeftPlayerTextureName = "media/textures/playerLeftLeft.png", RightRightPlayerTextureName = "media/textures/playerRightRight.png";

	const float LegDefaulRadius = 30.f;
	const float LegDefaultMass = 1.f;
	const float LegDefaultBounceCoefficient = 1.f;
	const float LegDefautKickSpeed = 1000.f;
	const std::string LeftLegTextureName = "media/textures/legLeft.png", RightLegTextureName = "media/textures/legRight.png";

	const sf::Time TimePerBonusSpawn = sf::seconds(5.0f);
	const float BonusRadius = 60.f;
	enum class BonusType {LowGravity = 0, BouncyBall = 1, DeflatedBall = 2, HighJump = 3, LowJump = 4, HighSpeed = 5, LowSpeed = 6, SmallGates = 7, BigGates = 8, Count = 9};

	const nf::Vector2f LowGravity(0.f, 500.f);
	const sf::Time LowGravityTime = sf::seconds(15.f);
	const std::string LowGravityTextureName = "media/textures/bonusLowGravity.png";

	const float BouncyBallBounceCoefficient = 0.95;
	const sf::Time BouncyBallTime = sf::seconds(9.f);
	const std::string BallBouncyTextureName = "media/textures/ballBouncy.png";
	const std::string BouncyBallTextureName = "media/textures/bonusBouncyBall.png";

	const float DeflatedBallBounceCoefficient = 0.2;
	const sf::Time DeflatedBallTime = sf::seconds(7.f);
	const std::string BallDeflatedTextureName = "media/textures/ballDeflated.png";
	const std::string DeflatedBallTextureName = "media/textures/bonusDeflatedBall.png";

	const float HighJumpForce = 650.f;
	const sf::Time HighJumpTime = sf::seconds(7.f);
	const std::string HighJumpTextureName = "media/textures/bonusHighJump.png";

	const float LowJumpForce = 250.f;
	const sf::Time LowJumpTime = sf::seconds(7.f);
	const std::string LowJumpTextureName = "media/textures/bonusLowJump.png";

	const float HighSpeed = 900.f;
	const sf::Time HighSpeedTime = sf::seconds(10.f);
	const std::string HighSpeedTextureName = "media/textures/bonusHighSpeed.png";

	const float LowSpeed = 300.f;
	const sf::Time LowSpeedTime = sf::seconds(10.f);
	const std::string LowSpeedTextureName = "media/textures/bonusLowSpeed.png";

	const sf::Time SmallGatesTime = sf::seconds(7.f);
	const std::string LeftSmallGatesTextureName = "media/textures/smallGatesLeft.png";
	const std::string RightSmallGatesTextureName = "media/textures/smallGatesRight.png";
	const std::string SmallGatesTextureName = "media/textures/bonusSmallGates.png";

	const sf::Time BigGatesTime = sf::seconds(7.f);
	const std::string LeftBigGatesTextureName = "media/textures/bigGatesLeft.png";
	const std::string RightBigGatesTextureName = "media/textures/bigGatesRight.png";
	const std::string BigGatesTextureName = "media/textures/bonusBigGates.png";

}