#include "Cell.hpp"

Cell::Cell(Cell& newCell)
{
	this->mValue = newCell.getValue();
	this->mCorrectValue = newCell.getCorrectValue();
	this->mIsFixed = newCell.getIsFixed();
	this->mHiLightStr = newCell.getHiLightStr();
	this->mIsCorrect = newCell.getIsCorrect();
	this->mIsWrong = newCell.getIsWrong();
}

Cell& Cell::operator=(Cell& rhs)
{
	this->mValue = rhs.getValue();
	this->mCorrectValue = rhs.getCorrectValue();
	this->mIsFixed = rhs.getIsFixed();
	this->mHiLightStr = rhs.getHiLightStr();
	this->mIsCorrect = rhs.getIsCorrect();
	this->mIsWrong = rhs.getIsWrong();

	return *this;
}

int Cell::getValue() const
{
	return this->mValue;
}

int Cell::getCorrectValue() const
{
	return this->mCorrectValue;
}

bool Cell::getIsFixed() const
{
	return this->mIsFixed;
}

bool Cell::getIsCorrect() const
{
	return this->mIsCorrect;
}

bool Cell::getIsWrong() const
{
	return this->mIsWrong;
}

string Cell::getHiLightStr() const
{
	return this->mHiLightStr;
}

void Cell::setValue(const int newVal)
{
	this->mValue = newVal;
}

void Cell::setCorrectValue(const int newVal)
{
	this->mCorrectValue = newVal;
}

void Cell::setIsFixed(const bool newFixedness)
{
	this->mIsFixed = newFixedness;
}

void Cell::setIsCorrect(const bool newCorrectness)
{
	this->mIsCorrect = newCorrectness;
}

void Cell::setHiLightStr(const string& newStr)
{
	this->mHiLightStr = newStr;
}

void Cell::setIsWrong(bool newWrongness)
{
	this->mIsWrong = newWrongness;
}
