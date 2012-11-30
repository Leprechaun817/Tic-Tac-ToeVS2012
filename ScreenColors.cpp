#include "ScreenColors.h"

int ScreenColors::otherPlayerColor_ = 0;

ScreenColors::ScreenColors()
	: hConsole_(GetStdHandle(STD_OUTPUT_HANDLE)), colorAttribute_(0)
{
	otherPlayerColor_ = -1;

	//Initialize colorList with values
	int color;
	for(int i = 0; i < constListSize; i++)
	{
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
	screenColorInitialized = false;
}

void ScreenColors::DecidePlayerScreenColor()
{
	const string space = "\t";
	const string dash = " - ";
	char choiceLoop = 'a';
	ScreenColorListsIters_C colorListIter;

	system("cls");
	cout<<"What color do you want your piece to be?\n";
	for(unsigned int i = 1; i < constListSize; i++)
	{
		colorListIter = colorList.find(i);
		SetTextColor((colorListIter->second));
		cout<<space<<choiceLoop++<<dash<<colorNames[i];

		if((i + 1) == constListSize)
			cout<<"\n";
		else if((i % 2) == 0)
			cout<<"\n";
	}
	ResetConsoleColor();
	
	char selection;
	cout<<"Please enter the letter which represents your choice.\n";
	cout<<"Ex. a\n";
	cin>>selection;
	bool checkForOtherPlayer = false;
	while(!checkForOtherPlayer)
	{
		//Reset choiceLoop back to the letter a
		choiceLoop = 'a';
		if(otherPlayerColor_ == -1)
		{
			int x = 1;
			bool selectionGood = false;
			for(char i = 'a'; i <= 'o'; i++)
			{
				if(selection == i || selection == (i - 32))
				{
					colorListIter = colorList.find(x++);
					SetPlayerTextColor(colorListIter->second);
					checkForOtherPlayer = true;
					selectionGood = true;
					break;
				}
				else
					x++;
			}

			if(!selectionGood)
			{
				ResetConsoleColor();
				cout<<"That wasn't one of your choices.\n";
				cout<<"Please re-enter your choice.\n";
				cin>>selection;
			}
		}
		else
		{
			int x = 1;
			bool selectionGood = false;
			bool reCheck = false;
			for(char i = 'a'; i <= 'o'; i++)
			{
				if(selection == i || selection == (i - 32))
				{
					colorListIter = colorList.find(x++);
					if(otherPlayerColor_ == (colorListIter->second))
					{
						ChangeErrorTextColor((colorListIter->second));
						cout<<" has already been chosen by the other player.\n";
						cout<<"Please make another choice.\n";
						cin>>selection;
						reCheck = true;
						break;
					}
					else
					{
						colorAttribute_ = colorListIter->second;
						checkForOtherPlayer = true;
						selectionGood = true;
						break;
					}
				}
				else
					x++;
			}

			if(!selectionGood && !reCheck)
			{
				ResetConsoleColor();
				cout<<"That wasn't one of your choices.\n";
				cout<<"Please re-enter your choice.\n";
				cin>>selection;
			}
		}
	}

	screenColorInitialized = true;
}

void ScreenColors::SetPlayerTextColor(int color)
{
	colorAttribute_ = color;
	otherPlayerColor_ = color;
}

void ScreenColors::ChangeErrorTextColor(int color)
{
	SetTextColor(color);
	ScreenColorListsIters_C colorListIter;
	for(unsigned int i = 1; i < colorNames.size(); i++)
	{
		colorListIter = colorList.find(i);
		if((colorListIter->second) == color)
		{
			cout<<colorNames[i];
			break;
		}
	}
	ResetConsoleColor();
}

void ScreenColors::ResetConsoleColor()
{
	SetConsoleTextAttribute(hConsole_, dark_white);
}

void ScreenColors::SetTextColor(int color)
{
	SetConsoleTextAttribute(hConsole_, color);
}

void ScreenColors::SetTextToPlayerColor() const
{
	if(screenColorInitialized)
		SetConsoleTextAttribute(hConsole_, colorAttribute_);
	else
		throw Exception(err.Invalid_Variable_Access);
}

const int ScreenColors::GetTextColor() const
{
	if(screenColorInitialized)
		return colorAttribute_;
	else
		throw Exception(err.Invalid_Variable_Access);
}