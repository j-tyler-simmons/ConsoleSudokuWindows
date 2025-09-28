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
    this->mGameCells[0][0].setHiLightStr("\x1b[7m");

    this->mHiLightX = 0;
    this->mHiLightY = 0;

    //set num filled and num board
    this->mNumFilled = 0;
    this->mNumBoard = 9 * 9;

    //set num solutions
    this->mNumSolutions = 0;
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

    this->mHiLightX = newBoard.getHiLightX();
    this->mHiLightY = newBoard.getHiLightY();
    this->mNumFilled = newBoard.getNumFilled();
    this->mNumBoard = newBoard.getNumBoard();
    this->mNumSolutions = newBoard.getNumSolutions();
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

    this->mHiLightX = rhs.getHiLightX();
    this->mHiLightY = rhs.getHiLightY();
    this->mNumFilled = rhs.getNumFilled();
    this->mNumBoard = rhs.getNumBoard();
    this->mNumSolutions = rhs.getNumSolutions();

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

double GameBoard::getNumFilled() const
{
    return this->mNumFilled;
}

double GameBoard::getNumBoard() const
{
    return this->mNumBoard;
}

int GameBoard::getNumSolutions() const
{
    return this->mNumSolutions;
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

void GameBoard::setNumFilled(const double num)
{
    this->mNumFilled = num;
}

void GameBoard::setNumBoard(const double num)
{
    this->mNumBoard = num;
}

void GameBoard::setNumSolutions(const int solutions)
{
    this->mNumBoard = solutions;
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
            val = this->mGameCells[row][col].getValue();
            cout << this->mGameCells[row][col].getHiLightStr();
            
            if (this->mGameCells[row][col].getIsFixed() == true) {
                cout << "\x1b[32m";
            }

            cout << " ";
            
            cout << (val == 0 ? '.' : static_cast<char>('0' + val));   //solves issue of 46 being printed

            cout << " ";
            cout << "\x1b[0m";
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
    this->mGameCells[yPos][xPos].setHiLightStr("\x1b[0m");
}

void GameBoard::setHiLightStr(const int xPos, const int yPos)
{
    this->mGameCells[yPos][xPos].setHiLightStr("\x1b[7m");
}

bool GameBoard::checkValidMove(int input)
{
    bool testMove = false;

    if (this->mGameCells[this->mHiLightY][this->mHiLightX].getIsFixed() == false) {
        this->mGameCells[this->mHiLightY][this->mHiLightX].setValue(input - '0');
        testMove = true;
    }

    return testMove;
}

void GameBoard::genFullBoard(int cluesToKeep)
{
    fillBoardRecursive(); // Fill the board fully

    // Randomly remove cells
    int removed = 0;
    while (removed < (81 - cluesToKeep)) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (mGameCells[row][col].getValue() != 0) {
            mGameCells[row][col].setValue(0);
            mGameCells[row][col].setIsFixed(false);
            ++removed;
        }
    }

    // Mark remaining values as fixed clues
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (mGameCells[i][j].getValue() != 0) {
                mGameCells[i][j].setIsFixed(true);
            }
        }
    }
}

void GameBoard::makePuzzle(int fixedCount)
{
    int placed = 0,
        row = 0,
        col = 0,
        size = 9;
    do {
        row = 0;
        col = 0;
        placed = 0;

        while (placed < fixedCount) {
            int row = rand() % size;
            int col = rand() % size;

            if (!this->mGameCells[row][col].getIsFixed()) {
                this->mGameCells[row][col].setIsFixed(true);
                ++placed;
            }
        }
        this->countSolutions(1);
    } while (this->getNumSolutions() != 1);

    //set fixed numbers so they display correctly on board
    this->setFixedNums();
}

bool GameBoard::isNumSafe(int row, int col, int num)
{
    // Check the row and column
    for (int i = 0; i < 9; ++i) {
        if (mGameCells[row][i].getValue() == num) return false;
        if (mGameCells[i][col].getValue() == num) return false;
    }

    // Check the 3x3 box
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int r = boxStartRow + i;
            int c = boxStartCol + j;
            if (mGameCells[r][c].getValue() == num) return false;
        }
    }

    return true; // No conflicts found
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

bool GameBoard::fillBoardRecursive()
{
    int row = -1, col = -1;
    bool found = false;

    // Find the next empty cell (value == 0)
    for (int i = 0; i < 9 && !found; ++i) {
        for (int j = 0; j < 9 && !found; ++j) {
            if (mGameCells[i][j].getValue() == 0) {
                row = i;
                col = j;
                found = true;
            }
        }
    }

    if (!found)
        return true; // All cells filled successfully

    // Generate shuffled numbers 1–9 manually
    int numbers[9] = { 1,2,3,4,5,6,7,8,9 };

    // Fisher-Yates shuffle (manual swap)
    for (int i = 8; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try each number in random order
    for (int i = 0; i < 9; ++i) {
        int num = numbers[i];

        if (isNumSafe(row, col, num)) {
            mGameCells[row][col].setValue(num);

            if (fillBoardRecursive())
                return true;

            mGameCells[row][col].setValue(0); // Backtrack
        }
    }

    return false; // Trigger backtracking
}

int GameBoard::getProgress()
{
    int row = 0,
        col = 0;

    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (this->mGameCells[row][col].getValue() != 0) {
                this->setNumFilled(this->getNumFilled() + 1.0);
            }
        }
    }

    return (int)((this->getNumFilled()/this->getNumBoard()) * 100);
}

void GameBoard::printProgress(int percent, int width)
{
    int i = 0,
        filled = (percent * width) / 100;

    cout << "[";

    for (i = 0; i < width; ++i) {

        if (i < filled) {
            cout << u8"█";
        }
        else {
            cout << " ";
        }
    }
    cout << "] " << percent << "%\r";
}

void GameBoard::updateStats()
{
    int percentComp = 0;
    this->setNumFilled(0);

    percentComp = this->getProgress();

    this->printProgress(percentComp, 30);

    if (round(percentComp) == 100) {
        cout << "test" << endl;
    }
}

void GameBoard::countSolutions(int maxSolutions)
{
    mNumSolutions = 0;

    countSolutionsRecursive(mNumSolutions, maxSolutions);
}

bool GameBoard::countSolutionsRecursive(int& numSolutions, int maxSolutions)
{
    if (numSolutions >= maxSolutions)
        return false;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!mGameCells[row][col].getIsFixed() && mGameCells[row][col].getValue() == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isNumSafe(row, col, num)) {
                        mGameCells[row][col].setValue(num);

                        if (countSolutionsRecursive(numSolutions, maxSolutions))
                            return true;

                        mGameCells[row][col].setValue(0); // backtrack
                    }
                }
                return false; // No valid number, backtrack
            }
        }
    }

    // All cells are filled, solution found
    numSolutions++;
    return false; // Continue to count more solutions
}

void GameBoard::setFixedNums()
{
    int row = 0,
        col = 0;

    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (this->mGameCells[row][col].getIsFixed() == true) {
                this->mGameCells[row][col].setValue(this->mGameCells[row][col].getCorrectValue());
            }
        }
    }
}




