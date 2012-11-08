#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include "Board.h"
#include "Player.h"
#include "WinDrawPacket.h"

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;

class Game
{
private:
	//----Message Constants----
	//Win/Draw Messages
	static const string gameDrawMessage;
	static const string playerOneWinMessage;
	static const string playerTwoWinMessage;
	//WinDrawPacket Related Messages
	static const string winDrawErrorMessage;
	static const string playerPieceErrorMessage;
	static const string winTypeErrorMessage;
	static const string diagonalTypeErrorMessage;
	static const string rowAcrossErrorMessage;
	static const string columnDownErrorMessage;
	//Main Error Messages
	static const string fatalErrorMessage;
	static const string minorErrorMessage;
	//Other Messages
	static const string anyKey;

	//Normal Variables
	Player playerOne;
	Player playerTwo;
	Board board;
	bool firstPlay;
	int roundsPlayed;  //Keeps track of total number of games played
	int boundsLimit;
	int gameDraws;	//Used to keep track of how many times the game closed with a draw
	int playOrder;	//Dictates which player goes first
	int turnCounter; //This gets incremented by 1 everytime both players have taken their turns. Resets after each new game... 
	WinDrawPacket gameConstants;
	bool GetPlayerMoves();
	int FormatMove(string move);
	bool PlayerOneMove();
	bool PlayerTwoMove();
	bool CheckAndUpdateBoard(int move);
	bool ProcessPacket(WDPacketPtr packet);
	
public:
	Game();
	void StartGame();
	bool GameLoop();		//All the different states that the game could be in are listed as
	bool EndGame();			//functions here. These are called as is necessary through the game loop
	void ResetGame();		//in the main.
};