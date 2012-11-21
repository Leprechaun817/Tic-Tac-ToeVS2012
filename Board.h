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

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;
typedef vector<int> IntList;
typedef vector<int>::iterator IntIter;
typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;
typedef map<const int, char> PieceList;
typedef map<const int, char>::const_iterator PieceListIters_C;
typedef map<const int, string> IntStringList;
typedef map<const int, string>::const_iterator ISListIter_C;

//TODO:
//-Use typedefs for spacelist and piecePlacement
//-Take the building of the piecePlacement out of the board display functions and put it into its own function thats called
// when the board is updated.
// 
class Board
{
private:
	//----String constants----//
	//For use with the constantsList
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
	
	//The characters that make up the board
	static const string horizontalLine1;
	static const char horizontalLine2;
	static const char verticalLine;
	
	//Character measurements of board
	static const int sizeOfSquareAcross;
	static const int sizeOfSquareDown;
	static const int pieceSpacing;
	
	//The integers that represent the total number of squares on the board
	//There are 3 possible combinations
	static const int A;
	static const int B;
	static const int C;

	//Board related error codes
	static const int error1;
	static const int error2;
	static const int error3;

	HANDLE hConsoleWindow_;	//This will be used when changing the text colors
	int multiplier_; //total number of spaces in one line going across or down. Also acts as the height and width for the board, as well as the winning number
	int numOfSpaces_; //calculated during the making of the board, this number is used when creating the vector that will
					 //keep track of which spaces are filled
	int totalXsOnBoard_;
	int totalOsOnBoard_;
	IntList spaceList;	//The vector spaceList keeps track of the positions on the board and whether they have been filled with a X,O or have nothing there.
	IntList piecePlacement;  //Keeps track of just the piece types, their location on the board is figured out by their location within the vector
	ConstList constantsList;
	PieceList numToCharConversionList;
	IntStringList errorMsgList;
	bool boardFatalError_;
	void InitiateBoard();	//Function lays out board in terms of the numbers used to keep track of each spot and stores them in the spaceList vector.
	char XorO(int num);	//Figure out whether the space is supposed to contain an X or O or nothing and returns the proper character
	void DisplayPiece(int &squareCount, int &temp2, int pieceSpacing);
	bool ProcessSpaceList(int location, int playerPiece);
	void ProcessPiecePlacementList();
	void ResetConsoleColor();
	bool CheckMoveLocation(int location);
	int GetConstantFromList(string request);
	char GetConstantFromList(int request);

public:
	Board();	//Constructor, Asks user for size of board and then calls InitiateBoard and DisplayBoard to setup the playing board and displays the empty board.
	~Board();
	void SetupBoard(const ConstList &cList);		//Asks user for number of spaces on board, figures out the multiplier
	//DisplayBoard - Takes the spaceList vector and using that makes a new display of the board accordingly. Kind of like the Blit function in a graphical sense.
	//All graphical or informative data to be displayed on screen is processed by this function.
	void DisplayBoard(int numRounds, int numTies, const Player &pOne, const Player &pTwo);
	//This display function is only used when there was a win
	//Displays the winning move on the board
	void DisplayWinningBoard(int type, int diagonalLocation, int acrossDownLocation, const Player &pOne, const Player &pTwo);
	void ResetBoard();  //Resets board and sets it up for another play-through
	bool UpdateBoard(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus);
	WDPacketPtr FindWinDraw();

	//Get functions
	const int GetMultiplier() const;
	const bool GetFatalError() const;
	const int GetTotalNumOfPiecesOnBoard() const;
};