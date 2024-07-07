#pragma once

#include <SFML/Graphics.hpp>

#include "TextureHolder.hpp"
#include "Object.hpp"
#include "Ball.hpp"
#include "Player.hpp"

namespace nf {
	class Game {
	public:
		nf::GameMode mGameMode;

		sf::RenderWindow mWindow;
		nf::TextureHolder mTextureHolder;

		sf::Sprite mBackground;
		nf::Vector2f mField[11] = {nf::Vector2f(60.f, 960.f), nf::Vector2f(60.f, 720.f), nf::Vector2f(120.f, 360.f), nf::Vector2f(360.f, 120.f), nf::Vector2f(720.f, 60.f), 
			nf::Vector2f(1200.f, 60.f), nf::Vector2f(1560.f, 120.f), nf::Vector2f(1800.f, 360.f), nf::Vector2f(1860.f, 720.f), nf::Vector2f(1860.f, 960.f), nf::Vector2f(60.f, 960.f)};
		nf::Vector2f mLeftGates[4] = {nf::Vector2f(0.f, 660.f), nf::Vector2f(240.f, 660.f), nf::Vector2f(240.f, 670.f), nf::Vector2f(0.f, 670.f)};
		nf::Vector2f mRightGates[4] = {nf::Vector2f(1920.f, 660.f), nf::Vector2f(1680.f, 660.f), nf::Vector2f(1680.f, 670.f), nf::Vector2f(1920.f, 670.f)};

		nf::Vector2f mGravity = DefaultGravity;

		std::vector<nf::Ball> mBalls;
		std::vector<nf::Player> mPlayers;
		
	private:
		void processInput();
		void processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed);
		void processPlayerInput(const sf::Mouse::Button& button, const bool isPressed);

		void gravityEffect(const sf::Time& deltaTime);
		void collisionWithField();
		void collisionBallsWithBalls();
		void collisionPlayersWithPlayers();
		void collisionBallsWithPlayers();
		void processPlayersJumps();
		void update(const sf::Time& deltaTime);

		void render();
	public:
		Game(nf::GameMode gameMode);
		void run();
	};
}