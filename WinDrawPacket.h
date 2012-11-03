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
	~WinDrawPacket();

	WinDrawPacket& operator=(const WinDrawPacket& packet);

	//This used to create the packet that will get sent from the board object to the game object
	void CreatePacket(string prePacket);

	//Get variables
	int GetWinDraw();
	int GetPlayerPiece();
	int GetWinType();
	int GetDiagType();
	int GetRow();
	int GetColumn();

	//Get functions for the constants
	//Will be used in board object mostly
	//Will only output the proper values if readable is set to false.
	//I did it this way to insure that the gameConstants object in the Board object only gets used
	//to output the necessary constants to build the prePacket.
	int GetConstNoWinDraw();
	int GetConstWin();
	int GetConstDraw();
	int GetConstAcross();
	int GetConstDown();
	int GetConstDiagonal();
	int GetConstDiagonalLeft();
	int GetConstDiagonalRight();
	int GetConstColumnOne();
	int GetConstColumnTwo();
	int GetConstColumnThree();
	int GetConstColumnFour();
	int GetConstColumnFive();
	int GetConstRowOne();
	int GetConstRowTwo();
	int GetConstRowThree();
	int GetConstRowFour();
	int GetConstRowFive();
	int GetConstNullConstant();
	int GetConstFatalError();
	char GetConstCharFatalError();
	char GetConstDelimiter();
};