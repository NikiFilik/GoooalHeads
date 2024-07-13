#include "Game.hpp"
#include "globalConsts.hpp"
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	nf::GameMode gameMode = nf::GameMode::PvP;
	int maxNumOfGoals = 5;

	std::cout << "������������ ��� � ���� ��������!\n\n";
	std::cout << "�������� ����� ����:\n\n" << "1) ����� VS �����\n" << "2) 2 ������ VS 2 ������\n" << "3) ����� VS ���������\n\n";
	std::cout << "��� ������ ������ ���� �������� � ������� ��������������� �����:\n";

	int chosenGameMode = 0;
	while (chosenGameMode < 1 || chosenGameMode > 3) {
		std::cin >> chosenGameMode;
		if (chosenGameMode < 1 || chosenGameMode > 3) {
			std::cout << "���-�� �� ���, ���������� ��� ���:\n";
		}
	}
	gameMode = nf::GameMode(chosenGameMode);

	std::cout << "�� ������ ����� ������?\n";
	std::cin >> maxNumOfGoals;

	nf::Game game(gameMode, maxNumOfGoals);
	game.run();

	return 0;
}