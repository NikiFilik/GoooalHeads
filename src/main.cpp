#include "Game.hpp"
#include "globalConsts.hpp"

int main() {
	nf::GameMode gameMode = nf::GameMode::PvP;

	nf::Game game(gameMode);
	game.run();

	return 0;
}