#include "Game.hpp"
#include <conio.h>

void Game::run()
{
	this->mBoard.genFullBoard(40);
	//this->mBoard.makePuzzle(40);	//set to 40 initially for an easy puzzle
	this->mBoard.updateStats();
	this->mBoard.displayBoard();

	while (this->mExitGame != true) {
		cout << "\x1b[H";
		this->parseMove();
		this->mBoard.updateStats();
		this->mBoard.displayBoard();
	}
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