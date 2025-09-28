#include "Cell.hpp"

Cell::Cell(Cell& newCell)
{
	this->mValue = newCell.getValue();
	this->mCorrectValue = newCell.getCorrectValue();
	this->mIsFixed = newCell.getIsFixed();
	this->mHiLightStr = newCell.getHiLightStr();
}

Cell& Cell::operator=(Cell& rhs)
{
	this->mValue = rhs.getValue();
	this->mCorrectValue = rhs.getCorrectValue();
	this->mIsFixed = rhs.getIsFixed();
	this->mHiLightStr = rhs.getHiLightStr();

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
