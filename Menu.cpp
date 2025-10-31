#include "Menu.hpp"

Menu::Menu()
{
	int index = 0;

	this->mBorderWidth = 0;
	this->mBorderHeight = 0;
	this->mPadding = 0;
	this->mOptionsEnd = 0;
	this->mMaxOptionLength = 0;
	this->mTrackHiLight = 1;	//always start by highlighting the first option

	for (index = 0; index < 10; ++index) {
		this->mHiLightColor[index] = "";
		this->mOptions[index] = "";
	}
}

Menu& Menu::operator=(Menu& rhs)
{
	int index = 0;

	this->mBorderHeight = rhs.getBorderHeight();
	this->mBorderWidth = rhs.getBorderWidth();
	this->mOptionsEnd = rhs.getOptionsEnd();
	this->mPadding = rhs.getPadding();
	this->mTrackHiLight = rhs.getTrackHiLight();
	
	for (index = 0; index < 10; ++index) {
		this->mHiLightColor[index] = rhs.getHiLightColor(index);
		this->mOptions[index] = rhs.getOption(index);
	}

	return *this;
}

int Menu::getBorderWidth() const
{
	return this->mBorderWidth;
}

int Menu::getBorderHeight() const
{
	return this->mBorderHeight;
}

int Menu::getPadding() const
{
	return this->mPadding;
}

int Menu::getOptionsEnd() const
{
	return this->mOptionsEnd;
}

int Menu::getTrackHiLight() const
{
	return this->mTrackHiLight;
}

int Menu::getMaxOptionLength() const
{
	return this->mMaxOptionLength;
}

string Menu::getOption(const int index) const
{
	return this->mOptions[index];
}

string Menu::getHiLightColor(const int index) const
{
	return this->mHiLightColor[index];
}

void Menu::setBorderWidth(const int newWidth)
{
	this->mBorderWidth = newWidth;
}

void Menu::setBorderHeight(const int newHeight)
{
	this->mBorderHeight = newHeight;
}

void Menu::setPadding(const int newPadding)
{
	this->mPadding = newPadding;
}

void Menu::setOptionsEnd(const int newEnd)
{
	this->mOptionsEnd = newEnd;
}

void Menu::setTrackHiLight(const int newIndex)
{
	this->mTrackHiLight = newIndex;
}

void Menu::setMaxOptionLength(const int length)
{
	this->mMaxOptionLength = length;
}

void Menu::setOptions(const string newOptions[10])
{
	int index = 0;

	for (index = 0; index < 10; ++index) {
		this->mOptions[index] = newOptions[index];

		if (this->mOptions[index] != "") {
			++this->mOptionsEnd;
		}
	}
}

int Menu::scroll(int yOffset, int xOffset)
{
	int moveEvent = 0;
	char moveEventch = '\0';

	while (moveEvent != '\r') {
		this->showMenu(yOffset, xOffset);

		moveEvent = _getch();

		if (moveEvent == -32 || moveEvent == 224) {

			moveEvent = _getch();

			switch (moveEvent) {
			case 72:
				if (this->mTrackHiLight > 1) {
					--this->mTrackHiLight;		//move highlight up
				}
				break;
			case 80:
				if (this->mTrackHiLight < this->mOptionsEnd) {
					++this->mTrackHiLight;		//move highlight down
				}
				break;
			case 75:
				break;
			case 77:
				break;
			default:
				break;
			}
			
		}
		else {
			moveEventch = (char)moveEvent;
			if (moveEventch == 'w' && this->mTrackHiLight > 1) {
				--this->mTrackHiLight;
			}
			else if (moveEventch == 's' && this->mTrackHiLight < this->mOptionsEnd) {
				++this->mTrackHiLight;
			}
		}
	}

	return this->mTrackHiLight;
}

bool Menu::showMenu(int yOffset, int xOffset)
{
	bool isMenuDisplayed = true;
	int index = 0,
		index2 = 0;
	const string ESC = "\x1b[";
	const string HILIGHT = "\x1b[7m";
	const string END_HILIGHT = "\x1b[0m";

	cout << ESC << xOffset << ";" << yOffset << "H" << u8"┏";

	for (index = 0; index < this->getBorderWidth(); ++index) {
		cout << u8"━";
	}

	cout << u8"┓" << endl;

	for (index = 0; index < this->getBorderHeight(); ++index) {
		cout << ESC << xOffset + index + 1 << ";" << yOffset << "H" << u8"┃";

		for (index2 = 0; index2 < this->getPadding(); ++index2) {
			cout << " ";
		}

		//Highlight logic
		if (index == this->mTrackHiLight - 1) {
			cout << HILIGHT << this->getOption(index) << END_HILIGHT;
		}
		else {
			cout << this->getOption(index);
		}

		for (index2 = 0; index2 + this->getOption(index).length() < this->getBorderWidth() - 1; ++index2) {
			cout << " ";
		}

		cout << u8"┃" << endl;
	}

	cout << ESC << xOffset + index + 1 << ";" << yOffset << "H" << u8"┗";

	for (index = 0; index < this->getBorderWidth(); ++index) {
		cout << u8"━";
	}

	cout << u8"┛";

	return isMenuDisplayed;
}

void Menu::setupMenu()
{
	int i = 0,
		nonEmptyOptions = 0;

	this->setPadding(1);

	for (i = 0; i < 10; ++i) {
		if (this->getOption(i).length() > this->getMaxOptionLength()) {
			this->setMaxOptionLength(this->getOption(i).length());
		}
		if (this->getOption(i) != "") {
			++nonEmptyOptions;
		}
	}

	this->setBorderHeight(nonEmptyOptions);
	this->setBorderWidth(2*this->getPadding() + this->getMaxOptionLength());
}
