#include "Game.hpp"
#include <conio.h>

void Game::run()
{
	int startMenuChoice = 0;

	system("cls");

	//start menu stuff
	this->setupStartMenu();
	startMenuChoice = this->mStartMenu.scroll(20, 2);
	this->EvaluateStartMenuChoice(startMenuChoice);
}

void Game::parseMove()
{
	int moveEvent = 0;
	char moveEventch = '\0';

	moveEvent = _getch();

	if (moveEvent == -32 || moveEvent == 224) {
		
		moveEvent = _getch();

		switch (moveEvent) {
			case 72:
				moveEventch = 'w';
				break;
			case 80:
				moveEventch = 's';
				break;
			case 75:
				moveEventch = 'a';
				break;
			case 77:
				moveEventch = 'd';
				break;
			default:
				break;
		}
		this->move(moveEventch);
	}
	else {
		moveEventch = (char)moveEvent;
		if (moveEventch > '0' && moveEventch <= '9') {
			this->mBoard.checkValidMove(moveEvent);
		}
		else if (moveEventch == 'w' || moveEventch == 's' || moveEventch == 'a' || moveEventch == 'd') {
			this->move(moveEventch);
		}
		else if (moveEventch == '\b' && this->mBoard.getIsCellFixed(this->mBoard.getHiLightX(), this->mBoard.getHiLightY()) == false) {
			this->mBoard.setGameCellValue(this->mBoard.getHiLightX(), this->mBoard.getHiLightY(), 0);
			this->mBoard.makeCellWrong(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());
		}
	}
}

void Game::move(char moveEvent)
{
	if (this->mBoard.getHiLightY() >= 0 && this->mBoard.getHiLightY() < 8
		&& moveEvent == 's') {
		this->mBoard.clearHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());

		//only need to move down
		this->mBoard.setHiLightY(this->mBoard.getHiLightY() + 1);

		//highlight new cell
		this->mBoard.setHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());
	}
	else if (this->mBoard.getHiLightY() > 0 && this->mBoard.getHiLightY() <= 8
		&& moveEvent == 'w') {
		this->mBoard.clearHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());

		//only need to move down
		this->mBoard.setHiLightY(this->mBoard.getHiLightY() - 1);

		//highlight new cell
		this->mBoard.setHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());
	}
	else if (this->mBoard.getHiLightX() > 0 && this->mBoard.getHiLightX() <= 8
		&& moveEvent == 'a') {
		this->mBoard.clearHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());

		//only need to move left
		this->mBoard.setHiLightX(this->mBoard.getHiLightX() - 1);

		//highlight new cell
		this->mBoard.setHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());
	}
	else if (this->mBoard.getHiLightX() >= 0 && this->mBoard.getHiLightX() < 8
		&& moveEvent == 'd') {
		this->mBoard.clearHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());

		//only need to move right
		this->mBoard.setHiLightX(this->mBoard.getHiLightX() + 1);

		//highlight new cell
		this->mBoard.setHiLightStr(this->mBoard.getHiLightX(), this->mBoard.getHiLightY());
	}
	else {
		//do nothing
	}
}

void Game::setupStartMenu()
{
	string optionArray[10] = {"Start Game", "Show Rules", "Load Settings (to do)", "Exit", 
		"", "", "", "", "", ""};

	this->mStartMenu.~Menu();
	this->mStartMenu.setOptions(optionArray);
	this->mStartMenu.setupMenu();
}

void Game::EvaluateStartMenuChoice(int choice)
{
	switch (choice) {
		case 1:
			this->runGame();
			break;
		case 2:
			this->printRules();
			break;
		case 3:
			break;
		case 4:
			this->mExitGame = true;
			break;
	}
}

void Game::runGame()
{
	system("cls");

	this->mBoard.genFullBoard(40);
	this->mBoard.updateStats();
	this->mBoard.displayBoard();

	while (this->mExitGame != true) {
		cout << "\x1b[H";
		this->parseMove();
		this->mBoard.updateStats();
		this->mBoard.displayBoard();
	}
}

void Game::printRules()
{
	system("cls");

	cout << "The rules of Sudoku are to fill a 9x9 grid with numbers from 1 to 9 so that each row, each column, and" << endl;
	cout << "each of the nine 3x3 subgrids contains each digit exactly once.This means no number can be repeated in" << endl; 
	cout << "any row, column, or 3x3 box.The game is won when the entire grid is correctly filled." << endl << endl;

	cout << "[Press any key to return to the start menu...]";
	_getch();
	
	this->recallAfterRules();
}

void Game::recallAfterRules()
{
	int startMenuChoice = 0;

	system("cls");

	startMenuChoice = this->mStartMenu.scroll(20, 2);
	this->EvaluateStartMenuChoice(startMenuChoice);
}
