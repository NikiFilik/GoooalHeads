#include "Game.hpp"
#include "globalConsts.hpp"

int main() {
	srand(time(0));

	nf::GameMode gameMode = nf::GameMode::PvP;
	int maxNumOfGoals = 5;

	nf::Game game(gameMode, maxNumOfGoals);
	game.run();

	return 0;
}