#include "GameBoard.hpp"

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

		//private member functions
		void parseMove();
		void move(char moveEvent);
};