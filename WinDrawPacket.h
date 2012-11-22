#pragma once
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <conio.h>
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;

class WinDrawPacket
{
public:
	WinDrawPacket(const ConstList &cList);
	
	//This used to create the packet that will get sent from the board object to the game object
	void CreatePacket(const int gameOutcome, const int winningPiece, const int winLocation, const int winDiagonalLocation, const int winRowLocation, const int winColumnLocation);

	//----Const notes----
	//Adding const before a function makes the compiler catch assignment errors in things like if statements
	//Adding const after the function is basically guaranteeing the compiler that it is a inspector function and not a mutator function
	//Get variables
	const int GetWinDraw() const;
	const int GetPlayerPiece() const;
	const int GetWinType() const;
	const int GetDiagType() const;
	const int GetRow() const;
	const int GetColumn() const;

//----Constants List Variables----//
private:
	static const string noWinDrawState;
	static const string winState;
	static const string drawState;
	static const string acrossWinType;
	static const string downWinType;
	static const string diagonalWinType;
	static const string diagonalLeftSubType;
	static const string diagonalRightSubType;
	static const string noPlayerPiece;
	static const string oPlayerPiece;
	static const string xPlayerPiece;
	static const string columnOne;
	static const string columnTwo;
	static const string columnThree;
	static const string columnFour;
	static const string columnFive;
	static const string rowOne;
	static const string rowTwo;
	static const string rowThree;
	static const string rowFour;
	static const string rowFive;
	static const string nullConstant;
	static const string fatalError;

//Local constants
private:
	//Local Error String -- Unique to the WinDrawPacket object
	static const string packetUnreadable;

//Container Variables
private:
	ConstList constantsList;
	ErrorTypes err;

//Regular variables
private:
	int winDraw_;		//Change this to gameState instead of winDraw, it's much more descriptive.
						//Make these changes code wide. Any references to winDraw or anything like it are to be changed to gameState.
	int playerPiece_;
	int winType_;
	int diagonalType_;
	int rowAcross_;
	int columnDown_;
	bool packetCreated_;	//This makes the packet unreadable until CreatePacket has been run

//Private Functions
private:
	int GetConstantFromList(string request);
};