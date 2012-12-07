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

#include "ScreenColors.h"

const string ScreenColors::fatalErrorSound = "fatalErrorSound";

int ScreenColors::otherPlayerColor_ = 0;

ScreenColors::ScreenColors() throw()
	: hConsole_(GetStdHandle(STD_OUTPUT_HANDLE)), colorAttribute_(0)
{
	otherPlayerColor_ = -1;

	//Initialize colorList with values
	int color;
	for(int i = 0; i < constListSize; i++) {
		color = i % constListSize;
		colorList.insert(pair<const int, int>(i, color));
	}

	//Initialize colorNames array with values
	//Create temp array with color names and then copy it over to the colorNames array
	//A bit messy but it works
	array<string, constListSize> tempColorNames = {"black", "dark blue", "dark green", "dark cyan", "dark red", "dark purple", "dark yellow", "dark white", "gray", "blue", "green", "cyan",
												   "red", "purple", "yellow", "white"};
	colorNames = tempColorNames;
	//DecidePlayerScreenColor() must be run before the get/set functions can be accessed
	screenColorInitialized_ = false;
}

void ScreenColors::DecidePlayerScreenColor()
{
	const string space = "\t";
	const string dash = " - ";
	char choiceLoop = 'a';

	system("cls");
	cout<<"What color do you want your piece to be?\n";
	int x = 1;
	for(auto &i : colorList) {
		if((i.second) == 0)
			continue;
		
		SetConsoleTextAttribute(hConsole_, (i.second));
		cout<<space<<choiceLoop++<<dash<<colorNames[x];

		if((x + 1) == constListSize)
			cout<<"\n";
		else if((x % 2) == 0)
			cout<<"\n";
		x++;
	}
	ResetConsoleColor();
	
	char selection;
	cout<<"Please enter the letter which represents your choice.\n";
	cout<<"Ex. a\n";
	selection = GetSelection();
	bool checkForOtherPlayer = false;
	while(!checkForOtherPlayer) {
		ScreenColorListsIters_C colorListIter;
		//Reset choiceLoop back to the letter a
		choiceLoop = 'a';
		if(otherPlayerColor_ == -1) {
			int x = 1;
			bool selectionGood = false;
			for(char i = 'a'; i <= 'o'; i++)
				if(selection == i || selection == (i - 32)) {
					colorListIter = colorList.find(x++);
					SetPlayerTextColor(colorListIter->second);
					checkForOtherPlayer = true;
					selectionGood = true;
					break;
				}
				else
					x++;

			if(!selectionGood) {
				ResetConsoleColor();
				cout<<"\nThat wasn't one of your choices.\n";
				cout<<"Please re-enter your choice.\n";
				selection = GetSelection();
			}
		}
		else {
			int x = 1;
			bool selectionGood = false;
			bool reCheck = false;
			for(char i = 'a'; i <= 'o'; i++)
				if(selection == i || selection == (i - 32))
				{
					colorListIter = colorList.find(x++);
					if(otherPlayerColor_ == (colorListIter->second)) {
						ChangeErrorTextColor((colorListIter->second));
						cout<<" has already been chosen by the other player.\n";
						cout<<"Please make another choice.\n";
						selection = GetSelection();
						reCheck = true;
						break;
					}
					else {
						colorAttribute_ = colorListIter->second;
						checkForOtherPlayer = true;
						selectionGood = true;
						break;
					}
				}
				else
					x++;

			if(!selectionGood && !reCheck) {
				ResetConsoleColor();
				cout<<"\nThat wasn't one of your choices.\n";
				cout<<"Please re-enter your choice.\n";
				selection = GetSelection();
			}
		}
	}

	screenColorInitialized_ = true;
}

void ScreenColors::SetPlayerTextColor(int color)
{
	colorAttribute_ = color;
	otherPlayerColor_ = color;
}

void ScreenColors::ChangeErrorTextColor(int color)
{
	SetConsoleTextAttribute(hConsole_, color);
	int x = 0;
	for(auto &i : colorList) {
		if((i.second) == color) {
			cout<<"\n"<<colorNames[x];
			break;
		}
		x++;
	}
	ResetConsoleColor();
}

void ScreenColors::ResetConsoleColor()
{
	SetConsoleTextAttribute(hConsole_, dark_white);
}

void ScreenColors::SetTextToPlayerColor() const
{
	if(screenColorInitialized_)
		SetConsoleTextAttribute(hConsole_, colorAttribute_);
	else
		throw Exception(err.Invalid_Variable_Access);	//Play fatal error message here
}

const int ScreenColors::GetTextColor() const
{
	if(screenColorInitialized_)
		return colorAttribute_;
	else
		throw Exception(err.Invalid_Variable_Access);	//Play fatal error message here
}

void ScreenColors::OutputCharacterWithColor(char c, int color)
{
	SetConsoleTextAttribute(hConsole_, color);
	putchar(c);
	ResetConsoleColor();
}

char ScreenColors::GetSelection()
{
	COORD curPosition;
	curPosition.X = 0;
	curPosition.Y = 11;

	char ans;
	char output = ' ';
	bool getLoop = true;
	while(getLoop) {
		if(_kbhit()) {
			ans = _getch();
			if(ans == 'A' || ans == 'a') {
				OutputCharacterWithColor(ans, dark_blue);
				output = ans;
			}
			else if(ans == 'B' || ans == 'b') {
				OutputCharacterWithColor(ans, dark_green);
				output = ans;
			}
			else if(ans == 'C' || ans == 'c') {
				OutputCharacterWithColor(ans, dark_cyan);
				output = ans;
			}
			else if(ans == 'D' || ans == 'd') {
				OutputCharacterWithColor(ans, dark_red);
				output = ans;
			}
			else if(ans == 'E' || ans == 'e') {
				OutputCharacterWithColor(ans, dark_purple);
				output = ans;
			}
			else if(ans == 'F' || ans == 'f') {
				OutputCharacterWithColor(ans, dark_yellow);
				output = ans;
			}
			else if(ans == 'G' || ans == 'g') {
				OutputCharacterWithColor(ans, dark_white);
				output = ans;
			}
			else if(ans == 'H' || ans == 'h') {
				OutputCharacterWithColor(ans, gray);
				output = ans;
			}
			else if(ans == 'I' || ans == 'i') {
				OutputCharacterWithColor(ans, blue);
				output = ans;
			}
			else if(ans == 'J' || ans == 'j') {
				OutputCharacterWithColor(ans, green);
				output = ans;
			}
			else if(ans == 'K' || ans == 'k') {
				OutputCharacterWithColor(ans, cyan);
				output = ans;
			}
			else if(ans == 'L' || ans == 'l') {
				OutputCharacterWithColor(ans, red);
				output = ans;
			}
			else if(ans == 'M' || ans == 'm') {
				OutputCharacterWithColor(ans, purple);
				output = ans;
			}
			else if(ans == 'N' || ans == 'n') {
				OutputCharacterWithColor(ans, yellow);
				output = ans;
			}
			else if(ans == 'O' || ans == 'o') {
				OutputCharacterWithColor(ans, white);
				output = ans;
			}
			else if(ans == '\b') {
				ans = ' ';
				SetConsoleCursorPosition(hConsole_, curPosition);
				putchar(ans);
				SetConsoleCursorPosition(hConsole_, curPosition);
				output = ans;
			}
			else if(ans == '\r')
				getLoop = false;
			else {
				OutputCharacterWithColor(ans, dark_white);
				output = ans;
			}
		}
	}

	return output;
}