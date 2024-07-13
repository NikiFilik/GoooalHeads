#include "Game.hpp"

#include "functions.hpp"
#include "globalConsts.hpp"
#include <iostream>

namespace nf {
	Game::Game(nf::GameMode gameMode, int maxNumOfGoals) : mWindow(sf::VideoMode(WindowWidth, WindowHeight), "GoooalHeads", sf::Style::Fullscreen) {
		mWindow.setVerticalSyncEnabled(true);

		mGameMode = gameMode;
		mMaxNumOfGoals = maxNumOfGoals;

		mFont.loadFromFile(FontName);

		mTextureHolder.load(BackgroundTextureName);
		mTextureHolder.load(LeftGatesTextureName);
		mTextureHolder.load(RightGatesTextureName);

		mTextureHolder.load(BallTextureName);

		mTextureHolder.load(LeftPlayerTextureName);
		mTextureHolder.load(RightPlayerTextureName);
		mTextureHolder.load(LeftLeftPlayerTextureName);
		mTextureHolder.load(RightRightPlayerTextureName);
		mTextureHolder.load(LeftLegTextureName);
		mTextureHolder.load(RightLegTextureName);

		mTextureHolder.load(LowGravityTextureName);
		mTextureHolder.load(BouncyBallTextureName);
		mTextureHolder.load(BallBouncyTextureName);
		mTextureHolder.load(DeflatedBallTextureName);
		mTextureHolder.load(BallDeflatedTextureName);
		mTextureHolder.load(HighJumpTextureName);
		mTextureHolder.load(LowJumpTextureName);
		mTextureHolder.load(HighSpeedTextureName);
		mTextureHolder.load(LowSpeedTextureName);
		mTextureHolder.load(SmallGatesTextureName);
		mTextureHolder.load(LeftSmallGatesTextureName);
		mTextureHolder.load(RightSmallGatesTextureName);
		mTextureHolder.load(BigGatesTextureName);
		mTextureHolder.load(LeftBigGatesTextureName);
		mTextureHolder.load(RightBigGatesTextureName);


		mBackground.setTexture(*mTextureHolder.get(BackgroundTextureName));
		mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftGatesTextureName));
		mRightGatesSprite.setTexture(*mTextureHolder.get(RightGatesTextureName));

		nf::Ball ball;
		ball.setup(BallStartPosition, BallStartSpeed, BallDefaultRadius, BallDefaultMass, BallDefaultBounceCoefficient, mTextureHolder.get(BallTextureName));
		mBalls.push_back(ball);

		if(mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE){
			nf::Player playerLeft, playerRight;
			playerLeft.setup(LeftPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftPlayerTextureName), 
				nf::PlayerSide::Left, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, mTextureHolder.get(LeftLegTextureName));
			playerRight.setup(RightPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightPlayerTextureName), 
				nf::PlayerSide::Right, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::P, mTextureHolder.get(RightLegTextureName));
			mPlayers.push_back(playerLeft);
			mPlayers.push_back(playerRight);
		}
		if (mGameMode == nf::GameMode::P2vP2) {
			nf::Player playerLeft, playerRight, playerLeftLeft, playerRightRight;
			playerLeft.setup(LeftPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftPlayerTextureName),
				nf::PlayerSide::Left, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, mTextureHolder.get(LeftLegTextureName));
			playerRight.setup(RightPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightPlayerTextureName),
				nf::PlayerSide::Right, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::P, mTextureHolder.get(RightLegTextureName));

			playerLeftLeft.setup(LeftPlayerStartPosition - nf::Vector2f(200.f, 0.f), PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftLeftPlayerTextureName),
				nf::PlayerSide::Left, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::Num6, sf::Keyboard::M, mTextureHolder.get(LeftLegTextureName));
			playerRightRight.setup(RightPlayerStartPosition + nf::Vector2f(200.f, 0.f), PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightRightPlayerTextureName),
				nf::PlayerSide::Right, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8, sf::Keyboard::Numpad0, mTextureHolder.get(RightLegTextureName));
			mPlayers.push_back(playerLeft);
			mPlayers.push_back(playerRight);
			mPlayers.push_back(playerLeftLeft);
			mPlayers.push_back(playerRightRight);
		}

		mBalls[0].setLastTouched(&mPlayers[0]);


		mTextScoreLeft.setFont(mFont);
		mTextScoreRight.setFont(mFont);
		mGoalText.setFont(mFont);

		mTextScoreLeft.setFillColor(sf::Color::White);
		mTextScoreRight.setFillColor(sf::Color::White);
		mGoalText.setFillColor(sf::Color::White);

		mTextScoreLeft.setOutlineColor(sf::Color::Black);
		mTextScoreRight.setOutlineColor(sf::Color::Black);
		mGoalText.setOutlineColor(sf::Color::Black);

		mTextScoreLeft.setOutlineThickness(4);
		mTextScoreRight.setOutlineThickness(4);
		mGoalText.setOutlineThickness(8);

		mTextScoreLeft.setCharacterSize(180);
		mTextScoreRight.setCharacterSize(180);
		mGoalText.setCharacterSize(300);

		mTextScoreLeft.setString(std::to_string(mScoreLeft));
		mTextScoreRight.setString(std::to_string(mScoreRight));
		mGoalText.setString(L"√ŒŒŒÀ!");

		sf::FloatRect textRect = mTextScoreLeft.getLocalBounds();
		mTextScoreLeft.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		mTextScoreLeft.setPosition(sf::Vector2f(120.f, 120.f));

		textRect = mTextScoreRight.getLocalBounds();
		mTextScoreRight.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		mTextScoreRight.setPosition(sf::Vector2f(1800.f, 120.f));

		textRect = mGoalText.getLocalBounds();
		mGoalText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		mGoalText.setPosition(sf::Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f));
	}





	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;
		sf::Time timeSinceLastBonusSpawn = sf::Time::Zero;
		while (mWindow.isOpen() && (mScoreLeft < mMaxNumOfGoals && mScoreRight < mMaxNumOfGoals)) {
			mGoalFlag = false;
			startPosition();
			while (mWindow.isOpen() && (!mGoalFlag || mAfterGoalClock.getElapsedTime().asSeconds() < TimeAfterGoal.asSeconds())) {
				timeSinceLastUpdate = clock.restart();
				timeSinceLastFrame += timeSinceLastUpdate;
				timeSinceLastBonusSpawn += timeSinceLastUpdate;

				processInput();
				if (mGameMode == nf::GameMode::PvE) {
					computerPlayerActions();
				}

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
			if (mScoreLeft == mMaxNumOfGoals) {
				std::cout << "À≈¬¿ﬂ  ŒÃ¿Õƒ¿ œŒ¡≈ƒ»À¿!" << std::endl;
			}
			if (mScoreRight == mMaxNumOfGoals) {
				std::cout << "œ–¿¬¿ﬂ  ŒÃ¿Õƒ¿ œŒ¡≈ƒ»À¿!" << std::endl;
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
				if (mGameMode != nf::GameMode::PvE || iterPlayers->getSide() == nf::PlayerSide::Right) {
					iterPlayers->setIsMovingLeft(isPressed);
				}
			}
			if (key == iterPlayers->getMoveRightKey()) {
				if (mGameMode != nf::GameMode::PvE || iterPlayers->getSide() == nf::PlayerSide::Right) {
					iterPlayers->setIsMovingRight(isPressed);
				}
			}
			if (key == iterPlayers->getJumpKey()) {
				if (mGameMode != nf::GameMode::PvE || iterPlayers->getSide() == nf::PlayerSide::Right) {
					iterPlayers->setIsJumping(isPressed);
				}
			}
			if (key == iterPlayers->getKickKey()) {
				if (mGameMode != nf::GameMode::PvE || iterPlayers->getSide() == nf::PlayerSide::Right) {
					iterPlayers->setIsKicking(isPressed);
				}
			}
			iterPlayers++;
		}
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
	}
	void Game::computerPlayerActions() {
		sf::Time timeToKick = sf::seconds(120.f / LegDefautKickSpeed);
		sf::Time timeToJumpPeak = sf::seconds(mPlayers[0].getJumpForce() / mGravity.y);
		float jumpPeak = mPlayers[0].getJumpForce() * timeToJumpPeak.asSeconds() - mGravity.y * timeToJumpPeak.asSeconds() * timeToJumpPeak.asSeconds() / 2.f;

		if (mBalls[0].getPosition().x - mBalls[0].getRadius() < mPlayers[0].getPosition().x + mPlayers[0].getRadius()) {
			mPlayers[0].setIsMovingLeft(true);
		}
		else {
			mPlayers[0].setIsMovingLeft(false);
		}

		if (mBalls[0].getPosition().x > 960.f && mPlayers[0].getPosition().x > 300.f) {
			mPlayers[0].setIsMovingLeft(true);
		}

		if (mBalls[0].getPosition().x - mBalls[0].getRadius() > mPlayers[0].getPosition().x + mPlayers[0].getRadius() && mBalls[0].getPosition().x < 960.f) {
			mPlayers[0].setIsMovingRight(true);
		}
		else {
			mPlayers[0].setIsMovingRight(false);
		}

		if ((mBalls[0].getPosition() + mBalls[0].getSpeed() * timeToJumpPeak.asSeconds()).y < mPlayers[0].getPosition().y - mPlayers[0].getRadius() && 
			(mBalls[0].getPosition() + mBalls[0].getSpeed() * timeToJumpPeak.asSeconds()).y > mPlayers[0].getPosition().y - mPlayers[0].getRadius() - jumpPeak &&
			std::abs(mPlayers[0].getPosition().x - mBalls[0].getPosition().x) <= 600.f) {
			mPlayers[0].setIsJumping(true);
		}
		else {
			mPlayers[0].setIsJumping(false);
		}

		if ((mBalls[0].getPosition() + mBalls[0].getSpeed() * timeToKick.asSeconds() - mPlayers[0].getPosition() - mPlayers[0].getSpeed() * timeToKick.asSeconds()).x > 0.f && 
			(mBalls[0].getPosition() + mBalls[0].getSpeed() * timeToKick.asSeconds() - mPlayers[0].getPosition() - mPlayers[0].getSpeed() * timeToKick.asSeconds()).x < 120.f && 
			(mBalls[0].getPosition() + mBalls[0].getSpeed() * timeToKick.asSeconds() - mPlayers[0].getPosition() - mPlayers[0].getSpeed() * timeToKick.asSeconds()).y > -10.f &&
			mPlayers[0].getPosition().y < mBalls[0].getPosition().y) {
			mPlayers[0].setIsKicking(true);
		}
		else {
			if (mPlayers[0].getLegAngle() == 1.f) {
				mPlayers[0].setIsKicking(false);
			}
		}
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

		nf::Vector2f leftCrossbar(mLeftGates[1].x, (mLeftGates[1].y + mLeftGates[2].y) / 2.f);
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			bool isColliding;
			nf::Vector2f deltaPosition = iterBalls->getPosition() - leftCrossbar;
			if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(iterBalls->getRadius() + ((mLeftGates[1].y - mLeftGates[2].y) / 2.f), 2.f)) {
				isColliding = true;
			}
			else {
				isColliding = false;
			}
			if (isColliding) {
				nf::Vector2f deltaPosition = leftCrossbar - iterBalls->getPosition();

				float distance = deltaPosition.length();
				float requiredDistance = iterBalls->getRadius() + ((mLeftGates[1].y - mLeftGates[2].y) / 2.f);

				nf::Vector2f unitNormalVector = deltaPosition.normalized();
				nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

				iterBalls->setPosition(iterBalls->getPosition() - unitNormalVector * (requiredDistance - distance));

				float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, iterBalls->getSpeed());
				float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, iterBalls->getSpeed());

				float newThisNormalSpeed, newOtherNormalSpeed;
				nf::resolveOneDimensionalCollision(iterBalls->getMass(), 1000000.f, thisNormalSpeed, 0.f, newThisNormalSpeed, newOtherNormalSpeed);

				iterBalls->setSpeed(unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed);
			}
			iterBalls++;
		}
		auto iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			bool isColliding;
			nf::Vector2f deltaPosition = iterPlayers->getPosition() - leftCrossbar;
			if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(iterPlayers->getRadius() + ((mLeftGates[1].y - mLeftGates[2].y) / 2.f), 2.f)) {
				isColliding = true;
			}
			else {
				isColliding = false;
			}
			if (isColliding) {
				nf::Vector2f deltaPosition = leftCrossbar - iterPlayers->getPosition();

				float distance = deltaPosition.length();
				float requiredDistance = iterPlayers->getRadius() + ((mLeftGates[1].y - mLeftGates[2].y) / 2.f);

				nf::Vector2f unitNormalVector = deltaPosition.normalized();
				nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

				iterPlayers->setPosition(iterPlayers->getPosition() - unitNormalVector * (requiredDistance - distance));

				float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, iterPlayers->getSpeed());
				float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, iterPlayers->getSpeed());

				float newThisNormalSpeed, newOtherNormalSpeed;
				nf::resolveOneDimensionalCollision(iterPlayers->getMass(), 1000000.f, thisNormalSpeed, 0.f, newThisNormalSpeed, newOtherNormalSpeed);

				iterPlayers->setSpeed(unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed);
			}
			iterPlayers++;
		}

		nf::Vector2f rightCrossbar(mRightGates[1].x, (mRightGates[1].y + mRightGates[2].y) / 2.f);
		iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			bool isColliding;
			nf::Vector2f deltaPosition = iterBalls->getPosition() - rightCrossbar;
			if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(iterBalls->getRadius() + ((mRightGates[1].y - mRightGates[2].y) / 2.f), 2.f)) {
				isColliding = true;
			}
			else {
				isColliding = false;
			}
			if (isColliding) {
				nf::Vector2f deltaPosition = rightCrossbar - iterBalls->getPosition();

				float distance = deltaPosition.length();
				float requiredDistance = iterBalls->getRadius() + ((mRightGates[1].y - mRightGates[2].y) / 2.f);

				nf::Vector2f unitNormalVector = deltaPosition.normalized();
				nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

				iterBalls->setPosition(iterBalls->getPosition() - unitNormalVector * (requiredDistance - distance));

				float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, iterBalls->getSpeed());
				float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, iterBalls->getSpeed());

				float newThisNormalSpeed, newOtherNormalSpeed;
				nf::resolveOneDimensionalCollision(iterBalls->getMass(), 1000000.f, thisNormalSpeed, 0.f, newThisNormalSpeed, newOtherNormalSpeed);

				iterBalls->setSpeed(unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed);
			}
			iterBalls++;
		}
		iterPlayers = mPlayers.begin();
		while (iterPlayers != mPlayers.end()) {
			bool isColliding;
			nf::Vector2f deltaPosition = iterPlayers->getPosition() - rightCrossbar;
			if (std::pow(deltaPosition.x, 2.f) + std::pow(deltaPosition.y, 2.f) <= std::pow(iterPlayers->getRadius() + ((mRightGates[1].y - mRightGates[2].y) / 2.f), 2.f)) {
				isColliding = true;
			}
			else {
				isColliding = false;
			}
			if (isColliding) {
				nf::Vector2f deltaPosition = rightCrossbar - iterPlayers->getPosition();

				float distance = deltaPosition.length();
				float requiredDistance = iterPlayers->getRadius() + ((mRightGates[1].y - mRightGates[2].y) / 2.f);

				nf::Vector2f unitNormalVector = deltaPosition.normalized();
				nf::Vector2f unitTangentVector(-unitNormalVector.y, unitNormalVector.x);

				iterPlayers->setPosition(iterPlayers->getPosition() - unitNormalVector * (requiredDistance - distance));

				float thisNormalSpeed = nf::scalarMultiplication(unitNormalVector, iterPlayers->getSpeed());
				float thisTangentSpeed = nf::scalarMultiplication(unitTangentVector, iterPlayers->getSpeed());

				float newThisNormalSpeed, newOtherNormalSpeed;
				nf::resolveOneDimensionalCollision(iterPlayers->getMass(), 1000000.f, thisNormalSpeed, 0.f, newThisNormalSpeed, newOtherNormalSpeed);

				iterPlayers->setSpeed(unitNormalVector * newThisNormalSpeed + unitTangentVector * thisTangentSpeed);
			}
			iterPlayers++;
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
					if (jterPlayers->getPosition().y >= 885.f && iterPlayers->isColliding(*jterPlayers)) {
						canJumpFromAnotherPlayer = true;
					}
				}
				jterPlayers++;
			}

			if ((iterPlayers->getPosition().y >= 885.f || canJumpFromAnotherPlayer) && iterPlayers->getIsJumping()) {
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

		mWindow.draw(mTextScoreLeft);
		mWindow.draw(mTextScoreRight);

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

		mWindow.draw(mLeftGatesSprite);
		mWindow.draw(mRightGatesSprite);

		if (mGoalFlag) {
			mGoalText.setScale(mAfterGoalClock.getElapsedTime().asSeconds() / TimeAfterGoal.asSeconds(), mAfterGoalClock.getElapsedTime().asSeconds() / TimeAfterGoal.asSeconds());
			if (mScoreLeft == mMaxNumOfGoals || mScoreRight == mMaxNumOfGoals) {
				mGoalText.setPosition(sf::Vector2f(WindowWidth / 2.0f + nf::randIntFromRange(-10, 10), WindowHeight / 2.0f + nf::randIntFromRange(-10, 10)));
			}
			mWindow.draw(mGoalText);
		}

		mWindow.display();
	}





	void Game::startPosition() {
		mGravity = DefaultGravity;

		mBalls[0].setup(BallStartPosition, BallStartSpeed, BallDefaultRadius, BallDefaultMass, BallDefaultBounceCoefficient, mTextureHolder.get(BallTextureName));
		if (mScoreLeft != 0 || mScoreRight != 0) {
			if (mLastGoal == nf::PlayerSide::Left) {
				mBalls[0].setSpeed(nf::Vector2f(nf::randIntFromRange(100.f, 250.f), nf::randIntFromRange(-100.f, 100.f)));
			}
			else {
				mBalls[0].setSpeed(nf::Vector2f(nf::randIntFromRange(-250.f, -100.f), nf::randIntFromRange(-100.f, 100.f)));
			}
		}
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
		else {
			mPlayers[0].setup(LeftPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftPlayerTextureName),
				nf::PlayerSide::Left, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, mTextureHolder.get(LeftLegTextureName));
			mPlayers[1].setup(RightPlayerStartPosition, PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightPlayerTextureName),
				nf::PlayerSide::Right, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::P, mTextureHolder.get(RightLegTextureName));
			mPlayers[2].setup(LeftPlayerStartPosition - nf::Vector2f(200.f, 0.f), PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(LeftLeftPlayerTextureName),
				nf::PlayerSide::Left, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::Num6, sf::Keyboard::M, mTextureHolder.get(LeftLegTextureName));
			mPlayers[3].setup(RightPlayerStartPosition + nf::Vector2f(200.f, 0.f), PlayerStartSpeed, PlayerDefaultRadius, PlayerDefaultMass, PlayerDefaultBounceCoefficient, mTextureHolder.get(RightRightPlayerTextureName),
				nf::PlayerSide::Right, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8, sf::Keyboard::Numpad0, mTextureHolder.get(RightLegTextureName));
		}

		if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
			mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
			mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
		}
		else {
			mPlayers[0].setMaxXSpeed(PlayerDefaultMaxXSpeed);
			mPlayers[1].setMaxXSpeed(PlayerDefaultMaxXSpeed);
			mPlayers[2].setMaxXSpeed(PlayerDefaultMaxXSpeed);
			mPlayers[3].setMaxXSpeed(PlayerDefaultMaxXSpeed);
		}

		if (mGameMode == nf::GameMode::PvP || mGameMode == nf::GameMode::PvE) {
			mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
			mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
		}
		else {
			mPlayers[0].setJumpForce(PlayerDefaultJumpForce);
			mPlayers[1].setJumpForce(PlayerDefaultJumpForce);
			mPlayers[2].setJumpForce(PlayerDefaultJumpForce);
			mPlayers[3].setJumpForce(PlayerDefaultJumpForce);
		}

		mLeftGates[0].y = 660.f;
		mLeftGates[1].y = 660.f;
		mLeftGates[2].y = 670.f;
		mLeftGates[3].y = 670.f;

		mRightGates[0].y = 660.f;
		mRightGates[1].y = 660.f;
		mRightGates[2].y = 670.f;
		mRightGates[3].y = 670.f;

		mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftGatesTextureName));
		mRightGatesSprite.setTexture(*mTextureHolder.get(RightGatesTextureName));

		mBonuses.clear();
	}
	void Game::goalCheck() {
		auto iterBalls = mBalls.begin();
		while (iterBalls != mBalls.end()) {
			if (iterBalls->getPosition().x < mLeftGates[1].x && iterBalls->getPosition().y > mLeftGates[2].y && mGoalFlag == false) {
				mAfterGoalClock.restart();
				mGoalFlag = true;
				mLastGoal = nf::PlayerSide::Right;
				mScoreRight++;
				mTextScoreRight.setString(std::to_string(mScoreRight));
				sf::FloatRect textRect = mTextScoreRight.getLocalBounds();
				mTextScoreRight.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				mTextScoreRight.setPosition(sf::Vector2f(1800.f, 120.f));
				
			}
			if (iterBalls->getPosition().x > mRightGates[1].x && iterBalls->getPosition().y > mRightGates[2].y && mGoalFlag == false) {
				mAfterGoalClock.restart();
				mGoalFlag = true;
				mLastGoal = nf::PlayerSide::Left;
				mScoreLeft++;
				mTextScoreLeft.setString(std::to_string(mScoreLeft));
				sf::FloatRect textRect = mTextScoreLeft.getLocalBounds();
				mTextScoreLeft.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				mTextScoreLeft.setPosition(sf::Vector2f(120.f, 120.f));
			}
			iterBalls++;
		}
	}





	void Game::bonusSpawn() {
		nf::BonusType type;
		type = nf::BonusType(nf::randIntFromRange(0, int(nf::BonusType::Count) - 1));
		nf::Bonus bonus;
		nf::Vector2f bonusPosition;
		while (true) {
			bonusPosition = nf::Vector2f(nf::randIntFromRange(420, 1500), nf::randIntFromRange(180, 720));
			auto iterBonuses = mBonuses.begin();
			bool overlapping = false;
			while (iterBonuses != mBonuses.end()) {
				if (std::sqrt((bonusPosition.x - iterBonuses->getPosition().x) * (bonusPosition.x - iterBonuses->getPosition().x) + (bonusPosition.y - iterBonuses->getPosition().y) * (bonusPosition.y - iterBonuses->getPosition().y)) <= 2 * BonusRadius) {
					overlapping = true;
					break;
				}
				iterBonuses++;
			}
			if (!overlapping) {
				break;
			}
		}
		if (type == nf::BonusType::LowGravity) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowGravityTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::BouncyBall) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(BouncyBallTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::DeflatedBall) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(DeflatedBallTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::HighJump) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(HighJumpTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::LowJump) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowJumpTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::HighSpeed) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(HighSpeedTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::LowSpeed) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(LowSpeedTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::SmallGates) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(SmallGatesTextureName));
			bonus.setBonusType(type);
		}
		if (type == nf::BonusType::BigGates) {
			bonus.setup(bonusPosition, BallStartSpeed, BonusRadius, 0.f, 0.f, mTextureHolder.get(BigGatesTextureName));
			bonus.setBonusType(type);
		}
		if (mBonuses.size() < 5) {
			mBonuses.push_back(bonus);
		}
		else {
			mBonuses.erase(mBonuses.begin());
			mBonuses.push_back(bonus);
		}
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
				iterBalls->setTexture(mTextureHolder.get(BallBouncyTextureName));
				iterBalls++;
			}
			mBouncyBallClock.restart();
		}
		if (type == nf::BonusType::DeflatedBall) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(DeflatedBallBounceCoefficient);
				iterBalls->setTexture(mTextureHolder.get(BallDeflatedTextureName));
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
				mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftSmallGatesTextureName));
			}
			else {
				mRightGates[0].y = 780.f;
				mRightGates[1].y = 780.f;
				mRightGates[2].y = 790.f;
				mRightGates[3].y = 790.f;
				mRightGatesSprite.setTexture(*mTextureHolder.get(RightSmallGatesTextureName));
			}
			mSmallGatesClock.restart();
		}
		if (type == nf::BonusType::BigGates) {
			if (ball.getLastTouched()->getSide() == nf::PlayerSide::Left) {
				mLeftGates[0].y = 540.f;
				mLeftGates[1].y = 540.f;
				mLeftGates[2].y = 550.f;
				mLeftGates[3].y = 550.f;
				mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftBigGatesTextureName));
			}
			else {
				mRightGates[0].y = 540.f;
				mRightGates[1].y = 540.f;
				mRightGates[2].y = 550.f;
				mRightGates[3].y = 550.f;
				mRightGatesSprite.setTexture(*mTextureHolder.get(RightBigGatesTextureName));
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
				iterBalls->setTexture(mTextureHolder.get(BallTextureName));
				iterBalls++;
			}
		}
		if (mDeflatedBallClock.getElapsedTime() >= DeflatedBallTime && mBalls[0].getBounceCoefficient() == DeflatedBallBounceCoefficient) {
			auto iterBalls = mBalls.begin();
			while (iterBalls != mBalls.end()) {
				iterBalls->setBounceCoefficient(BallDefaultBounceCoefficient);
				iterBalls->setTexture(mTextureHolder.get(BallTextureName));
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
			mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftGatesTextureName));
			mRightGatesSprite.setTexture(*mTextureHolder.get(RightGatesTextureName));
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
			mLeftGatesSprite.setTexture(*mTextureHolder.get(LeftGatesTextureName));
			mRightGatesSprite.setTexture(*mTextureHolder.get(RightGatesTextureName));
		}
	}
}