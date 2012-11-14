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

void WinDrawPacket::CreatePacket(const int gameOutcome, const int winningPiece, const int winLocation, const int winDiagonalLocation, const int winRowLocation, const int winColumnLocation)
{
	packetCreated = true;

	//Error values
	const int t_nullConstant = GetConstantFromList(nullConstant);
	const int t_fatalError = GetConstantFromList(nullConstant);

	//Other values needed for testing
	const int t_noWinDrawState = GetConstantFromList(noWinDrawState);
	const int t_drawState = GetConstantFromList(drawState);
	const int t_winState = GetConstantFromList(winState);

	if((gameOutcome == t_noWinDrawState) || (gameOutcome == t_drawState))
	{
		winDraw = gameOutcome;
		//Adding nullConstants here so if parser code in ProcessPacket goes to far it will pop up with a minor error
		playerPiece = t_nullConstant;
		winType = t_nullConstant;
		diagonalType = t_nullConstant;
		rowAcross = t_nullConstant;
		columnDown = t_nullConstant;
	}
	else if(gameOutcome == t_winState)
	{
		winDraw = gameOutcome;
		playerPiece = winningPiece;
		winType = winLocation;
		diagonalType = winDiagonalLocation;
		rowAcross = winRowLocation;
		columnDown = winColumnLocation;
	}
	else if(gameOutcome == t_nullConstant)
	{
		//Minor error, list all variables with minor errors regardless of what they were before
		winDraw = t_nullConstant;
		playerPiece = t_nullConstant;
		winType = t_nullConstant;
		diagonalType = t_nullConstant;
		rowAcross = t_nullConstant;
		columnDown = t_nullConstant;
	}
	else if(gameOutcome == t_fatalError)
	{
		//Major Error, list all variables with major errors regardless of what they were before
		winDraw = t_fatalError;
		playerPiece = t_fatalError;
		winType = t_fatalError;
		diagonalType = t_fatalError;
		rowAcross = t_fatalError;
		columnDown = t_fatalError;
	}
	else
	{
		//If gameOutcome has an unknown value treat as major error//
		//winDraw and all the other variables will equal whatever the weird number was in gameOutcome
		winDraw = gameOutcome;
		playerPiece = gameOutcome;
		winType = gameOutcome;
		diagonalType = gameOutcome;
		rowAcross = gameOutcome;
		columnDown = gameOutcome;
	}

}

int WinDrawPacket::GetConstantFromList(string request)
{
	ConstListIters_C constListIter;
	constListIter = constantsList.find(request);
	int t_request = constListIter->second;

	return t_request;
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
