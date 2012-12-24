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
#include <string>
#include <map>
#include <sstream>
#include "SoundEngine.h"
#include "ScreenColors.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

class Player
{
public:
	Player() throw();
	//DisplayName and DisplayScore may be removed at some point. I don't think they will be needed
	void DisplayName();
	void DisplayScore();
	void UpdateScore();
	bool MakeMove();
	void ResetPlayer(int boundsLimit);
	void ResetPlayerPiece(); //Call this function before ResetPlayer is called. Very Important!!!
	void InitializePlayer(int boundsLimit);
	const void SetPlayerTextColor() const;
	
	//These return the id and the number representing the playerPiece respectively
	const int GetID() const;
	const int GetPiece() const;
	const std::string GetName() const;
	const int GetScore() const;
	const int GetMove() const;
	const int GetPlayerTextColor() const;
	const bool DidPlayerWin() const;

	void ResetMove();

	//Only sets win to true
	void SetPlayerWon();

	bool HasPlayerMadeMove();

//Protected Functions
//Made these protected in preperation for the computer player (AI player)
//Computer player class will derive from this one
//Other changes coming soon...
protected:
	void AssignPlayerPiece();  //Assign either an X or an O to a player
	void PieceGen();	//Used to generate the first players piece, X or O.
	bool CheckMoveFormat(std::string choice);
	int ReformatMove(std::string choice);

//Constants
private:
	static const std::string noPlayerPiece, oPlayerPiece, xPlayerPiece, varError;
	
	//Constants for the sounds
	static const std::string badMoveErrorSound, fatalErrorSound, clickSound;

//Container Variables
private:
	ScreenColors textColor;
	ErrorTypes err;

//Local Class Constants
private:
	static const int answerSize = 3;
	
//Regular Variables
private:
	int id_;
	std::string name_;
	int score_;
	int playerPiece_;
	static int otherPlayerPiece_;
	int playerTurnOrder_;
	int move_;	//Stores the move of the player temporarly
	bool madeMove_;
	bool win_;
	int boundsLimit_;
	bool playerInitialized_;
	bool resetPlayerFunctionCalled_;
	static int numOfPlayers_;
};