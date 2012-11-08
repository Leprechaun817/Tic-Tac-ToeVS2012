#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

class WinDrawPacket
{
private:
	//--Constants--
	//Win/Draw constants
	static const int noWinDraw;
	static const int win;
	static const int draw;

	//Board Win Possibilities
	static const int across;
	static const int down;
	static const int diagonal;

	//Diagonal winning possibilities
	static const int diagonalLeft;
	static const int diagonalRight;

	//Piece constants
	static const int O;
	static const int X;

	//Column constants
	static const int colmOne;
	static const int colmTwo;
	static const int colmThree;
	static const int colmFour;
	static const int colmFive;

	//Row constants
	static const int rowOne;
	static const int rowTwo;
	static const int rowThree;
	static const int rowFour;
	static const int rowFive;

	//Other constants
	static const int nullConstant;

	//Error States
	static const int fatalError;
	static const char charFatalError;

	static const char delimiter;	//Used when processing prepacket string

	//Regular variables
	int winDraw;
	int playerPiece;
	int winType;
	int diagonalType;
	int rowAcross;
	int columnDown;

	bool readable;	//This makes the packet unreadable until CreatePacket has been run
	

public:
	WinDrawPacket();
	WinDrawPacket(const WinDrawPacket& packet);
	
	WinDrawPacket& operator=(const WinDrawPacket& packet);

	//This used to create the packet that will get sent from the board object to the game object
	void CreatePacket(string prePacket);

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

	//Get functions for the constants
	//Will be used in board object mostly
	//Will only output the proper values if readable is set to false.
	//I did it this way to insure that the gameConstants object in the Board object only gets used
	//to output the necessary constants to build the prePacket.
	const int GetConstNoWinDraw() const;
	const int GetConstWin() const;
	const int GetConstDraw() const;
	const int GetConstAcross() const;
	const int GetConstDown() const;
	const int GetConstDiagonal() const;
	const int GetConstDiagonalLeft() const;
	const int GetConstDiagonalRight() const;
	const int GetConstColumnOne() const;
	const int GetConstColumnTwo() const;
	const int GetConstColumnThree() const;
	const int GetConstColumnFour() const;
	const int GetConstColumnFive() const;
	const int GetConstRowOne() const;
	const int GetConstRowTwo() const;
	const int GetConstRowThree() const;
	const int GetConstRowFour() const;
	const int GetConstRowFive() const;
	const int GetConstNullConstant() const;
	const int GetConstFatalError() const;
	const char GetConstCharFatalError() const;
	const char GetConstDelimiter() const;
};