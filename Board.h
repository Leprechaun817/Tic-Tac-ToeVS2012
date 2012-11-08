#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include "WinDrawPacket.h"

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;

class Board
{
private:
	//The characters that make up the board
	static const string horizontalLine1;
	static const char horizontalLine2;
	static const char verticalLine;
	static const char space;
	static const char xPiece;
	static const char oPiece;

	//Character measurements of board
	static const int sizeOfSquareAcross;
	static const int sizeOfSquareDown;
	static const int pieceSpacing;
	
	//The integers that represent the characters on the board
	static const int noPiece;
	static const int X;
	static const int O;
	
	//The integers that represent the total number of squares on the board
	//There are 3 possible combinations
	static const int A;
	static const int B;
	static const int C;

	HANDLE hConsoleWindow;	//This will be used when changing the text colors
	int multiplier; //total number of spaces in one line going across or down. Also acts as the height and width for the board, as well as the winning number
	int numOfSpaces; //calculated during the making of the board, this number is used when creating the vector that will
					 //keep track of which spaces are filled
	vector<int> spaceList;	//The vector spaceList keeps track of the positions on the board and whether they have been filled with a X,O or have nothing there.
	WinDrawPacket gameConstants;	//Used when making the prePacket. Setup only for that express purpose!
	void SetupBoard();		//Asks user for number of spaces on board, figures out the multiplier
	void InitiateBoard();	//Function lays out board in terms of the numbers used to keep track of each spot and stores them in the spaceList vector.
	char XorO(int num, bool special);	//Figure out whether the space is supposed to contain an X or O or nothing and returns the proper character
	//Creates the string that will be sent to the packet object for processing
	string CreatePrePacket(int gameOutcome, int piece, int winLocation, int diagonalLocation, int rowLocation, int columnLocation);
	void DisplayPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing, int pieceColor = 0);
	void DisplayWinningPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing, int playerColor);
	void DisplayNonWinningPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing);
	void ResetConsoleColor();

public:
	Board();	//Constructor, Asks user for size of board and then calls InitiateBoard and DisplayBoard to setup the playing board and displays the empty board.
	~Board();
	//DisplayBoard - Takes the spaceList vector and using that makes a new display of the board accordingly. Kind of like the Blit function in a graphical sense.
	//All graphical or informative data to be displayed on screen is processed by this function.
	void DisplayBoard(int numRounds, int numTies, string p1Name, int p1Score, int p1Piece, int p1PieceColor, string p2Name, int p2Score, int p2Piece, int p2PieceColor);
	//This display function is only used when there was a win
	//Displays the winning move on the board
	void DisplayWinningBoard(bool playerOneWin, bool playerTwoWin, int type, int diagonalLocation, int acrossDownLocation, int playerOneColor, int playerTwoColor, int playerOnePiece, int playerTwoPiece);
	void ResetBoard();  //Resets board and sets it up for another play-through
	int BoardRefresh(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus);
	WDPacketPtr FindWinDraw();

	//Get functions
	int GetMultiplier() const;
};