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
#include "ExceptionClass.h"
#include "ErrorTypes.h"

typedef std::map<const std::string, int> ConstList;

class WinDrawPacket
{
public:
	WinDrawPacket(const ConstList &cList) throw();
	
	//This used to create the packet that will get sent from the board object to the game object
	void CreatePacket(const int gameOutcome, const int winningPiece, const int winLocation, const int winDiagonalLocation, const int winRowLocation, const int winColumnLocation);

	//----Const notes----
	//Adding const before a function makes the compiler catch assignment errors in things like if statements
	//Adding const after the function is basically guaranteeing the compiler that it is a inspector function and not a mutator function
	//Get variables
	const int GetGameState() const;
	const int GetPlayerPiece() const;
	const int GetWinType() const;
	const int GetDiagType() const;
	const int GetRow() const;
	const int GetColumn() const;

//----Constants List Variables----//
private:
	static const std::string noWinDrawState, winState, drawState;
	static const std::string acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType;
	static const std::string noPlayerPiece, oPlayerPiece, xPlayerPiece;
	static const std::string columnOne, columnTwo, columnThree, columnFour, columnFive;
	static const std::string rowOne, rowTwo, rowThree, rowFour, rowFive;
	static const std::string nullConstant;
	static const std::string fatalError;

//Local Class Constants
private:
	//Local Error String -- Unique to the WinDrawPacket object
	static const std::string packetUnreadable;

//Container Variables
private:
	ConstList constantsList;
	ErrorTypes err;

//Regular variables
private:
	int gameState_;
	int playerPiece_;
	int winType_;
	int diagonalType_;
	int rowAcross_;
	int columnDown_;
	bool packetCreated_;	//This makes the packet unreadable until CreatePacket has been run

//Private Functions
private:
	int GetConstantFromList(std::string request) const;
};