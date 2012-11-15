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
	bool win;
	int boundsLimit;
	bool playerInitialized;
	ConstList constantsList;
	static int numOfPlayers;
	static const int answerSize;
	bool resetPlayerFunctionCalled;
	void AssignPlayerPiece();  //Assign either an X or an O to a player
	int PieceGen();	//Used to generate the first players piece, X or O. Generates numbers 1 or 2 randomly and is sent back to calling function
	bool CheckMoveFormat(string choice);
	int ReformatMove(string choice);

public:
	Player();
	~Player();
	//DisplayName and DisplayScore may be removed at some point. I don't think they will be needed
	void DisplayName();
	void DisplayScore();
	void UpdateScore();
	int MakeMove();
	void ResetPlayer(int boundsLimit);
	void ResetPlayerPiece(); //Call this function before ResetPlayer is called. Very Important!!!
	void InitializePlayer(int boundsLimit, const ConstList &cList);
	const void SetPlayerTextColor() const;
	//These return the id and the number representing the playerPiece respectively
	const int GetID() const;
	const int GetPiece() const;

	//Get functions for name and score -- Only used when just the name or score is needed without all the other dialoge
	const string GetName() const;
	const int GetScore() const;

	//Get/Set functions for move
	const int GetMove() const;
	void ResetMove();

	//Only sets win to true
	void SetPlayerWon();

	//Get for win variable
	const bool DidPlayerWin() const;
	
	//Checks if player has made their move or not returns whatever that value is
	//and then toggles madeMove to the opposite of what it was.
	//So if it was true after running this it will be false and visa versa...
	bool HasPlayerMadeMove();
};