#include "Game.hpp"

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
	}





	void Game::run() {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timeSinceLastFrame = sf::Time::Zero;

		while (mWindow.isOpen()) {
			timeSinceLastUpdate = clock.restart();
			timeSinceLastFrame += timeSinceLastUpdate;

			processInput();

			update(timeSinceLastUpdate);

			if (timeSinceLastFrame >= TimePerFrame) {
				timeSinceLastFrame = sf::Time::Zero;
				render();
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
				}
				if (iterBalls->isColliding(iterPlayers->getLeg())) {
					iterBalls->resolveCollision(iterPlayers->getLeg());
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
	}





	void Game::render() {
		mWindow.clear();
		mWindow.draw(mBackground);
		
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
}