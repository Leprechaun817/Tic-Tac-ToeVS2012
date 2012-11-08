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

void WinDrawPacket::CreatePacket(string prePacket)
{
	const char Xs = 'X';
	const char Os = 'O';
	const char negative = '-';

	stringstream ssConverter;
	int poundCount = 0;
	int tempNum;
	char tempChar;
	//Prepare stringstream for processing
	ssConverter.clear();

	//Make readable true so that the game object can read the data
	readable = true;

	for(unsigned int i = 0; i < prePacket.size(); i++)
	{
		tempNum = NULL;
		tempChar = NULL;
		ssConverter<<prePacket[i];
		
		if(ssConverter.peek() == delimiter || ssConverter.peek() == Xs || ssConverter.peek() == Os)
		{
			ssConverter>>tempChar;
			tempNum = (int)tempChar;
		}
		else if(ssConverter.peek() == negative)
		{
			ssConverter.clear();
			ssConverter<<prePacket[(i + 1)];
			ssConverter>>tempNum;
			tempNum *= -1;
			i++;
		}
		else
		{
			ssConverter>>tempNum;
		}
		
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
		else if(tempNum == delimiter)
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
			if((poundCount == 1 || poundCount == 2) && tempNum != delimiter)
			{
				switch(poundCount)
				{
				case 1:
					if(tempNum == nullConstant)
					{
						playerPiece = nullConstant;
					}
					else if(tempNum == Os)
					{
						playerPiece = O;
					}
					else if(tempNum == Xs)
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
				}
			}
			else if(winType == diagonal && poundCount == 3)
			{
				if(tempNum != delimiter)
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
			}
			else if(winType == across && poundCount == 4)
			{
				if(tempNum != delimiter)
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
			}
			else if(winType == down && poundCount == 5)
			{
				if(tempNum != delimiter)
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
}

//Get functions with readable check
//Only work when readable is set to true
int WinDrawPacket::GetWinDraw() const
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

int WinDrawPacket::GetPlayerPiece() const
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

int WinDrawPacket::GetWinType() const
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

int WinDrawPacket::GetDiagType() const
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

int WinDrawPacket::GetRow() const
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

int WinDrawPacket::GetColumn() const
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
int WinDrawPacket::GetConstNoWinDraw() const
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

int WinDrawPacket::GetConstWin() const
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

int WinDrawPacket::GetConstDraw() const
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

int WinDrawPacket::GetConstAcross() const
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

int WinDrawPacket::GetConstDown() const
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

int WinDrawPacket::GetConstDiagonal() const
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

int WinDrawPacket::GetConstDiagonalLeft() const
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

int WinDrawPacket::GetConstDiagonalRight() const
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

int WinDrawPacket::GetConstColumnOne() const
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

int WinDrawPacket::GetConstColumnTwo() const
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

int WinDrawPacket::GetConstColumnThree() const
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

int WinDrawPacket::GetConstColumnFour() const
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

int WinDrawPacket::GetConstColumnFive() const
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

int WinDrawPacket::GetConstRowOne() const
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

int WinDrawPacket::GetConstRowTwo() const
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

int WinDrawPacket::GetConstRowThree() const
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

int WinDrawPacket::GetConstRowFour() const
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

int WinDrawPacket::GetConstRowFive() const
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

int WinDrawPacket::GetConstNullConstant() const
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

int WinDrawPacket::GetConstFatalError() const
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

char WinDrawPacket::GetConstCharFatalError() const
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
	
char WinDrawPacket::GetConstDelimiter() const
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