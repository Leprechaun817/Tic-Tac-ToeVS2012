#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <sstream>
#include "WinDrawPacket.h"
#include "ScreenColors.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef map<const string, int> ConstList;
typedef map<const string, int>::const_iterator ConstListIters_C;

class Player
{
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

//Protected Functions
//Made these protected in preperation for the computer player (AI player)
//Computer player class will derive from this one
//Other changes coming soon...
protected:
	void AssignPlayerPiece();  //Assign either an X or an O to a player
	int PieceGen();	//Used to generate the first players piece, X or O. Generates numbers 1 or 2 randomly and is sent back to calling function
	bool CheckMoveFormat(string choice);
	int ReformatMove(string choice);

//Constants
private:
	static const string noPlayerPiece;
	static const string oPlayerPiece;
	static const string xPlayerPiece;
	static const string varError;

//Container Variables
private:
	ScreenColors textColor;
	ConstList constantsList;
	ErrorTypes err;

//Regular Variables
private:
	int id_;
	string name_;
	int score_;
	int playerPiece_;
	static int otherPlayerPiece_;
	int playerTurnOrder_;
	int move_;	//Stores the move of the player temporarly
	bool madeMove_;
	bool win_;
	int boundsLimit_;
	bool playerInitialized_;
	static int numOfPlayers_;
	static const int answerSize;
	bool resetPlayerFunctionCalled_;
};