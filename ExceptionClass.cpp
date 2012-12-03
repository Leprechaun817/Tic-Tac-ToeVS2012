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

#include "ExceptionClass.h"

Exception::Exception(int type, string extraMsg1) throw()
	: errorType_(type), errorMsg_(extraMsg1)
{
	switch(type) {
		case err.Invalid_Variable_Access:
			errorMsg_ = "Cannot access the variable, object uninitialized";
			break;
		case err.Move_Format_Invalid:
			errorMsg_ = "The move was invalid";
			break;
		case err.Double_Function_Call:
			errorMsg_ = "This function has already been called,\nit can't be called again.";
			break;
		case err.Piece_Exists_At_Location:
			errorMsg_ = "A piece already exists here.";
			break;
		case err.Move_Out_Of_Bounds:
			errorMsg_ = "The location of your move doesn't exist.";
			break;
		case err.Minor_Error:
			errorMsg_ = "Tic-Tac-Toe had a minor error and cannot recover.";
			break;
		case err.Fatal_Error:
			errorMsg_ = "Tic-Tac-Toe had a fatal error and cannot recover.";
			break;
		case err.Unknown_Error:
			errorMsg_ = "Tic-Tac-Toe had an unknown error and cannot recover.\nUse the debugger to figure out what happened.";
			break;
		case err.Bad_PlayerPiece_Variable_Fatal:
			errorMsg_ = "An fatal error has occured with the playerPiece variable in the packet.\nCheck packet code.\n";
			break;
		case err.Bad_DiagonalLocation_Minor:
			errorMsg_ = "A minor error has occured with the diagonalType variable in the packet.\n";
			errorMsg_ += "The diagonalType variable shouldn't be a -1 when the winType variable is equal to a diagonal.\nPlease check the diagonalType variable!!";
			break;
		case err.Bad_DiagonalLocation_Fatal:
			errorMsg_ = "A fatal error has occured with the diagonalType variable in the packet.\n";
			errorMsg_ += "The diagonalType variable shouldn't be a -2 when winType variable is equal to a diagonal.";
			break;
		case err.Bad_DiagonalLocation_Unknown:
			errorMsg_ = "A unknown error has occured with the diagonalType variable in the packet.\n";
			errorMsg_ += "The diagonalType variable had an unexpected output.";
			break;
		case err.Bad_AcrossLocation_Minor:
			errorMsg_ = "A minor error has occured with the rowAcross variable in the packet.\n";
			errorMsg_ += "The row variable shouldn't be a -1 when the winType variable is equal to an across.";
			break;
		case err.Bad_AcrossLocation_Fatal:
			errorMsg_ = "A fatal error has occured with the rowAcross variable in the packet.\n";
			errorMsg_ += "The row variable shouldn't be a -2 when the winType is equal to an across.";
			break;
		case err.Bad_AcrossLocation_Unknown:
			errorMsg_ = "A unknown error has occured with the rowAcross variable in the packet.\n";
			errorMsg_ += "The row variable had an unexpected output.";
			break;
		case err.Bad_DownLocation_Minor:
			errorMsg_ = "A minor error has occured with the columnDown variable in the packet.\n";
			errorMsg_ += "The column variable shouldn't be a -1 when the winType is equal to a down.";
			break;
		case err.Bad_DownLocation_Fatal:
			errorMsg_ = "A fatal error has occured with the columnDown variable in the packet.\n";
			errorMsg_ += "The column variable shouldn't be a -2 when the winType is equal to a down.";
			break;
		case err.Bad_DownLocation_Unknown:
			errorMsg_ = "A unknown error has occured with the columnDown variable in the packet.\n";
			errorMsg_ += "The column variable had an unexpected output.";
			break;
		case err.Bad_WinType_Variable_Minor:
			errorMsg_ = "A minor error has occured with the winType variable in the packet.\n";
			errorMsg_ += "The winType variable shouldn't be a -1 when a win exists.";
			break;
		case err.Bad_WinType_Variable_Fatal:
			errorMsg_ = "A fatal error has occured with the winType variable in the packet.\n";
			errorMsg_ += "The winType variable shouldn't be a -2 when a win exists.";
			break;
		case err.Bad_WinType_Variable_Unknown:
			errorMsg_ = "A unknown error has occured with the winType variable in the packet.\n";
			errorMsg_ += "The winType definitly shouldn't be a unknown error.\nPlease double check code for serious errors!!";
			break;
		case err.Bad_GameState_Fatal:
			errorMsg_ = "A fatal error has occured with the gameState variable in the packet.\n";
			errorMsg_ += "The winDraw variable cannot equal -2. Double check the code logic.";
			break;
		case err.Bad_GameState_Unknown:
			errorMsg_ = "A unknown error has occured with the gameState variable in the packet.\n";
			errorMsg_ += "The winDraw variable has an unknown error value.";
			break;
		case err.NonAcceptance_Of_Notices:
			errorMsg_ = "Did not accept the license.\nThis program will now close.";
			break;
		case err.Unknown_Constant_Error:
			errorMsg_ = "Constant that was searched for does not exist.";
			break;
		case err.SoundBuffer_Fatal_Error:
			errorMsg_ = "A fatal error has occurred with the sound buffer.";
			break;
		case err.SoundEngine_Fatal_Error:
			errorMsg_ = "A fatal error has occurred with the sound engine.";
			break;
	}
	
	if(extraMsg1 != " ") {
		errorMsg_ += "\n";
		errorMsg_ += extraMsg1;
	}
}

const char* Exception::what() const throw()
{
	return errorMsg_.c_str();
}

const int Exception::GetErrorType() const
{
	return errorType_;
}