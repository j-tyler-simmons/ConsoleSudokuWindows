#include "GameBoard.hpp"

GameBoard::GameBoard()
{
	int i = 0, j = 0;

	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			this->mGameCells[i][j].setValue(0);
		}
	}

    //set top left cell to be highlighted
    this->mGameCells[0][0].setHiLightStr("\033[7m");

    this->mHiLightX = 0;
    this->mHiLightY = 0;
}

GameBoard::GameBoard(GameBoard& newBoard)
{
	int i = 0, j = 0;

	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			this->mGameCells[i][j].setValue(newBoard.getGameCell(i, j).getValue());
			this->mGameCells[i][j].setIsFixed(newBoard.getGameCell(i, j).getIsFixed());
		}
	}
}

GameBoard& GameBoard::operator=(GameBoard& rhs)
{
	int i = 0, j = 0;

	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			this->mGameCells[i][j].setValue(rhs.getGameCell(i, j).getValue());
			this->mGameCells[i][j].setIsFixed(rhs.getGameCell(i, j).getIsFixed());
		}
	}

	return *this;
}

Cell GameBoard::getGameCell(const int xPos, const int yPos)
{
	Cell copyCell(this->mGameCells[yPos][xPos]);

	return copyCell;
}

int GameBoard::getGameCellValue(const int xPos, const int yPos) const
{
    return this->mGameCells[yPos][xPos].getValue();
}

int GameBoard::getGameCellCorrectValue(const int xPos, const int yPos) const
{
    return this->mGameCells[yPos][xPos].getCorrectValue();
}

bool GameBoard::getIsCellFixed(const int xPos, const int yPos) const
{
    return this->mGameCells[yPos][xPos].getIsCorrect();
}

bool GameBoard::getIsCellCorrect(const int xPos, const int yPos) const
{
    return this->mGameCells[yPos][xPos].getIsCorrect();
}

int GameBoard::getHiLightX() const
{
    return this->mHiLightX;
}

int GameBoard::getHiLightY() const
{
    return this->mHiLightY;
}

void GameBoard::setGameCellValue(const int xPos, const int yPos, const int value)
{
	this->mGameCells[yPos][xPos].setValue(value);
}

void GameBoard::setGameCellCorrectValue(const int xPos, const int yPos, const int value)
{
    this->mGameCells[yPos][xPos].setCorrectValue(value);
}

void GameBoard::makeCellFixed(const int xPos, const int yPos)
{
    this->mGameCells[yPos][xPos].setIsFixed(true);
}

void GameBoard::makeCellCorrect(const int xPos, const int yPos)
{
    this->mGameCells[yPos][xPos].setIsCorrect(true);
}

void GameBoard::setHiLightX(const int xPos)
{
    this->mHiLightX = xPos;
}

void GameBoard::setHiLightY(const int yPos)
{
    this->mHiLightY = yPos;
}

void GameBoard::displayBoard()
{
    const char* topBorder = u8"  ╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗";
    const char* midSeparator = u8"  ║───┼───┼───╫───┼───┼───╫───┼───┼───╢";
    const char* thickSep = u8"  ╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣";
    const char* bottomBorder = u8"  ╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";

    int val = 0,
        row = 0,
        col = 0;


    cout << u8"\n    1   2   3   4   5   6   7   8   9" << endl;
    cout << topBorder << endl;

    for (row = 0; row < 9; ++row) {
        cout << row + 1 << u8" ║";

        for (col = 0; col < 9; ++col) {
            if (this->mGameCells[row][col].getIsFixed() == true) {
                this->mGameCells[row][col].setValue(this->mGameCells[row][col].getCorrectValue());
            }
            val = this->mGameCells[row][col].getValue();
            cout << this->mGameCells[row][col].getHiLightStr();
            cout << " ";
            std::cout << (val == 0 ? '.' : static_cast<char>('0' + val));   //solves issue of 46 being printed
            cout << " ";
            cout << "\033[0m";
            if (col == 8)
                cout << u8"║";
            else if ((col + 1) % 3 == 0)
                cout << u8"║";
            else
                cout << u8"│";
        }
        cout << endl;

        if (row == 8) {
            cout << bottomBorder << endl;
        }
        else if ((row + 1) % 3 == 0) {
            cout << thickSep << endl;
        }
        else {
            cout << midSeparator << endl;
        }
    }

}

void GameBoard::clearHiLightStr(const int xPos, const int yPos)
{
    this->mGameCells[yPos][xPos].setHiLightStr("\033[0m");
}

void GameBoard::setHiLightStr(const int xPos, const int yPos)
{
    this->mGameCells[yPos][xPos].setHiLightStr("\033[7m");
}

bool GameBoard::checkValidMove(const char* input)
{
    int numEntered = atoi(input);

    if (numEntered > 0 && numEntered < 10) {
        this->mGameCells[this->mHiLightY][this->mHiLightX].setValue(numEntered);
    }
    return false;
}

void GameBoard::genFullBoard()
{
    int size = 9,
        i = 0,
        j = 0;

    //Clear all mCorrect values
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            this->mGameCells[i][j].setCorrectValue(0);
        }
    }

    fillBoardRecursive(0, 0);
}

void GameBoard::makePuzzle(int fixedCount)
{
    int placed = 0,
        row = 0,
        col = 0,
        size = 9;

    while (placed < fixedCount) {
        int row = rand() % size;
        int col = rand() % size;

        if (!this->mGameCells[row][col].getIsFixed()) {
            this->mGameCells[row][col].setIsFixed(true);
            ++placed;
        }
    }
}

bool GameBoard::isNumSafe(int row, int col, int num)
{
    bool safetyTest = true;
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    int i = 0, j = 0, x = 0;

    for (x = 0; x < 9; x++) {
        if (this->mGameCells[row][x].getCorrectValue() == num || this->mGameCells[x][col].getCorrectValue() == num) {
            safetyTest = false;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (this->mGameCells[startRow + i][startCol + j].getCorrectValue() == num) {
                safetyTest = false;
            }
        }
    }

    return safetyTest;
}

void GameBoard::shuffleNumbers(int arr[])
{
    int i = 0, 
        j = 0, 
        size = 9, 
        temp = 0;

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool GameBoard::fillBoardRecursive(int row, int col)
{
    int nums[9] = { 0 };
    int i = 0,
        num = 0;

    if (row == 9) {
        return true; // Entire board filled
    }

    // Move to next row if at end of column
    if (col == 9) {
        return fillBoardRecursive(++row, 0);
    }

    if (this->mGameCells[row][col].getCorrectValue() != 0) {
        // Already filled (should not happen in generation, but just in case)
        return fillBoardRecursive(row, ++col);
    }

    for (i = 0; i < 9; ++i) {
        nums[i] = i + 1;
    }

    this->shuffleNumbers(nums); // Shuffle numbers 1-9

    for (i = 0; i < 9; ++i) {
        num = nums[i];
        if (this->isNumSafe(row, col, num)) {
            this->mGameCells[row][col].setCorrectValue(num);
            if (fillBoardRecursive(row, ++col)) {
                return true;
            }
            this->mGameCells[row][col].setCorrectValue(0); // Backtrack
        }
    }

    return false; // No valid number found, trigger backtracking
}
