#include "ScreenColors.h"

const int ScreenColors::black = 0;
const int ScreenColors::dark_blue = 1 % 16;
const int ScreenColors::dark_green = 2 % 16;
const int ScreenColors::dark_cyan = 3 % 16;
const int ScreenColors::dark_red = 4 % 16;
const int ScreenColors::dark_purple = 5 % 16;
const int ScreenColors::dark_yellow = 6 % 16;
const int ScreenColors::dark_white = 7 % 16;
const int ScreenColors::gray = 8 % 16;
const int ScreenColors::blue = 9 % 16;
const int ScreenColors::green = 10 % 16;
const int ScreenColors::cyan = 11 % 16;
const int ScreenColors::red = 12 % 16;
const int ScreenColors::purple = 13 % 16;
const int ScreenColors::yellow = 14 % 16;
const int ScreenColors::white = 15 % 16;
int ScreenColors::otherPlayerColor_ = 0;

ScreenColors::ScreenColors()
{
	hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
	otherPlayerColor_ = -1;
	colorAttribute_ = 0;
}

void ScreenColors::DecidePlayerScreenColor()
{
	char selection;
	cout<<"What color do you want your piece to be?"<<endl;
	SetConsoleTextAttribute(hConsole_, dark_blue);
	cout<<"		a - dark blue";
	SetConsoleTextAttribute(hConsole_, dark_green);
	cout<<"		b - dark green\n";
	SetConsoleTextAttribute(hConsole_, dark_cyan);
	cout<<"		c - dark cyan";
	SetConsoleTextAttribute(hConsole_, dark_red);
	cout<<"		d - dark red\n";
	SetConsoleTextAttribute(hConsole_, dark_purple);
	cout<<"		e - dark purple";
	SetConsoleTextAttribute(hConsole_, dark_yellow);
	cout<<"		f - dark yellow\n";
	SetConsoleTextAttribute(hConsole_, dark_white);
	cout<<"		g - dark white";
	SetConsoleTextAttribute(hConsole_, gray);
	cout<<"		h - gray\n";
	SetConsoleTextAttribute(hConsole_, blue);
	cout<<"		i - blue";
	SetConsoleTextAttribute(hConsole_, green);
	cout<<"		j - green\n";
	SetConsoleTextAttribute(hConsole_, cyan);
	cout<<"		k - cyan";
	SetConsoleTextAttribute(hConsole_, red);
	cout<<"		l - red\n";
	SetConsoleTextAttribute(hConsole_, purple);
	cout<<"		m - purple";
	SetConsoleTextAttribute(hConsole_, yellow);
	cout<<"		n - yellow\n";
	SetConsoleTextAttribute(hConsole_, white);
	cout<<"		o - white\n";
	
	ResetConsoleColor();
	cout<<"Please enter the letter which represents your choice.\n";
	cout<<"Ex. a\n";
	cin>>selection;
	bool checkForOtherPlayer = false;
	while(!checkForOtherPlayer)
	{
		if(otherPlayerColor_ == 0)
		{
			switch(selection)
			{
			case 'a':
			case 'A':
				SetPlayerTextColor(dark_blue);
				checkForOtherPlayer = true;
				break;
			case 'b':
			case 'B':
				SetPlayerTextColor(dark_green);
				checkForOtherPlayer = true;
				break;
			case 'c':
			case 'C':
				SetPlayerTextColor(dark_cyan);
				checkForOtherPlayer = true;
				break;
			case 'd':
			case 'D':
				SetPlayerTextColor(dark_red);
				checkForOtherPlayer = true;
				break;
			case 'e':
			case 'E':
				SetPlayerTextColor(dark_purple);
				checkForOtherPlayer = true;
				break;
			case 'f':
			case 'F':
				SetPlayerTextColor(dark_yellow);
				checkForOtherPlayer = true;
				break;
			case 'g':
			case 'G':
				SetPlayerTextColor(dark_white);
				checkForOtherPlayer = true;
				break;
			case 'h':
			case 'H':
				SetPlayerTextColor(gray);
				checkForOtherPlayer = true;
				break;
			case 'i':
			case 'I':
				SetPlayerTextColor(blue);
				checkForOtherPlayer = true;
				break;
			case 'j':
			case 'J':
				SetPlayerTextColor(green);
				checkForOtherPlayer = true;
				break;
			case 'k':
			case 'K':
				SetPlayerTextColor(cyan);
				checkForOtherPlayer = true;
				break;
			case 'l':
			case 'L':
				SetPlayerTextColor(red);
				checkForOtherPlayer = true;
				break;
			case 'm':
			case 'M':
				SetPlayerTextColor(purple);
				checkForOtherPlayer = true;
				break;
			case 'n':
			case 'N':
				SetPlayerTextColor(yellow);
				checkForOtherPlayer = true;
				break;
			case 'o':
			case 'O':
				SetPlayerTextColor(white);
				checkForOtherPlayer = true;
				break;
			default:
				ResetConsoleColor();
				cout<<"That wasn't one of the choices.\n";
				cout<<"Please reenter your choice.\n";
				cin>>selection;
			}
		}
		else
		{
			switch(selection)
			{
			case 'a':
			case 'A':
				if(otherPlayerColor_ == dark_blue)
					selection = ChangeErrorTextColor(dark_blue);
				else
				{
					colorAttribute_ = dark_blue;
					checkForOtherPlayer = true;
				}
				break;
			case 'b':
			case 'B':
				if(otherPlayerColor_ == dark_green)
					selection = ChangeErrorTextColor(dark_green);
				else
				{
					colorAttribute_ = dark_green;
					checkForOtherPlayer = true;
				}
				break;
			case 'c':
			case 'C':
				if(otherPlayerColor_ == dark_cyan)
					selection = ChangeErrorTextColor(dark_cyan);
				else
				{
					colorAttribute_ = dark_cyan;
					checkForOtherPlayer = true;
				}
				break;
			case 'd':
			case 'D':
				if(otherPlayerColor_ == dark_red)
					selection = ChangeErrorTextColor(dark_red);
				else
				{
					colorAttribute_ = dark_red;
					checkForOtherPlayer = true;
				}
				break;
			case 'e':
			case 'E':
				if(otherPlayerColor_ == dark_purple)
					selection = ChangeErrorTextColor(dark_purple);
				else
				{
					colorAttribute_ = dark_purple;
					checkForOtherPlayer = true;
				}
				break;
			case 'f':
			case 'F':
				if(otherPlayerColor_ == dark_yellow)
					selection = ChangeErrorTextColor(dark_yellow);
				else
				{
					colorAttribute_ = dark_yellow;
					checkForOtherPlayer = true;
				}
				break;
			case 'g':
			case 'G':
				if(otherPlayerColor_ == dark_white)
					selection = ChangeErrorTextColor(dark_white);
				else
				{
					colorAttribute_ = dark_white;
					checkForOtherPlayer = true;
				}
				break;
			case 'h':
			case 'H':
				if(otherPlayerColor_ == gray)
					selection = ChangeErrorTextColor(gray);
				else
				{
					colorAttribute_ = gray;
					checkForOtherPlayer = true;
				}
				break;
			case 'i':
			case 'I':
				if(otherPlayerColor_ == blue)
					selection = ChangeErrorTextColor(blue);
				else
				{
					colorAttribute_ = blue;
					checkForOtherPlayer = true;
				}
				break;
			case 'j':
			case 'J':
				if(otherPlayerColor_ == green)
					selection = ChangeErrorTextColor(green);
				else
				{
					colorAttribute_ = green;
					checkForOtherPlayer = true;
				}
				break;
			case 'k':
			case 'K':
				if(otherPlayerColor_ == cyan)
					selection = ChangeErrorTextColor(cyan);
				else
				{
					colorAttribute_ = cyan;
					checkForOtherPlayer = true;
				}
				break;
			case 'l':
			case 'L':
				if(otherPlayerColor_ == red)
					selection = ChangeErrorTextColor(red);
				else
				{
					colorAttribute_ = red;
					checkForOtherPlayer = true;
				}
				break;
			case 'm':
			case 'M':
				if(otherPlayerColor_ == purple)
					selection = ChangeErrorTextColor(purple);
				else
				{
					colorAttribute_ = purple;
					checkForOtherPlayer = true;
				}
				break;
			case 'n':
			case 'N':
				if(otherPlayerColor_ == yellow)
					selection = ChangeErrorTextColor(yellow);
				else
				{
					colorAttribute_ = yellow;
					checkForOtherPlayer = true;
				}
				break;
			case 'o':
			case 'O':
				if(otherPlayerColor_ == white)
					selection = ChangeErrorTextColor(white);
				else
				{
					colorAttribute_ = white;
					checkForOtherPlayer = true;
				}
				break;
			default:
				ResetConsoleColor();
				cout<<"That wasn't one of the choices.\n";
				cout<<"Please reenter your choice.\n";
				cin>>selection;
			}
		}
	}
}

void ScreenColors::SetPlayerTextColor(int color)
{
	colorAttribute_ = color;
	otherPlayerColor_ = color;
}

char ScreenColors::ChangeErrorTextColor(int color)
{
	char returnSelection;
	SetConsoleTextAttribute(hConsole_, color);
	
	switch(color)
	{
	case dark_blue:
		cout<<"Dark blue";
		break;
	case dark_green:
		cout<<"Dark green";
		break;
	case dark_cyan:
		cout<<"Dark cyan";
		break;
	case dark_red:
		cout<<"Dark red";
		break;
	case dark_purple:
		cout<<"Dark purple";
		break;
	case dark_yellow:
		cout<<"Dark yellow";
		break;
	case dark_white:
		cout<<"Dark white";
		break;
	case gray:
		cout<<"Gray";
		break;
	case blue:
		cout<<"Blue";
		break;
	case green:
		cout<<"Green";
		break;
	case cyan:
		cout<<"Cyan";
		break;
	case red:
		cout<<"Red";
		break;
	case purple:
		cout<<"Purple";
		break;
	case yellow:
		cout<<"Yellow";
		break;
	case white:
		cout<<"White";
		break;
	}
	
	ResetConsoleColor();
	cout<<" has already been chosen by the other player.\n";
	cout<<"Please make another choice.\n";
	cin>>returnSelection;

	return returnSelection;
}

void ScreenColors::SetTextToPlayerColor() const
{
	SetConsoleTextAttribute(hConsole_, colorAttribute_);
}

void ScreenColors::ResetConsoleColor()
{
	SetConsoleTextAttribute(hConsole_, dark_white);
}