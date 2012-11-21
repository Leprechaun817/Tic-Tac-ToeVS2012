#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class ScreenColors
{
public:
	ScreenColors();
	void DecidePlayerScreenColor();
	void SetTextToPlayerColor() const;
	void ResetConsoleColor();

//Color constants
private:
	static const int black;
	static const int dark_blue;
	static const int dark_green;
	static const int dark_cyan;
	static const int dark_red;
	static const int dark_purple;
	static const int dark_yellow;
	static const int dark_white;
	static const int gray;
	static const int blue;
	static const int green;
	static const int cyan;
	static const int red;
	static const int purple;
	static const int yellow;
	static const int white;
	
//Regular Variables
private:
	HANDLE hConsole_;
	//Actual player color, shows what will appear on screen
	int colorAttribute_;
	static int otherPlayerColor_;

//Private Functions
private:
	void SetPlayerTextColor(int color);
	char ChangeErrorTextColor(int color);
};
