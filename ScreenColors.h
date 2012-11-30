#include <iostream>
#include <conio.h>
#include <array>
#include <map>
#include <Windows.h>
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef map<const int, int> ScreenColorLists;
typedef map<const int, int>::const_iterator ScreenColorListsIters_C;

class ScreenColors
{
public:
	ScreenColors();
	void DecidePlayerScreenColor();
	void SetTextToPlayerColor() const;
	void ResetConsoleColor();
	const int GetTextColor() const;

//Color constants
private:
	static const int black = 0, dark_blue = 1, dark_green = 2, dark_cyan = 3, dark_red = 4, dark_purple = 5, dark_yellow = 6, dark_white = 7, gray = 8, blue = 9, green = 10, cyan = 11, 
					 red = 12, purple = 13, yellow = 14, white = 15;
	
//Local Class Constants
private:
	static const int constListSize = 16;

//Container variables
private:
	ScreenColorLists colorList;
	array<string, 16> colorNames;
	ErrorTypes err;

//Regular Variables
private:
	HANDLE hConsole_;
	//Actual player color, shows what will appear on screen
	int colorAttribute_;
	bool screenColorInitialized;
	static int otherPlayerColor_;

//Private Functions
private:
	void SetPlayerTextColor(int color);
	void ChangeErrorTextColor(int color);
	void SetTextColor(int color);
};
