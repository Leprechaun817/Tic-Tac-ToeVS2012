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

#include "WinDrawPacket.h"

//----Constants List Variables----//
const std::string WinDrawPacket::noWinDrawState = "noWinDrawState";
const std::string WinDrawPacket::winState = "winState";
const std::string WinDrawPacket::drawState = "drawState";
const std::string WinDrawPacket::acrossWinType = "acrossWinType";
const std::string WinDrawPacket::downWinType = "downWinType";
const std::string WinDrawPacket::diagonalWinType = "diagonalWinType";
const std::string WinDrawPacket::diagonalLeftSubType = "diagonalLeftSubType";
const std::string WinDrawPacket::diagonalRightSubType = "diagonalRightSubType";
const std::string WinDrawPacket::noPlayerPiece = "noPlayerPiece";
const std::string WinDrawPacket::oPlayerPiece = "oPlayerPiece";
const std::string WinDrawPacket::xPlayerPiece = "xPlayerPiece";
const std::string WinDrawPacket::columnOne = "columnOne";
const std::string WinDrawPacket::columnTwo = "columnTwo";
const std::string WinDrawPacket::columnThree = "columnThree";
const std::string WinDrawPacket::columnFour = "columnFour";
const std::string WinDrawPacket::columnFive = "columnFive";
const std::string WinDrawPacket::rowOne = "rowOne";
const std::string WinDrawPacket::rowTwo = "rowTwo";
const std::string WinDrawPacket::rowThree = "rowThree";
const std::string WinDrawPacket::rowFour = "rowFour";
const std::string WinDrawPacket::rowFive = "rowFive";
const std::string WinDrawPacket::nullConstant = "nullConstant";
const std::string WinDrawPacket::fatalError = "fatalError";

const std::string WinDrawPacket::packetUnreadable = "Packet has not been created yet...\nPlease run CreatePacket before sending the WinDrawPacket\nback to the Game object\n";

const std::string WinDrawPacket::fatalErrorSound = "fatalErrorSound";

WinDrawPacket::WinDrawPacket(const ConstList &cList) throw()
	: gameState_(-2), playerPiece_(-2), winType_(-2), diagonalType_(-2), rowAcross_(-2), columnDown_(-2), packetCreated_(false)
{
	constantsList = cList;
}

void WinDrawPacket::CreatePacket(const int gameOutcome, const int winningPiece, const int winLocation, const int winDiagonalLocation, const int winRowLocation, const int winColumnLocation)
{
	packetCreated_ = true;

	//Error values
	const int t_nullConstant = GetConstantFromList(nullConstant), t_fatalError = GetConstantFromList(nullConstant);

	//Other values needed for testing
	const int t_noWinDrawState = GetConstantFromList(noWinDrawState), t_drawState = GetConstantFromList(drawState), t_winState = GetConstantFromList(winState);

	if((gameOutcome == t_noWinDrawState) || (gameOutcome == t_drawState)) {
		gameState_ = gameOutcome;
		//Adding nullConstants here so if parser code in ProcessPacket goes to far it will pop up with a minor error
		playerPiece_ = winType_= diagonalType_ = rowAcross_ = columnDown_ = t_nullConstant;
	}
	else if(gameOutcome == t_winState) {
		gameState_ = gameOutcome;
		playerPiece_ = winningPiece;
		winType_ = winLocation;
		diagonalType_ = winDiagonalLocation;
		rowAcross_ = winRowLocation;
		columnDown_ = winColumnLocation;
	}
	else if(gameOutcome == t_nullConstant)
		//Minor error, list all variables with minor errors regardless of what they were before
		gameState_ = playerPiece_ = winType_ = diagonalType_ = rowAcross_ = columnDown_ = t_nullConstant;
	else if(gameOutcome == t_fatalError)
		//Major Error, list all variables with major errors regardless of what they were before
		gameState_ = playerPiece_ = winType_ = diagonalType_ = rowAcross_ = columnDown_ = t_fatalError;
	else
		//If gameOutcome has an unknown value treat as major error//
		//winDraw and all the other variables will equal whatever the weird number was in gameOutcome
		gameState_ = playerPiece_ = winType_ = diagonalType_ = rowAcross_ = columnDown_ = gameOutcome;

}

int WinDrawPacket::GetConstantFromList(std::string request) const
{
	int returnValue = -5;
	for(const auto &i : constantsList)
		if((i.first) == request) {
			returnValue = (i.second);
			break;
		}

	if(returnValue == -5) {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Unknown_Constant_Error);
	}

	return returnValue;
}

const int WinDrawPacket::GetGameState() const
{
	if(packetCreated_)
		return gameState_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}

const int WinDrawPacket::GetPlayerPiece() const
{
	if(packetCreated_)
		return playerPiece_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}

const int WinDrawPacket::GetWinType() const
{
	if(packetCreated_)
		return winType_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}

const int WinDrawPacket::GetDiagType() const
{
	if(packetCreated_)
		return diagonalType_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}

const int WinDrawPacket::GetRow() const
{
	if(packetCreated_)
		return rowAcross_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}

const int WinDrawPacket::GetColumn() const
{
	if(packetCreated_)
		return columnDown_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, packetUnreadable);
	}
}
