/********************************************************************************************
*********************************************************************************************
Aaron's Tic-Tac-Toe Clone
A 2 player verison of Tic-Tac-Toe game that's played on a console screen.

Copyright (C) 2012 Aaron Gagern

This file is part of Aaron's Tic-Tac-Toe Clone.

Aaron's Tic-Tac-Toe Clone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Aaron's Tic-Tac-Toe Clone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Aaron's Tic-Tac-Toe Clone.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************************
********************************************************************************************/

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <map>
#include <array>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include "Player.h"
#include "WinDrawPacket.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;
typedef vector<int> IntList;
typedef vector<int>::iterator IntIter;
typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;
typedef map<const int, char> PieceList;
typedef map<const int, char>::const_iterator PieceListIters_C;

class Board
{
public:
	Board();	//Constructor, Asks user for size of board and then calls InitiateBoard and DisplayBoard to setup the playing board and displays the empty board.
	~Board();
	void SetupBoard(const ConstList &cList);		//Asks user for number of spaces on board, figures out the multiplier
	//Displays board during a round
	void DisplayBoard(int numRounds, int numTies, const Player &pOne, const Player &pTwo);
	void DisplaySampleBoard();
	//Displays the winning move on the board
	void DisplayWinningBoard(int type, int diagonalLocation, int acrossDownLocation, const Player &pOne, const Player &pTwo);
	void ResetBoard();  //Resets board and sets it up for another play-through
	bool UpdateBoard(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus);
	WDPacketPtr FindWinDraw();

	//Get functions
	const int GetMultiplier() const;
	const int GetTotalNumOfPiecesOnBoard() const;

//----String constants----//
//For use with the constantsList
private:
	static const string noWinDrawState, winState, drawState;
	static const string acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType;
	static const string noPlayerPiece, oPlayerPiece, xPlayerPiece;
	static const string columnOne, columnTwo, columnThree, columnFour, columnFive;
	static const string rowOne, rowTwo, rowThree, rowFour, rowFive;
	static const string nullConstant;
	static const string fatalError;
	
	//The characters that make up the board
	static const char horizontalLine2 = '-', verticalLine = '|';
	
	//Character measurements of board
	static const int sizeOfSquareAcross = 5, sizeOfSquareDown = 4, pieceSpacing = 5;
	
	//The integers that represent the total number of squares on the board
	//There are 3 possible combinations
	static const int A = 9, B = 16, C = 25;

//Container Variables
private:
	IntList spaceList;	//The vector spaceList keeps track of the positions on the board and whether they have been filled with a X,O or have nothing there.
	IntList piecePlacement;  //Keeps track of just the piece types, their location on the board is figured out by their location within the vector
	ConstList constantsList;
	PieceList numToCharConversionList;
	ErrorTypes err;

//Regular Variables
private:
	HANDLE hConsoleWindow_;	//This will be used when changing the text colors
	int multiplier_; //total number of spaces in one line going across or down. Also acts as the height and width for the board, as well as the winning number
	int numOfSpaces_; //calculated during the making of the board, this number is used when creating the vector that will
					 //keep track of which spaces are filled
	int totalXsOnBoard_;
	int totalOsOnBoard_;
	
//Private Functions
private:
	void InitiateBoard();	//Function lays out board in terms of the numbers used to keep track of each spot and stores them in the spaceList vector.
	char XorO(int num);	//Figure out whether the space is supposed to contain an X or O or nothing and returns the proper character
	void DisplayPiece(int &squareCount, int &temp2, int pieceSpacing, bool pieceHasColor);
	char DisplayWinMessage(int playerID, int playerPiece, int playerTextColor);
	bool ProcessSpaceList(int location, int playerPiece);
	void ProcessPiecePlacementList();
	void ResetConsoleColor();
	bool CheckMoveLocation(int location);
	int GetConstantFromList(string request);
	char GetConstantFromList(int request);
	void SetWinningPlayersTextColor(bool p, const Player &p1, const Player &p2);
};