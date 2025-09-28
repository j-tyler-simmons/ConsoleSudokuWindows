#include "Cell.hpp"
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class GameBoard {
	public:
		//constructor
		GameBoard();

		//destructor
		virtual ~GameBoard() {}

		//copy constructor
		GameBoard(GameBoard& newBoard);

		//copy assignment operator
		GameBoard& operator=(GameBoard& rhs);

		//cell accessors
		Cell getGameCell(const int xPos, const int yPos);
		int getGameCellValue(const int xPos, const int yPos) const;
		int getGameCellCorrectValue(const int xPos, const int yPos) const;
		bool getIsCellFixed(const int xPos, const int yPos) const;
		bool getIsCellCorrect(const int xPos, const int yPos) const;
		int getHiLightX() const;
		int getHiLightY() const;

		void setGameCellValue(const int xPos, const int yPos, const int value);
		void setGameCellCorrectValue(const int xPos, const int yPos, const int value);
		void makeCellFixed(const int xPos, const int yPos);
		void makeCellCorrect(const int xPos, const int yPos);
		void setHiLightX(const int xPos);
		void setHiLightY(const int yPos);

		//public member functions
		void displayBoard();
		void clearHiLightStr(const int xPos, const int yPos);
		void setHiLightStr(const int xPos, const int yPos);
		bool checkValidMove(const char* input);
		void genFullBoard();
		void makePuzzle(int fixedCount);
		//bool solve();

	private:
		//data members
		Cell mGameCells[9][9];
		int mHiLightX;
		int mHiLightY;

		//private member functions
		bool isNumSafe(int row, int col, int num);
		void shuffleNumbers(int arr[]);
		bool fillBoardRecursive(int row, int col);
};