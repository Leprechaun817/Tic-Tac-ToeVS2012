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
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <memory>
#include <map>
#include <array>
#include <Windows.h>
#include "Board.h"
#include "Player.h"
#include "WinDrawPacket.h"
#include "SoundEngine.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

typedef std::unique_ptr<WinDrawPacket> WDPacketPtr;
typedef std::map<const std::string, int> ConstList;

class Game
{
public:
	Game() throw();
	void StartGame();
	bool GameLoop();		//All the different states that the game could be in are listed as
	bool EndGame();			//functions here. These are called as is necessary through the game loop
	void ResetGame();		//in the main.
	void DisplayFinalStats();
	void DisplayLastRoundStats();

//----Message Constants----
private:
	//Win/Draw Messages
	static const std::string gameDrawMessage, playerOneWinMessage, playerTwoWinMessage;
	//Other Messages
	static const std::string anyKey;

//----Constants Strings----
private:
	//These are used while creating the constantsList
	static const std::string noWinDrawState, winState, drawState;
	static const std::string acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType;
	static const std::string noPlayerPiece, oPlayerPiece, xPlayerPiece;
	static const std::string columnOne, columnTwo, columnThree, columnFour, columnFive;
	static const std::string rowOne, rowTwo, rowThree, rowFour, rowFive;
	static const std::string nullConstant;
	static const std::string fatalError;

	//Used in accessing the sounds
	static const std::string playerOneWinSound, playerTwoWinSound, gameOverSound, pieceClickSound, badMoveErrorSound, fatalErrorSound, clickSound, endOfGameSound, minorErrorSound;

//Object Variables
private:
	Player playerOne_, playerTwo_;
	Board board_;
	HANDLE hConsole_;
	HWND hWnd_;

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
	bool CheckGameState(WDPacketPtr packet);
	int GetConstantFromList(std::string request) const;
	void DecidePlayOrder();
	void DisplayGameInstructions();
	void DisplayNotices();
	void DisplayNoticeFile(char noticeType);
	void SetGameFullscreen();
	void SetGameWindowed();
};