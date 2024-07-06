#pragma once

#include <SFML/Graphics.hpp>

#include "TextureHolder.hpp"
#include "Object.hpp"
#include "Ball.hpp"

namespace nf {
	class Game {
	public:
		sf::RenderWindow mWindow;
		nf::TextureHolder mTextureHolder;

		sf::Sprite mBackground;
		const nf::Vector2f mField[11] = {nf::Vector2f(60.f, 960.f), nf::Vector2f(60.f, 720.f), nf::Vector2f(120.f, 360.f), nf::Vector2f(360.f, 120.f), nf::Vector2f(720.f, 60.f), 
			nf::Vector2f(1200.f, 60.f), nf::Vector2f(1560.f, 120.f), nf::Vector2f(1800.f, 360.f), nf::Vector2f(1860.f, 720.f), nf::Vector2f(1860.f, 960.f), nf::Vector2f(60.f, 960.f)};

		nf::Ball mBall;
		
	private:
		void processInput();
		void processPlayerInput(const sf::Keyboard::Key& key, const bool isPressed);
		void processPlayerInput(const sf::Mouse::Button& button, const bool isPressed);

		void update(const sf::Time& deltaTime);

		void render();
	public:
		Game();
		void run();
	};
}