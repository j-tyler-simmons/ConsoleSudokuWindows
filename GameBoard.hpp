#include "Cell.hpp"
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::round;

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

		//accessors
		Cell getGameCell(const int xPos, const int yPos);
		int getGameCellValue(const int xPos, const int yPos) const;
		int getGameCellCorrectValue(const int xPos, const int yPos) const;
		bool getIsCellFixed(const int xPos, const int yPos) const;
		bool getIsCellCorrect(const int xPos, const int yPos) const;
		int getHiLightX() const;
		int getHiLightY() const;
		double getNumFilled() const;
		double getNumBoard() const;
		int getNumSolutions() const;

		void setGameCellValue(const int xPos, const int yPos, const int value);
		void setGameCellCorrectValue(const int xPos, const int yPos, const int value);
		void makeCellFixed(const int xPos, const int yPos);
		void makeCellCorrect(const int xPos, const int yPos);
		void setHiLightX(const int xPos);
		void setHiLightY(const int yPos);
		void setNumFilled(const double num);
		void setNumBoard(const double num);
		void setNumSolutions(const int solutions);

		//public member functions
		void displayBoard();
		void clearHiLightStr(const int xPos, const int yPos);
		void setHiLightStr(const int xPos, const int yPos);
		bool checkValidMove(int input);
		void genFullBoard(int cluesToKeep);
		void makePuzzle(int fixedCount);
		void updateStats();
		void countSolutions(int maxSolutions);
		bool countSolutionsRecursive(int& numSolutions, int maxSolutions);
		//bool solve();

	private:
		//data members
		Cell mGameCells[9][9];
		int mHiLightX;
		int mHiLightY;
		double mNumFilled;
		double mNumBoard;
		int mNumSolutions;

		//private member functions
		bool isNumSafe(int row, int col, int num);
		void shuffleNumbers(int arr[]);
		bool fillBoardRecursive();
		int getProgress();
		void printProgress(int percent, int width);
		void setFixedNums();
};		