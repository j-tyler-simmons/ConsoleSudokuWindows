#include "Game.hpp"
#include <windows.h>
#include <conio.h>	//needed for _getch()
#include <ctime>

int main() {
	Game sudoku;

	// Set console output to UTF-8
	SetConsoleOutputCP(CP_UTF8);

	//turn off the cursor
	cout << "\033[?25l";

	//setting up srand
	srand((unsigned int)time(NULL));

	sudoku.run();

	return 0;
}