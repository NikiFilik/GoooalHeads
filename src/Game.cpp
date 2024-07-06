#include "Game.hpp"

#include "globalConsts.hpp"

namespace nf {
	Game::Game() : mWindow(sf::VideoMode(WindowWidth, WindowHeight), "GoooalHeads", sf::Style::Fullscreen) {
		mWindow.setVerticalSyncEnabled(true);

		mTextureHolder.load(BackgroundTextureName);
		mTextureHolder.load(BallTextureName);

		mBackground.setTexture(*mTextureHolder.get(BackgroundTextureName));
		mBall.setup(BallStartPosition, BallStartSpeed, BallDefaultRadius, BallDefaultMass, BallDefaultBounceCoefficient, mTextureHolder.get(BallTextureName));
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
	}
	void Game::processPlayerInput(const sf::Mouse::Button& button, const bool isPressed) {
	}

	void Game::update(const sf::Time& deltaTime) {
		mBall.update(deltaTime);
		for (int i = 1; i < 11; i++) {
			if (mBall.isColliding(mField[i - 1], mField[i])) {
				mBall.resolveCollision(mField[i - 1], mField[i]);
			}
		}
		
	}

	void Game::render() {
		mWindow.clear();
		mWindow.draw(mBackground);
		mWindow.draw(mBall.getSprite());
		mWindow.display();
	}
}