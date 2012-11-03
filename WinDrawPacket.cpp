#include "WinDrawPacket.h"

//Constants
//Win/Draw constants
const int WinDrawPacket::noWinDraw = 0;
const int WinDrawPacket::win = 1;
const int WinDrawPacket::draw = 2;

//Board Win Possibilities
const int WinDrawPacket::across = 1;
const int WinDrawPacket::down = 2;
const int WinDrawPacket::diagonal = 3;

//Diagonal winning possibilities
const int WinDrawPacket::diagonalLeft = 1;
const int WinDrawPacket::diagonalRight = 2;

//Column constants
const int WinDrawPacket::colmOne = 10;
const int WinDrawPacket::colmTwo = 20;
const int WinDrawPacket::colmThree = 30;
const int WinDrawPacket::colmFour = 40;
const int WinDrawPacket::colmFive = 50;

//Row constants
const int WinDrawPacket::rowOne = 100;
const int WinDrawPacket::rowTwo = 200;
const int WinDrawPacket::rowThree = 300;
const int WinDrawPacket::rowFour = 400;
const int WinDrawPacket::rowFive = 500;

//Piece constants
const int WinDrawPacket::O = 1;
const int WinDrawPacket::X = 2;

//Other constants
const int WinDrawPacket::nullConstant = -1;

//Error States
const int WinDrawPacket::fatalError = -2;
const char WinDrawPacket::charFatalError = '!';

const char WinDrawPacket::delimiter = '#';

WinDrawPacket::WinDrawPacket()
{
	//Fill all variables with an initial value
	winDraw = fatalError;
	playerPiece = fatalError;
	winType = fatalError;
	diagonalType = fatalError;
	rowAcross = fatalError;
	columnDown = fatalError;

	readable = false;
}

WinDrawPacket::WinDrawPacket(const WinDrawPacket& packet)
{
	(*this).winDraw = packet.winDraw;
	(*this).playerPiece = packet.playerPiece;
	(*this).winType = packet.winType;
	(*this).diagonalType = packet.diagonalType;
	(*this).rowAcross = packet.rowAcross;
	(*this).columnDown = packet.columnDown;
	(*this).readable = packet.readable;
}

WinDrawPacket& WinDrawPacket::operator=(const WinDrawPacket& packet)
{
	winDraw = packet.winDraw;
	playerPiece = packet.playerPiece;
	winType = packet.winType;
	diagonalType = packet.diagonalType;
	rowAcross = packet.rowAcross;
	columnDown = packet.columnDown;
	readable = packet.readable;

	return *this;
}

WinDrawPacket::~WinDrawPacket()
{}

void WinDrawPacket::CreatePacket(string prePacket)
{
	stringstream ssConverter;
	int tempNum;
	int poundCount = 0;

	//Prepare stringstream for processing
	ssConverter.clear();

	//Make readable true so that the game object can read the data
	readable = true;

	for(unsigned int i = 0; i < prePacket.size(); i++)
	{
		ssConverter<<prePacket[i];
		ssConverter>>tempNum;
		ssConverter.clear();
		if((tempNum == noWinDraw || tempNum == draw) && poundCount == 0)
		{
			if(tempNum == noWinDraw)
			{
				winDraw = noWinDraw;
			}
			else
			{
				winDraw = draw;
			}

			playerPiece = nullConstant;
			winType = nullConstant;
			diagonalType = nullConstant;
			rowAcross = nullConstant;
			columnDown = nullConstant;
		}
		else if(tempNum == win && poundCount == 0)
		{
			winDraw = win;
		}
		else if(tempNum == (int)delimiter)
		{
			poundCount++;
		}

		//Check for win, if no win exit the loop
		if(winDraw != win)
		{
			break;
		}
		else
		{
			if(i > 2)
			{
				switch(poundCount)
				{
				case 1:
					if(tempNum == nullConstant)
					{
						playerPiece = nullConstant;
					}
					else if(tempNum == O)
					{
						playerPiece = O;
					}
					else if(tempNum == X)
					{
						playerPiece = X;
					}
					else
					{
						playerPiece = fatalError;
					}
					break;
				case 2:
					if(tempNum == nullConstant)
					{
						winType = nullConstant;
					}
					else if(tempNum == across)
					{
						winType = across;
					}
					else if(tempNum == down)
					{
						winType = down;
					}
					else if(tempNum == diagonal)
					{
						winType = diagonal;
					}
					else
					{
						playerPiece = fatalError;
					}
					break;
				}
			}
			else if(winType == diagonal && poundCount == 3 && i > 5)
			{
				if(tempNum == diagonalLeft)
				{
					diagonalType = diagonalLeft;
				}
				else if(tempNum == diagonalRight)
				{
					diagonalType = diagonalRight;
				}
				else
				{
					diagonalType = fatalError;
				}

				//Since it's diagonal fill in the rest of the packet and break out of the loop
				rowAcross = nullConstant;
				columnDown = nullConstant;
				break;
			}
			else if(winType == across && poundCount == 4 && i > 7)
			{
				tempNum *= 100;
				switch(tempNum)
				{
				case rowOne:
					rowAcross = rowOne;
					break;
				case rowTwo:
					rowAcross = rowTwo;
					break;
				case rowThree:
					rowAcross = rowThree;
					break;
				case rowFour:
					rowAcross = rowFour;
					break;
				case rowFive:
					rowAcross = rowFive;
					break;
				default:
					rowAcross = fatalError;
				}

				//Fill in the rest of the packet and break out of loop
				diagonalType = nullConstant;
				columnDown = nullConstant;
				break;
			}
			else if(winType == down && poundCount == 5 && i > 9)
			{
				tempNum *= 10;
				switch(tempNum)
				{
				case colmOne:
					columnDown = colmOne;
					break;
				case colmTwo:
					columnDown = colmTwo;
					break;
				case colmThree:
					columnDown = colmThree;
					break;
				case colmFour:
					columnDown = colmFour;
					break;
				case colmFive:
					columnDown = colmFive;
					break;
				default:
					columnDown = fatalError;
				}

				//Fill in the rest of the packet and break out of loop
				diagonalType = nullConstant;
				rowAcross = nullConstant;
				break;
			}
		}
	}
}

//Get functions with readable check
//Only work when readable is set to true
int WinDrawPacket::GetWinDraw()
{
	if(readable == true)
	{
		return winDraw;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetPlayerPiece()
{
	if(readable == true)
	{
		return playerPiece;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetWinType()
{
	if(readable == true)
	{
		return winType;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetDiagType()
{
	if(readable == true)
	{
		return diagonalType;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetRow()
{
	if(readable == true)
	{
		return rowAcross;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetColumn()
{
	if(readable == true)
	{
		return columnDown;
	}
	else
	{
		return fatalError;
	}
}

//Get functions for constants with readable check
//Only work when readable is set to false
int WinDrawPacket::GetConstNoWinDraw()
{
	if(readable == false)
	{
		return noWinDraw;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstWin()
{
	if(readable == false)
	{
		return win;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstDraw()
{
	if(readable == false)
	{
		return draw;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstAcross()
{
	if(readable == false)
	{
		return across;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstDown()
{
	if(readable == false)
	{
		return down;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstDiagonal()
{
	if(readable == false)
	{
		return diagonal;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstDiagonalLeft()
{
	if(readable == false)
	{
		return diagonalLeft;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstDiagonalRight()
{
	if(readable == false)
	{
		return diagonalRight;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstColumnOne()
{
	if(readable == false)
	{
		return colmOne;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstColumnTwo()
{
	if(readable == false)
	{
		return colmTwo;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstColumnThree()
{
	if(readable == false)
	{
		return colmThree;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstColumnFour()
{
	if(readable == false)
	{
		return colmFour;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstColumnFive()
{
	if(readable == false)
	{
		return colmFive;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstRowOne()
{
	if(readable == false)
	{
		return rowOne;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstRowTwo()
{
	if(readable == false)
	{
		return rowTwo;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstRowThree()
{
	if(readable == false)
	{
		return rowThree;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstRowFour()
{
	if(readable == false)
	{
		return rowFour;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstRowFive()
{
	if(readable == false)
	{
		return rowFive;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstNullConstant()
{
	if(readable == false)
	{
		return nullConstant;
	}
	else
	{
		return fatalError;
	}
}

int WinDrawPacket::GetConstFatalError()
{
	int tempFatalError;
	if(readable == false)
	{
		tempFatalError = fatalError;
	}
	else
	{
		tempFatalError = 666;
	}

	return tempFatalError;
}

char WinDrawPacket::GetConstCharFatalError()
{
	char tempFatalError;
	if(readable == false)
	{
		tempFatalError = charFatalError;
	}
	else
	{
		tempFatalError = '-';
	}

	return tempFatalError;
}
	
char WinDrawPacket::GetConstDelimiter()
{
	if(readable == false)
	{
		return delimiter;
	}
	else
	{
		return charFatalError;
	}
}