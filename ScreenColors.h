#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class ScreenColors
{
private:
	//Color constants
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
	HANDLE hConsole;
	//Actual player color, shows what will appear on screen
	int colorAttribute;
	static int otherPlayerColor;
	void SetPlayerTextColor(int color);
	char ChangeErrorTextColor(int color);
public:
	ScreenColors();
	int GetColorAttribute() { return colorAttribute; }
	void ResetConsoleColor();
};
