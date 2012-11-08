#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "WinDrawPacket.h"
#include "ScreenColors.h"

using namespace std;

//TODO:
//Make all get functions const correct
//Needs to be done as soon as possible
class Player
{
private:
	ScreenColors textColor;
	int id;
	string name;
	int score;
	int playerPiece;
	string move;	//Stores the move of the player temporarly
	bool madeMove;
	int boundsLimit;
	static int numOfPlayers;
	static int otherPlayerPiece;	//Becomes a 1 or 2 depending on the first player, when instaniating the second player the construstor
									//only has to look at this varaible to know what the other player is and then assigns the other piece accordingly
	void AssignPlayerPiece();  //Assign either an X or an O to a player
	int PieceGen();	//Used to generate the first players piece, X or O. Generates numbers 1 or 2 randomly and is sent back to calling function
	static const int answerSize;
	bool CheckPlayerMove();

public:
	Player();
	~Player();
	void DisplayName();
	void DisplayScore();
	void UpdateScore();
	bool MakeMove();
	void ResetPlayer();
	void ResetPlayerPiece(); //Call this function before ResetPlayer is called. Very Important!!!
	
	//These return the id and the number representing the playerPiece respectively
	int GetID() { return id; }
	int GetPieceNum() { return playerPiece; }

	//Get functions for name and score -- Only used when just the name or score is needed without all the other dialoge
	string GetName() { return name; }
	int GetScore() { return score; }

	//Set function for the boundsLimit
	void SetBoundsLimit(int b) { boundsLimit = b; }
	
	//Get/Set functions for move
	string GetMove() { return move; }
	void SetMove(string m) { move = m; }
	
	//Check/Set functions for madeMove
	bool CheckMadeMove() { return madeMove; }
	void SetMadeMove(bool mm) { madeMove = mm; }

	//Get function for text color
	int GetTextColor() const;
};