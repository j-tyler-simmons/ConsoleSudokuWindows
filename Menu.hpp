#pragma once
#include <iostream>
#include <conio.h>
using std::string;
using std::cout;
using std::endl;

class Menu {
	public:
		//constructor
		Menu();

		//destructor
		virtual ~Menu() {}

		//copy assignment operator
		Menu& operator=(Menu& rhs);

		//accessors
		int getBorderWidth() const;
		int getBorderHeight() const;
		int getPadding() const;
		int getOptionsEnd() const;
		int getTrackHiLight() const;
		int getMaxOptionLength() const;
		string getOption(const int index) const;
		string getHiLightColor(const int index) const;

		void setBorderWidth(const int newWidth);
		void setBorderHeight(const int newHeight);
		void setPadding(const int newPadding);
		void setOptionsEnd(const int newEnd);
		void setTrackHiLight(const int newIndex);
		void setMaxOptionLength(const int length);
		void setOptions(const string newOptions[10]);

		//public member functions
		int scroll(int yOffset, int xOffset);
		void setupMenu();

	private:
		//data members
		int mBorderWidth;
		int mBorderHeight;
		int mPadding;
		int mOptionsEnd;
		int mTrackHiLight;
		int mMaxOptionLength;
		string mOptions[10];
		string mHiLightColor[10];

		//private member functions
		bool showMenu(int yOffset, int xOffset);
};