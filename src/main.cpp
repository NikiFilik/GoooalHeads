#include "Game.hpp"
#include "globalConsts.hpp"
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	nf::GameMode gameMode = nf::GameMode::PvP;
	int maxNumOfGoals = 5;

	std::cout << "ПРИВЕТСТВУЕМ ВАС В ИГРЕ ГОООЛОВЫ!\n\n";
	std::cout << "Выберете режим игры:\n\n" << "1) Игрок VS Игрок\n" << "2) 2 Игрока VS 2 Игрока\n" << "3) Игрок VS Компьютер\n\n";
	std::cout << "Для выбора режима игры напишите в консоль соответствующую цифру:\n";

	int chosenGameMode = 0;
	while (chosenGameMode < 1 || chosenGameMode > 3) {
		std::cin >> chosenGameMode;
		if (chosenGameMode < 1 || chosenGameMode > 3) {
			std::cout << "Что-то не так, попробуйте еще раз:\n";
		}
	}
	gameMode = nf::GameMode(chosenGameMode);

	std::cout << "До какого счёта играем?\n";
	std::cin >> maxNumOfGoals;

	nf::Game game(gameMode, maxNumOfGoals);
	game.run();

	return 0;
}