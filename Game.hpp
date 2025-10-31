#pragma once
#include "GameBoard.hpp"
#include "Menu.hpp"

class Game {
	public:
		//constructor
		Game() { this->mExitGame = false; }

		//destructor
		virtual ~Game() {}

		//public member functions
		void run();

	private:
		GameBoard mBoard;
		bool mExitGame;
		bool mExitStartMenu;
		Menu mStartMenu;

		//private member functions
		void parseMove();
		void move(char moveEvent);
		void setupStartMenu();
		void EvaluateStartMenuChoice(int choice);
		void runGame();
		void printRules();
		void recallAfterRules();
};