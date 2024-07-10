#include "Game.hpp"

#include "functions.hpp"
#include "globalConsts.hpp"

namespace nf {
	Game::Game(nf::GameMode gameMode) : mWindow(sf::VideoMode(WindowWidth, WindowHeight), "GoooalHeads", sf::Style::Fullscreen) {
		mWindow.setVerticalSyncEnabled(true);

		mGameMode = gameMode;

		mTextureHolder.load(BackgroundTextureName);

		mTextureHolder.load(BallTextureName);

		mTextureHolder.load(LeftPlayerTextureName);
		mTextureHolder.load(RightPlayerTextureName);
		mTextureHolder.load(LeftLegTextureName);
		mTextureHolder.load(RightLegTextureName);

		mTextureHolder.load(LowGravityTextureName);
		mTextureHolder.load(BouncyBallTextureName);
		mTextureHolder.load(DeflatedBallTextureName);
		mTextureHolder.load(HighJumpTextureName);
		mTextureHolder.load(LowJumpTextureName);
		mTextureHolder.load(HighSpeedTextureName);
		mTextureHolder.load(LowSpeedTextureName);
		mTextureHolder.load(SmallGatesTextureName);
		mTextureHolder.load(BigGatesTextureName);


		mBackground.setTexture(*mTextureHolder.get(BackgroundTextureName));

		nf::Ball ball;
		ball.setup(BallStartPosition, BallStartSpeed, BallDefaultRadius, BallDefaultMass, BallDefaultBounceCoefficient, mTextureHolder.get(BallTextureName));
		mBalls.push_back(ball);

		if(mGameMode == nf::GameMode::PvP){
			nf::Player playerLeft, playerRight;
			playerLeft.setup(LeftPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftPlayerTextureName), 
				nf::PlayerSide::Left, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, mTextureHolder.get(LeftLegTextureName));
			playerRight.setup(RightPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightPlayerTextureName), 
				nf::PlayerSide::Right, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::P, mTextureHolder.get(RightLegTextureName));
			mPlayers.push_back(playerLeft);
			mPlayers.push_back(playerRight);
		}

		mBalls[0].setLastTouched(&mPlayers[0]);
	}





	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;
		sf::Time timeSinceLastBonusSpawn = sf::Time::Zero;
		while (mWindow.isOpen()) {
			mGoalFlag = false;
			startPosition();
			while (mWindow.isOpen() && (!mGoalFlag || mAfterGoalClock.getElapsedTime().asSeconds() < TimeAfterGoal)) {
				timeSinceLastUpdate = clock.restart();
				timeSinceLastFrame += timeSinceLastUpdate;
				timeSinceLastBonusSpawn += timeSinceLastUpdate;

				processInput();

				if (timeSinceLastBonusSpawn >= TimePerBonusSpawn) {
					timeSinceLastBonusSpawn = sf::Time::Zero;
					bonusSpawn();
				}

				update(timeSinceLastUpdate);

				if (timeSinceLastFrame >= TimePerFrame) {
					timeSinceLastFrame = sf::Time::Zero;
					render();
				}
			}
		}
	}





	void Game::processInput() {
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				processPlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				processPlayerInput(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				processPlayerInput(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				processPlayerInput(event.mouseButton.button, false);
				break;
			}
		}
	}

	void Game::processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed) {
		if (key == sf::Keyboard::Escape && isPressed) {
			mWindow.close();
		}

		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			if (key == iterPlayers->getMoveLeftKey()) {
				iterPlayers->setIsMovingLeft(isPressed);
			}
			if (key == iterPlayers->getMoveRightKey()) {
				iterPlayers->setIsMovingRight(isPressed);
			}
			if (key == iterPlayers->getJumpKey()) {
				iterPlayers->setIsJumping(isPressed);
			}
			if (key == iterPlayers->getKickKey()) {
				iterPlayers->setIsKicking(isPressed);
			}
			iterPlayers++;
		}
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
	}





	void Game::gravityEffect(const sf::Time& deltaTime) {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			iterBalls->setSpeed(iterBalls->getSpeed() + mGravity * deltaTime.asSeconds());
			iterBalls++;
		}

		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			iterPlayers->setSpeed(iterPlayers->getSpeed() + mGravity * deltaTime.asSeconds());
			iterPlayers++;
		}
	}
	void Game::collisionWithField() {
		for (int i = 1; i < 11; i++) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				if (iterBalls->isColliding(mField[i - 1], mField[i])) {
					iterBalls->resolveCollision(mField[i - 1], mField[i]);
				}
				iterBalls++;
			}

			auto iterPlayers = mPlayers.begin();
			while (iterPlayers != mPlayers.end()) {
				if (iterPlayers->isColliding(mField[i - 1], mField[i])) {
					iterPlayers->resolveCollision(mField[i - 1], mField[i]);
				}
				iterPlayers++;
			}
		}

		for (int i = 1; i < 4; i++) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				if (iterBalls->isColliding(mLeftGates[i - 1], mLeftGates[i])) {
					iterBalls->resolveCollision(mLeftGates[i - 1], mLeftGates[i]);
				}
				iterBalls++;
			}

			auto iterPlayers = mPlayers.begin();
			while (iterPlayers != mPlayers.end()) {
				if (iterPlayers->isColliding(mLeftGates[i - 1], mLeftGates[i])) {
					iterPlayers->resolveCollision(mLeftGates[i - 1], mLeftGates[i]);
				}
				iterPlayers++;
			}
		}

		for (int i = 1; i < 4; i++) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				if (iterBalls->isColliding(mRightGates[i - 1], mRightGates[i])) {
					iterBalls->resolveCollision(mRightGates[i - 1], mRightGates[i]);
				}
				iterBalls++;
			}

			auto iterPlayers = mPlayers.begin();
			while (iterPlayers != mPlayers.end()) {
				if (iterPlayers->isColliding(mRightGates[i - 1], mRightGates[i])) {
					iterPlayers->resolveCollision(mRightGates[i - 1], mRightGates[i]);
				}
				iterPlayers++;
			}
		}
	}
	void Game::collisionBallsWithBalls() {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end() - 1) {
			auto jterBalls = iterBalls + 1;
			while (jterBalls != mBalls.end()) {
				if (iterBalls->isColliding(*jterBalls)) {
					iterBalls->resolveCollision(*jterBalls);
				}
				jterBalls++;
			}
			iterBalls++;
		}
	}
	void Game::collisionPlayersWithPlayers() {
		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end() - 1) {
			auto jterPlayers = iterPlayers + 1;
			while (jterPlayers != mPlayers.end()) {
				if (iterPlayers->isColliding(*jterPlayers)) {
					iterPlayers->resolveCollision(*jterPlayers);
				}
				jterPlayers++;
			}
			iterPlayers++;
		}
	}
	void Game::collisionBallsWithPlayers() {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			auto iterPlayers = mPlayers.begin();
			while (iterPlayers != mPlayers.end()) {
				if (iterBalls->isColliding(*iterPlayers)) {
					iterBalls->resolveCollision(*iterPlayers);
					iterBalls->setLastTouched(&(*iterPlayers));
				}
				if (iterBalls->isColliding(iterPlayers->getLeg())) {
					iterBalls->resolveCollision(iterPlayers->getLeg());
					iterBalls->setLastTouched(&(*iterPlayers));
				}
				iterPlayers++;
			}
			iterBalls++;
		}
	}
	void Game::processPlayersJumps() {
		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			auto jterPlayers = mPlayers.begin();
			bool canJumpFromAnotherPlayer = false;

			while (jterPlayers != mPlayers.end()) {
				if (iterPlayers != jterPlayers) {
					if (jterPlayers->getPosition().y >= 910.f && iterPlayers->isColliding(*jterPlayers)) {
						canJumpFromAnotherPlayer = true;
					}
				}
				jterPlayers++;
			}

			if ((iterPlayers->getPosition().y >= 910.f || canJumpFromAnotherPlayer) && iterPlayers->getIsJumping()) {
				iterPlayers->doJump();
			}
			iterPlayers++;
		}
	}
	void Game::update(const sf::Time& deltaTime) {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			iterBalls->update(deltaTime);
			iterBalls++;
		}

		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			iterPlayers->update(deltaTime);
			iterPlayers++;
		}

		gravityEffect(deltaTime);
		collisionWithField();
		processPlayersJumps();
		collisionBallsWithBalls();
		collisionPlayersWithPlayers();
		collisionBallsWithPlayers();

		goalCheck();

		iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			auto iterBonuses = mBonuses.begin();
			while (iterBonuses != mBonuses.end()) {
				if (iterBalls->isColliding(*iterBonuses)) {
					bonusActivator(iterBonuses->getBonusType(), *iterBalls);
					iterBonuses = mBonuses.erase(iterBonuses);
				}
				else {
					iterBonuses++;
				}
			}
			iterBalls++;
		}

		bonusDeactivator();
	}





	void Game::render() {
		mWindow.clear();
		mWindow.draw(mBackground);

		auto iterBonuses = mBonuses.begin();
		while (iterBonuses != mBonuses.end()) {
			mWindow.draw(iterBonuses->getSprite());
			iterBonuses++;
		}

		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			mWindow.draw(iterBalls->getSprite());
			iterBalls++;
		}

		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			mWindow.draw(iterPlayers->getSprite());
			mWindow.draw(iterPlayers->getLeg().getSprite());
			iterPlayers++;
		}

		mWindow.display();
	}





	void Game::startPosition() {
		mBalls[0].setup(BallStartPosition, BallStartSpeed, BallDefaultRadius, BallDefaultMass, BallDefaultBounceCoefficient, mTextureHolder.get(BallTextureName));
		auto iterBalls = mBalls.begin() + 1;
		while (iterBalls != mBalls.end()) {
			mBalls.erase(iterBalls);
			iterBalls++;
		}

		if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
			mPlayers[0].setup(LeftPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftPlayerTextureName),
				nf::PlayerSide::Left, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, mTextureHolder.get(LeftLegTextureName));
			mPlayers[1].setup(RightPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightPlayerTextureName),
				nf::PlayerSide::Right, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::P, mTextureHolder.get(RightLegTextureName));
		}

		mLeftGates[0].y = 660.f;
		mLeftGates[1].y = 660.f;
		mLeftGates[2].y = 670.f;
		mLeftGates[3].y = 670.f;

		mRightGates[0].y = 660.f;
		mRightGates[1].y = 660.f;
		mRightGates[2].y = 670.f;
		mRightGates[3].y = 670.f;

		mBonuses.clear();
	}
	void Game::goalCheck() {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			if (iterBalls->getPosition().x < mLeftGates[1].x && iterBalls->getPosition().y > mLeftGates[2].y) {
				if (mGoalFlag == false) {
					mAfterGoalClock.restart();
				}
				mGoalFlag = true;
				mLastGoal = nf::PlayerSide::Left;
			}
			if (iterBalls->getPosition().x > mRightGates[1].x && iterBalls->getPosition().y > mRightGates[2].y) {
				if (mGoalFlag == false) {
					mAfterGoalClock.restart();
				}
				mGoalFlag = true;
				mLastGoal = nf::PlayerSide::Right;
			}
			iterBalls++;
		}
	}





	void Game::bonusSpawn() {
		nf::BonusType type;
		type = nf::BonusType(nf::randIntFromRange(0, int(nf::BonusType::Count) - 1));
		nf::Bonus bonus;
		if (type == nf::BonusType::LowGravity) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowGravityTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::BouncyBall) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(BouncyBallTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::DeflatedBall) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(DeflatedBallTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::HighJump) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(HighJumpTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::LowJump) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowJumpTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::HighSpeed) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(HighSpeedTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::LowSpeed) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowSpeedTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::SmallGates) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(SmallGatesTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::BigGates) {
			bonus.setup(nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720)), BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(BigGatesTextureName));
			bonus.setBonusType(type);
		}
		mBonuses.push_back(bonus);
	}





	void Game::bonusActivator(nf::BonusType type, nf::Ball& ball) {
		if (type == nf::BonusType::LowGravity) {
			mGravity = LowGravity;
			mLowGravityClock.restart();
		}
		if (type == nf::BonusType::BouncyBall) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(BouncyBallBounceCoefficient);
				iterBalls++;
			}
			mBouncyBallClock.restart();
		}
		if (type == nf::BonusType::DeflatedBall) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(DeflatedBallBounceCoefficient);
				iterBalls++;
			}
			mDeflatedBallClock.restart();
		}
		if (type == nf::BonusType::HighJump) {
			ball.getLastTouched()->setJumpForce(HighJumpForce);
			mHighJumpClock.restart();
		}
		if (type == nf::BonusType::LowJump) {
			ball.getLastTouched()->setJumpForce(LowJumpForce);
			mLowJumpClock.restart();
		}
		if (type == nf::BonusType::HighSpeed) {
			ball.getLastTouched()->setMaxXSpeed(HighSpeed);
			mHighSpeedClock.restart();
		}
		if (type == nf::BonusType::LowSpeed) {
			ball.getLastTouched()->setMaxXSpeed(LowSpeed);
			mLowSpeedClock.restart();
		}
		if (type == nf::BonusType::SmallGates) {
			if (ball.getLastTouched()->getSide() == nf::PlayerSide::Left) {
				mLeftGates[0].y = 780.f;
				mLeftGates[1].y = 780.f;
				mLeftGates[2].y = 790.f;
				mLeftGates[3].y = 790.f;
			}
			else {
				mRightGates[0].y = 780.f;
				mRightGates[1].y = 780.f;
				mRightGates[2].y = 790.f;
				mRightGates[3].y = 790.f;
			}
			mSmallGatesClock.restart();
		}
		if (type == nf::BonusType::BigGates) {
			if (ball.getLastTouched()->getSide() == nf::PlayerSide::Left) {
				mLeftGates[0].y = 540.f;
				mLeftGates[1].y = 540.f;
				mLeftGates[2].y = 550.f;
				mLeftGates[3].y = 550.f;
			}
			else {
				mRightGates[0].y = 540.f;
				mRightGates[1].y = 540.f;
				mRightGates[2].y = 550.f;
				mRightGates[3].y = 550.f;
			}
			mBigGatesClock.restart();
		}
	}
	void Game::bonusDeactivator() {
		if (mLowGravityClock.getElapsedTime() >= LowGravityTime && mGravity == LowGravity) {
			mGravity = DefaultGravity;
		}
		if (mBouncyBallClock.getElapsedTime() >= BouncyBallTime && mBalls[0].getBounceCoefficient() == BouncyBallBounceCoefficient) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(BallDefaultBounceCoefficient);
				iterBalls++;
			}
		}
		if (mDeflatedBallClock.getElapsedTime() >= DeflatedBallTime && mBalls[0].getBounceCoefficient() == DeflatedBallBounceCoefficient) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(BallDefaultBounceCoefficient);
				iterBalls++;
			}
		}
		if (mHighJumpClock.getElapsedTime() >= HighJumpTime) {
			if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
				if (mPlayers[0].getJumpForce() == HighJumpForce || mPlayers[1].getJumpForce() == HighJumpForce) {
					mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
				}
			}
			else {
				if (mPlayers[0].getJumpForce() == HighJumpForce || mPlayers[1].getJumpForce() == HighJumpForce || mPlayers[2].getJumpForce() == HighJumpForce || mPlayers[3].getJumpForce() == HighJumpForce) {
					mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[2].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[3].setJumpForce(PlayerDefaultJumpForce);
				}
			}
		}
		if (mLowJumpClock.getElapsedTime() >= LowJumpTime) {
			if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
				if (mPlayers[0].getJumpForce() == LowJumpForce || mPlayers[1].getJumpForce() == LowJumpForce) {
					mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
				}
			}
			else {
				if (mPlayers[0].getJumpForce() == LowJumpForce || mPlayers[1].getJumpForce() == LowJumpForce || mPlayers[2].getJumpForce() == LowJumpForce || mPlayers[3].getJumpForce() == LowJumpForce) {
					mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[2].setJumpForce(PlayerDefaultJumpForce);
					mPlayers[3].setJumpForce(PlayerDefaultJumpForce);
				}
			}
		}
		if (mHighSpeedClock.getElapsedTime() >= HighSpeedTime) {
			if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
				if (mPlayers[0].getMaxXSpeed() == HighSpeed || mPlayers[1].getMaxXSpeed() == HighSpeed) {
					mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
				}
			}
			else {
				if (mPlayers[0].getMaxXSpeed() == HighSpeed || mPlayers[1].getMaxXSpeed() == HighSpeed || mPlayers[2].getMaxXSpeed() == HighSpeed || mPlayers[3].getMaxXSpeed() == HighSpeed) {
					mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[2].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[3].setMaxXSpeed(PlayerDefaultMaxXSpeed);
				}
			}
		}
		if (mLowSpeedClock.getElapsedTime() >= LowSpeedTime) {
			if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
				if (mPlayers[0].getMaxXSpeed() == LowSpeed || mPlayers[1].getMaxXSpeed() == LowSpeed) {
					mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
				}
			}
			else {
				if (mPlayers[0].getMaxXSpeed() == LowSpeed || mPlayers[1].getMaxXSpeed() == LowSpeed || mPlayers[2].getMaxXSpeed() == LowSpeed || mPlayers[3].getMaxXSpeed() == LowSpeed) {
					mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[2].setMaxXSpeed(PlayerDefaultMaxXSpeed);
					mPlayers[3].setMaxXSpeed(PlayerDefaultMaxXSpeed);
				}
			}
		}
		if (mSmallGatesClock.getElapsedTime() >= SmallGatesTime && (mLeftGates[0].y == 780.f || mRightGates[0].y == 780.f)) {
			mLeftGates[0].y = 660.f;
			mLeftGates[1].y = 660.f;
			mLeftGates[2].y = 670.f;
			mLeftGates[3].y = 670.f;

			mRightGates[0].y = 660.f;
			mRightGates[1].y = 660.f;
			mRightGates[2].y = 670.f;
			mRightGates[3].y = 670.f;
		}
		if (mBigGatesClock.getElapsedTime() >= BigGatesTime && (mLeftGates[0].y == 540.f || mRightGates[0].y == 540.f)) {
			mLeftGates[0].y = 660.f;
			mLeftGates[1].y = 660.f;
			mLeftGates[2].y = 670.f;
			mLeftGates[3].y = 670.f;

			mRightGates[0].y = 660.f;
			mRightGates[1].y = 660.f;
			mRightGates[2].y = 670.f;
			mRightGates[3].y = 670.f;
		}
	}
}