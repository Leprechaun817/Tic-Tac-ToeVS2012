#include "WinDrawPacket.h"

//----Constants List Variables----//
const string WinDrawPacket::noWinDrawState = "noWinDrawState";
const string WinDrawPacket::winState = "winState";
const string WinDrawPacket::drawState = "drawState";
const string WinDrawPacket::acrossWinType = "acrossWinType";
const string WinDrawPacket::downWinType = "downWinType";
const string WinDrawPacket::diagonalWinType = "diagonalWinType";
const string WinDrawPacket::diagonalLeftSubType = "diagonalLeftSubType";
const string WinDrawPacket::diagonalRightSubType = "diagonalRightSubType";
const string WinDrawPacket::noPlayerPiece = "noPlayerPiece";
const string WinDrawPacket::oPlayerPiece = "oPlayerPiece";
const string WinDrawPacket::xPlayerPiece = "xPlayerPiece";
const string WinDrawPacket::columnOne = "columnOne";
const string WinDrawPacket::columnTwo = "columnTwo";
const string WinDrawPacket::columnThree = "columnThree";
const string WinDrawPacket::columnFour = "columnFour";
const string WinDrawPacket::columnFive = "columnFive";
const string WinDrawPacket::rowOne = "rowOne";
const string WinDrawPacket::rowTwo = "rowTwo";
const string WinDrawPacket::rowThree = "rowThree";
const string WinDrawPacket::rowFour = "rowFour";
const string WinDrawPacket::rowFive = "rowFive";
const string WinDrawPacket::nullConstant = "nullConstant";
const string WinDrawPacket::fatalError = "fatalError";

const string WinDrawPacket::packetUnreadable = "Packet has not been created yet...\nPlease run CreatePacket before sending the WinDrawPacket\nback to the Game object\n"; 

WinDrawPacket::WinDrawPacket(const ConstList &cList)
{
	(*this).constantsList = cList;
	
	ConstListIters_C cListIter;
	cListIter = cList.find(fatalError);
	int fatalErrorConst = cListIter->second;
	
	//Fill all variables with the initial value above
	winDraw = fatalErrorConst;
	playerPiece = fatalErrorConst;
	winType = fatalErrorConst;
	diagonalType = fatalErrorConst;
	rowAcross = fatalErrorConst;
	columnDown = fatalErrorConst;

	packetCreated = false;
}

WinDrawPacket::WinDrawPacket(const WinDrawPacket& packet)
{
	(*this).winDraw = packet.winDraw;
	(*this).playerPiece = packet.playerPiece;
	(*this).winType = packet.winType;
	(*this).diagonalType = packet.diagonalType;
	(*this).rowAcross = packet.rowAcross;
	(*this).columnDown = packet.columnDown;
	(*this).packetCreated = packet.packetCreated;
	(*this).constantsList = packet.constantsList;
}

WinDrawPacket& WinDrawPacket::operator=(const WinDrawPacket& packet)
{
	(*this).winDraw = packet.winDraw;
	(*this).playerPiece = packet.playerPiece;
	(*this).winType = packet.winType;
	(*this).diagonalType = packet.diagonalType;
	(*this).rowAcross = packet.rowAcross;
	(*this).columnDown = packet.columnDown;
	(*this).packetCreated = packet.packetCreated;
	(*this).constantsList = packet.constantsList;

	return *this;
}

void WinDrawPacket::CreatePacket(int gameOutcome, int piece, int winLocation, int diagonalLocation, int rowLocation, int columnLocation)
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

const int WinDrawPacket::GetWinDraw() const
{
	if(packetCreated == true)
	{
		return winDraw;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int WinDrawPacket::GetPlayerPiece() const
{
	if(packetCreated == true)
	{
		return playerPiece;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int WinDrawPacket::GetWinType() const
{
	if(packetCreated == true)
	{
		return winType;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int WinDrawPacket::GetDiagType() const
{
	if(packetCreated == true)
	{
		return diagonalType;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int WinDrawPacket::GetRow() const
{
	if(packetCreated == true)
	{
		return rowAcross;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int WinDrawPacket::GetColumn() const
{
	if(packetCreated == true)
	{
		return columnDown;
	}
	else
	{
		cout<<packetUnreadable;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}
