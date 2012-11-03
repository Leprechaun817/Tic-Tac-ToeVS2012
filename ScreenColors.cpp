#include "ScreenColors.h"

const int ScreenColors::black = 0;
const int ScreenColors::dark_blue = 1 * 16;
const int ScreenColors::dark_green = 2 * 16;
const int ScreenColors::dark_cyan = 3 * 16;
const int ScreenColors::dark_red = 4 * 16;
const int ScreenColors::dark_purple = 5 * 16;
const int ScreenColors::dark_yellow = 6 * 16;
const int ScreenColors::dark_white = 7 * 16;
const int ScreenColors::gray = 8 * 16;
const int ScreenColors::blue = 9 * 16;
const int ScreenColors::green = 10 * 16;
const int ScreenColors::cyan = 11 * 16;
const int ScreenColors::red = 12 * 16;
const int ScreenColors::purple = 13 * 16;
const int ScreenColors::yellow = 14 * 16;
const int ScreenColors::white = 15 * 16;
//New to VS2012, static variables also must be declared in the same way constants must be declared inside a class
int ScreenColors::otherPlayerColor = 0;

ScreenColors::ScreenColors()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
				colorAttribute = dark_blue;
				otherPlayerColor = dark_blue;
				check = true;
				break;
			case 'b':
			case 'B':
				colorAttribute = dark_green;
				otherPlayerColor = dark_green;
				check = true;
				break;
			case 'c':
			case 'C':
				colorAttribute = dark_cyan;
				otherPlayerColor = dark_cyan;
				check = true;
				break;
			case 'd':
			case 'D':
				colorAttribute = dark_red;
				otherPlayerColor = dark_red;
				check = true;
				break;
			case 'e':
			case 'E':
				colorAttribute = dark_purple;
				otherPlayerColor = dark_purple;
				check = true;
				break;
			case 'f':
			case 'F':
				colorAttribute = dark_yellow;
				otherPlayerColor = dark_yellow;
				check = true;
				break;
			case 'g':
			case 'G':
				colorAttribute = dark_white;
				otherPlayerColor = dark_white;
				check = true;
				break;
			case 'h':
			case 'H':
				colorAttribute = gray;
				otherPlayerColor = gray;
				check = true;
				break;
			case 'i':
			case 'I':
				colorAttribute = blue;
				otherPlayerColor = blue;
				check = true;
				break;
			case 'j':
			case 'J':
				colorAttribute = green;
				otherPlayerColor = green;
				check = true;
				break;
			case 'k':
			case 'K':
				colorAttribute = cyan;
				otherPlayerColor = cyan;
				check = true;
				break;
			case 'l':
			case 'L':
				colorAttribute = red;
				otherPlayerColor = red;
				check = true;
				break;
			case 'm':
			case 'M':
				colorAttribute = purple;
				otherPlayerColor = purple;
				check = true;
				break;
			case 'n':
			case 'N':
				colorAttribute = yellow;
				otherPlayerColor = yellow;
				check = true;
				break;
			case 'o':
			case 'O':
				colorAttribute = white;
				otherPlayerColor = white;
				check = true;
				break;
			default:
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
					SetConsoleTextAttribute(hConsole, dark_blue);
					cout<<"Dark blue";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by the other player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_green);
					cout<<"Dark green";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by the other player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_cyan);
					cout<<"Dark cyan";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by the other player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_red);
					cout<<"Dark red";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_purple);
					cout<<"Dark purple";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_yellow);
					cout<<"Dark yellow";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, dark_white);
					cout<<"Dark white";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, gray);
					cout<<"Gray";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, blue);
					cout<<"Blue";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, green);
					cout<<"Green";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, cyan);
					cout<<"Cyan";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, red);
					cout<<"Red";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, purple);
					cout<<"Purple";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					SetConsoleTextAttribute(hConsole, yellow);
					cout<<"Yellow";
					SetConsoleTextAttribute(hConsole, white);
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
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
					cout<<"White";
					cout<<" has already been chosen by another player.\n";
					cout<<"Please make another choice.\n";
					cin>>selection;
				}
				else
				{
					colorAttribute = white;
					check = true;
				}
				break;
			default:
				cout<<"That wasn't one of the choices.\n";
				cout<<"Please reenter your choice.\n";
				cin>>selection;
			}
		}
	}
}