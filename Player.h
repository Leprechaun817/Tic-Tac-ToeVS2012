#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <sstream>
#include "WinDrawPacket.h"
#include "ScreenColors.h"

using namespace std;

typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;

class Player
{
private:
	//Constants
	static const string noPlayerPiece;
	static const string oPlayerPiece;
	static const string xPlayerPiece;
	
	//Regular Variables
	ScreenColors textColor;
	int id;
	string name;
	int score;
	int playerPiece;
	static int otherPlayerPiece;
	int playerTurnOrder;
	int move;	//Stores the move of the player temporarly
	bool madeMove;
	int boundsLimit;
	bool playerInitialized;
	WinDrawPacket gameConstants;
	ConstList constantsList;
	static int numOfPlayers;
	bool resetPlayerFunctionCalled;
	void AssignPlayerPiece();  //Assign either an X or an O to a player
	void DecidePlayerTurnOrder();	//Figures out whether the player goes second or third
	int PieceGen();	//Used to generate the first players piece, X or O. Generates numbers 1 or 2 randomly and is sent back to calling function
	static const int answerSize;
	bool CheckPlayerMove(string choice);

public:
	Player(const ConstList &cList);
	~Player();
	void DisplayName();
	void DisplayScore();
	void UpdateScore();
	bool MakeMove();
	void ResetPlayer(int boundsLimit);
	void ResetPlayerPiece(); //Call this function before ResetPlayer is called. Very Important!!!
	void InitializePlayer(int boundsLimit);
	void ChangeToPlayerTextColor();
	//These return the id and the number representing the playerPiece respectively
	int GetID() { return id; }
	int GetPieceNum() { return playerPiece; }

	//Get functions for name and score -- Only used when just the name or score is needed without all the other dialoge
	string GetName() { return name; }
	int GetScore() { return score; }

	//Get/Set functions for move
	int GetMove() { return move; }
	void ResetMove();
	
	//Check/Set functions for madeMove
	bool CheckMadeMove() { return madeMove; }
};