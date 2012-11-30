#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <memory>
#include <map>
#include <array>
#include "Board.h"
#include "Player.h"
#include "WinDrawPacket.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;
typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;

class Game
{
public:
	Game();
	void StartGame();
	bool GameLoop();		//All the different states that the game could be in are listed as
	bool EndGame();			//functions here. These are called as is necessary through the game loop
	void ResetGame();		//in the main.
	void DisplayFinalStats();
	void DisplayLastRoundStats();

//----Message Constants----
private:
	//Win/Draw Messages
	static const string gameDrawMessage, playerOneWinMessage, playerTwoWinMessage;
	//Other Messages
	static const string anyKey;

//----Constants Strings----
private:
	//These are used while creating the constantsList
	static const string noWinDrawState, winState, drawState;
	static const string acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType;
	static const string noPlayerPiece, oPlayerPiece, xPlayerPiece;
	static const string columnOne, columnTwo, columnThree, columnFour, columnFive;
	static const string rowOne, rowTwo, rowThree, rowFour, rowFive;
	static const string nullConstant;
	static const string fatalError;

//Object Variables
private:
	Player playerOne, playerTwo;
	Board board;

//Container Variables
private:
	ConstList constantsList;
	ErrorTypes err;

//Regular Variables
private:
	bool firstPlay_;
	int roundsPlayed_;  //Keeps track of total number of games played
	int boundsLimit_;
	int gameDraws_;	//Used to keep track of how many times all of the rounds played closed with a draw
	int playOrder_;	//Dictates which player goes first
	int turnCounter_; //This gets incremented by 1 everytime both players have taken their turns. Resets after each new game... 

//Private Functions
private:
	bool GetPlayerMove(int order);
	bool ProcessPacket(WDPacketPtr packet);
	int GetConstantFromList(string request);
	void DecidePlayOrder();
};