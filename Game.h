#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <array>
#include "Board.h"
#include "Player.h"
#include "WinDrawPacket.h"

using namespace std;

typedef auto_ptr<WinDrawPacket> WDPacketPtr;
typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;

//TODO:
//Create list of constants that can be used throughout the game.
//It'll just get sent to where it is needed
class Game
{
public:
	Game();
	void StartGame();
	bool GameLoop();		//All the different states that the game could be in are listed as
	bool EndGame();			//functions here. These are called as is necessary through the game loop
	void ResetGame();		//in the main.

	const bool HasGameHadFatalError() const;
	const bool HasWinOccurred() const;

//----Message Constants----
private:
	//Win/Draw Messages
	static const string gameDrawMessage;
	static const string playerOneWinMessage;
	static const string playerTwoWinMessage;
	//WinDrawPacket Related Messages
	static const string gameStateErrorMessage;
	static const string playerPieceErrorMessage;
	static const string winTypeErrorMessage;
	static const string diagonalTypeErrorMessage;
	static const string rowAcrossErrorMessage;
	static const string columnDownErrorMessage;
	//Main Error Messages
	static const string fatalErrorMessage;
	static const string minorErrorMessage;
	static const string unknownErrorMessage;
	//Other Messages
	static const string anyKey;

//----Constants Strings----
private:
	//These are used while creating the constantsList
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

//Object Variables
private:
	Player playerOne;
	Player playerTwo;
	Board board;

//Container Variables
private:
	ConstList constantsList;

//Regular Variables
private:
	bool firstPlay_;
	int roundsPlayed_;  //Keeps track of total number of games played
	int boundsLimit_;
	int gameDraws_;	//Used to keep track of how many times all of the rounds played closed with a draw
	int playOrder_;	//Dictates which player goes first
	int turnCounter_; //This gets incremented by 1 everytime both players have taken their turns. Resets after each new game... 
	bool gameFatalError_;

//Private Functions
private:
	bool GetPlayerMove(int order);
	bool ProcessPacket(WDPacketPtr packet);
	int GetConstantFromList(string request);
	void DecidePlayOrder();
};