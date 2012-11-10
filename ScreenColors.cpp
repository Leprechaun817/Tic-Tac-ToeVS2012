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
int ScreenColors::otherPlayerColor = 0;

ScreenColors::ScreenColors()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	otherPlayerColor = -1;
	colorAttribute = 0;
}

void ScreenColors::DecidePlayerScreenColor()
{
	char selection;
	cout<<"What color do you want your piece to be?"<<endl;
	SetConsoleTextAttribute(hConsole, dark_blue);
	cout<<"		a - dark blue";
	SetConsoleTextAttribute(hConsole, dark_green);
	cout<<"		b - dark green\n";
	SetConsoleTextAttribute(hConsole, dark_cyan);
	cout<<"		c - dark cyan";
	SetConsoleTextAttribute(hConsole, dark_red);
	cout<<"		d - dark red\n";
	SetConsoleTextAttribute(hConsole, dark_purple);
	cout<<"		e - dark purple";
	SetConsoleTextAttribute(hConsole, dark_yellow);
	cout<<"		f - dark yellow\n";
	SetConsoleTextAttribute(hConsole, dark_white);
	cout<<"		g - dark white";
	SetConsoleTextAttribute(hConsole, gray);
	cout<<"		h - gray\n";
	SetConsoleTextAttribute(hConsole, blue);
	cout<<"		i - blue";
	SetConsoleTextAttribute(hConsole, green);
	cout<<"		j - green\n";
	SetConsoleTextAttribute(hConsole, cyan);
	cout<<"		k - cyan";
	SetConsoleTextAttribute(hConsole, red);
	cout<<"		l - red\n";
	SetConsoleTextAttribute(hConsole, purple);
	cout<<"		m - purple";
	SetConsoleTextAttribute(hConsole, yellow);
	cout<<"		n - yellow\n";
	SetConsoleTextAttribute(hConsole, white);
	cout<<"		o - white\n";
	
	ResetConsoleColor();
	cout<<"Please enter the letter which represents your choice.\n";
	cout<<"Ex. a\n";
	cin>>selection;
	bool check = false;
	while(check == false)
	{
		if(otherPlayerColor == 0)
		{
			switch(selection)
			{
			case 'a':
			case 'A':
				SetPlayerTextColor(dark_blue);
				check = true;
				break;
			case 'b':
			case 'B':
				SetPlayerTextColor(dark_green);
				check = true;
				break;
			case 'c':
			case 'C':
				SetPlayerTextColor(dark_cyan);
				check = true;
				break;
			case 'd':
			case 'D':
				SetPlayerTextColor(dark_red);
				check = true;
				break;
			case 'e':
			case 'E':
				SetPlayerTextColor(dark_purple);
				check = true;
				break;
			case 'f':
			case 'F':
				SetPlayerTextColor(dark_yellow);
				check = true;
				break;
			case 'g':
			case 'G':
				SetPlayerTextColor(dark_white);
				check = true;
				break;
			case 'h':
			case 'H':
				SetPlayerTextColor(gray);
				check = true;
				break;
			case 'i':
			case 'I':
				SetPlayerTextColor(blue);
				check = true;
				break;
			case 'j':
			case 'J':
				SetPlayerTextColor(green);
				check = true;
				break;
			case 'k':
			case 'K':
				SetPlayerTextColor(cyan);
				check = true;
				break;
			case 'l':
			case 'L':
				SetPlayerTextColor(red);
				check = true;
				break;
			case 'm':
			case 'M':
				SetPlayerTextColor(purple);
				check = true;
				break;
			case 'n':
			case 'N':
				SetPlayerTextColor(yellow);
				check = true;
				break;
			case 'o':
			case 'O':
				SetPlayerTextColor(white);
				check = true;
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
				if(otherPlayerColor == dark_blue)
				{
					selection = ChangeErrorTextColor(dark_blue);
				}
				else
				{
					colorAttribute = dark_blue;
					check = true;
				}
				break;
			case 'b':
			case 'B':
				if(otherPlayerColor == dark_green)
				{
					selection = ChangeErrorTextColor(dark_green);
				}
				else
				{
					colorAttribute = dark_green;
					check = true;
				}
				break;
			case 'c':
			case 'C':
				if(otherPlayerColor == dark_cyan)
				{
					selection = ChangeErrorTextColor(dark_cyan);
				}
				else
				{
					colorAttribute = dark_cyan;
					check = true;
				}
				break;
			case 'd':
			case 'D':
				if(otherPlayerColor == dark_red)
				{
					selection = ChangeErrorTextColor(dark_red);
				}
				else
				{
					colorAttribute = dark_red;
					check = true;
				}
				break;
			case 'e':
			case 'E':
				if(otherPlayerColor == dark_purple)
				{
					selection = ChangeErrorTextColor(dark_purple);
				}
				else
				{
					colorAttribute = dark_purple;
					check = true;
				}
				break;
			case 'f':
			case 'F':
				if(otherPlayerColor == dark_yellow)
				{
					selection = ChangeErrorTextColor(dark_yellow);
				}
				else
				{
					colorAttribute = dark_yellow;
					check = true;
				}
				break;
			case 'g':
			case 'G':
				if(otherPlayerColor == dark_white)
				{
					selection = ChangeErrorTextColor(dark_white);
				}
				else
				{
					colorAttribute = dark_white;
					check = true;
				}
				break;
			case 'h':
			case 'H':
				if(otherPlayerColor == gray)
				{
					selection = ChangeErrorTextColor(gray);
				}
				else
				{
					colorAttribute = gray;
					check = true;
				}
				break;
			case 'i':
			case 'I':
				if(otherPlayerColor == blue)
				{
					selection = ChangeErrorTextColor(blue);
				}
				else
				{
					colorAttribute = blue;
					check = true;
				}
				break;
			case 'j':
			case 'J':
				if(otherPlayerColor == green)
				{
					selection = ChangeErrorTextColor(green);
				}
				else
				{
					colorAttribute = green;
					check = true;
				}
				break;
			case 'k':
			case 'K':
				if(otherPlayerColor == cyan)
				{
					selection = ChangeErrorTextColor(cyan);
				}
				else
				{
					colorAttribute = cyan;
					check = true;
				}
				break;
			case 'l':
			case 'L':
				if(otherPlayerColor == red)
				{
					selection = ChangeErrorTextColor(red);
				}
				else
				{
					colorAttribute = red;
					check = true;
				}
				break;
			case 'm':
			case 'M':
				if(otherPlayerColor == purple)
				{
					selection = ChangeErrorTextColor(purple);
				}
				else
				{
					colorAttribute = purple;
					check = true;
				}
				break;
			case 'n':
			case 'N':
				if(otherPlayerColor == yellow)
				{
					selection = ChangeErrorTextColor(yellow);
				}
				else
				{
					colorAttribute = yellow;
					check = true;
				}
				break;
			case 'o':
			case 'O':
				if(otherPlayerColor == white)
				{
					selection = ChangeErrorTextColor(white);
				}
				else
				{
					colorAttribute = white;
					check = true;
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
	colorAttribute = color;
	otherPlayerColor = color;
}

char ScreenColors::ChangeErrorTextColor(int color)
{
	char returnSelection;
	SetConsoleTextAttribute(hConsole, color);
	
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
	SetConsoleTextAttribute(hConsole, colorAttribute);
}

void ScreenColors::ResetConsoleColor()
{
	SetConsoleTextAttribute(hConsole, dark_white);
}