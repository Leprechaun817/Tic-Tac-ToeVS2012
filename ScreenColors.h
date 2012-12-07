/********************************************************************************************
*********************************************************************************************
Aaron's Tic-Tac-Toe Clone
A 2 player verison of Tic-Tac-Toe game that's played on a console screen.

Copyright (C) 2012 Aaron Gagern

This file is part of Aaron's Tic-Tac-Toe Clone.

Aaron's Tic-Tac-Toe Clone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Aaron's Tic-Tac-Toe Clone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Aaron's Tic-Tac-Toe Clone.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************************
********************************************************************************************/

#pragma once
#include <iostream>
#include <conio.h>
#include <array>
#include <map>
#include <algorithm>
#include <Windows.h>
#include "SoundEngine.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef map<const int, int> ScreenColorLists;
typedef map<const int, int>::const_iterator ScreenColorListsIters_C;

class ScreenColors
{
public:
	ScreenColors() throw();
	void DecidePlayerScreenColor();
	void SetTextToPlayerColor() const;
	void ResetConsoleColor();
	const int GetTextColor() const;

//Color constants
private:
	static const int black = 0, dark_blue = 1, dark_green = 2, dark_cyan = 3, dark_red = 4, dark_purple = 5, dark_yellow = 6, dark_white = 7, gray = 8, blue = 9, green = 10, cyan = 11, 
					 red = 12, purple = 13, yellow = 14, white = 15;
	static const string fatalErrorSound;
	
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
	bool screenColorInitialized_;
	static int otherPlayerColor_;

//Private Functions
private:
	void SetPlayerTextColor(int color);
	void ChangeErrorTextColor(int color);
	char GetSelection();
	void OutputCharacterWithColor(char c, int color);
};
