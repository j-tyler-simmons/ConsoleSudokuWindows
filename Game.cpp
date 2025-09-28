#include "Game.hpp"
#include <conio.h>

void Game::run()
{
	this->mBoard.genFullBoard();
	this->mBoard.makePuzzle(40);	//set to 40 initially for an easy puzzle
	this->mBoard.displayBoard();

	while (this->mExitGame != true) {
		cout << "\x1b[H";
		this->move();
		this->mBoard.displayBoard();
	}
}

void Game::move()
{
	char moveEvent = '\0';

	moveEvent = _getch();
	const char* eventCopy = &moveEvent;

	if (isdigit(moveEvent)) {
		this->mBoard.checkValidMove(eventCopy);
	}
	else {
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
}
