#include <iostream>
using std::string;

class Cell {
	public:
		//constructor
		Cell(int newVal = 0, int newCorrectVal = 0, bool newFixedness = false, string newStr = "\033[0m",
			bool newCorrectness = false)
			: mValue(newVal), mIsFixed(newFixedness), mHiLightStr(newStr), mCorrectValue(newCorrectVal),
				mIsCorrect(newCorrectness) {}

		//destructor
		virtual ~Cell() {}

		//copy constructor
		Cell(Cell& newCell);

		//copy assignment operator
		Cell& operator=(Cell& rhs);

		//public member functions
		int getValue() const;
		int getCorrectValue() const;
		bool getIsFixed() const;
		bool getIsCorrect() const;
		string getHiLightStr() const;

		void setValue(const int newVal);
		void setCorrectValue(const int newVal);
		void setIsFixed(const bool newFixedness);
		void setIsCorrect(const bool newCorrectness);
		void setHiLightStr(const string& newStr);

	private:
		//data members
		int mValue;
		int mCorrectValue;
		bool mIsFixed;
		bool mIsCorrect;
		string mHiLightStr;
};