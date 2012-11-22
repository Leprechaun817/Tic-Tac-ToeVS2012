#include "ExceptionClass.h"

Exception::Exception(int type, string extraMsg1)
{
	errorType = type;
	switch(type)
	{
		case err.Invalid_Variable_Access:
			errorMsg = "Cannot access the variable, object uninitialized";
			break;
		case err.Move_Format_Invalid:
			errorMsg = "The move was invalid";
			break;
		case err.Double_Function_Call:
			errorMsg = "This function has already been called,\nit can't be called again.";
			break;
		case err.Piece_Exists_At_Location:
			errorMsg = "A piece already exists here.";
			break;
		case err.Move_Out_Of_Bounds:
			errorMsg = "The location of your move doesn't exist.";
			break;
		case err.Minor_Error:
			errorMsg = "Tic-Tac-Toe had a minor error and cannot recover.";
			break;
		case err.Fatal_Error:
			errorMsg = "Tic-Tac-Toe had a fatal error and cannot recover.";
			break;
		case err.Unknown_Error:
			errorMsg = "Tic-Tac-Toe had an unknown error and cannot recover.\nUse the debugger to figure out what happened.";
			break;
		case err.Bad_PlayerPiece_Variable_Fatal:
			errorMsg = "An fatal error has occured with the playerPiece variable in the packet.\nCheck packet code.\n";
			break;
		case err.Bad_DiagonalLocation_Minor:
			errorMsg = "A minor error has occured with the diagonalType variable in the packet.\n";
			errorMsg += "The diagonalType variable shouldn't be a -1 when the winType variable is equal to a diagonal.\nPlease check the diagonalType variable!!";
			break;
		case err.Bad_DiagonalLocation_Fatal:
			errorMsg = "A fatal error has occured with the diagonalType variable in the packet.\n";
			errorMsg += "The diagonalType variable shouldn't be a -2 when winType variable is equal to a diagonal.";
			break;
		case err.Bad_DiagonalLocation_Unknown:
			errorMsg = "A unknown error has occured with the diagonalType variable in the packet.\n";
			errorMsg += "The diagonalType variable had an unexpected output.";
			break;
		case err.Bad_AcrossLocation_Minor:
			errorMsg = "A minor error has occured with the rowAcross variable in the packet.\n";
			errorMsg += "The row variable shouldn't be a -1 when the winType variable is equal to an across.";
			break;
		case err.Bad_AcrossLocation_Fatal:
			errorMsg = "A fatal error has occured with the rowAcross variable in the packet.\n";
			errorMsg += "The row variable shouldn't be a -2 when the winType is equal to an across.";
			break;
		case err.Bad_AcrossLocation_Unknown:
			errorMsg = "A unknown error has occured with the rowAcross variable in the packet.\n";
			errorMsg += "The row variable had an unexpected output.";
			break;
		case err.Bad_DownLocation_Minor:
			errorMsg = "A minor error has occured with the columnDown variable in the packet.\n";
			errorMsg += "The column variable shouldn't be a -1 when the winType is equal to a down.";
			break;
		case err.Bad_DownLocation_Fatal:
			errorMsg = "A fatal error has occured with the columnDown variable in the packet.\n";
			errorMsg += "The column variable shouldn't be a -2 when the winType is equal to a down.";
			break;
		case err.Bad_DownLocation_Unknown:
			errorMsg = "A unknown error has occured with the columnDown variable in the packet.\n";
			errorMsg += "The column variable had an unexpected output.";
			break;
		case err.Bad_WinType_Variable_Minor:
			errorMsg = "A minor error has occured with the winType variable in the packet.\n";
			errorMsg += "The winType variable shouldn't be a -1 when a win exists.";
			break;
		case err.Bad_WinType_Variable_Fatal:
			errorMsg = "A fatal error has occured with the winType variable in the packet.\n";
			errorMsg += "The winType variable shouldn't be a -2 when a win exists.";
			break;
		case err.Bad_WinType_Variable_Unknown:
			errorMsg = "A unknown error has occured with the winType variable in the packet.\n";
			errorMsg += "The winType definitly shouldn't be a unknown error.\nPlease double check code for serious errors!!";
			break;
		case err.Bad_GameState_Fatal:
			errorMsg = "A fatal error has occured with the gameState variable in the packet.\n";
			errorMsg += "The winDraw variable cannot equal -2. Double check the code logic.";
			break;
		case err.Bad_GameState_Unknown:
			errorMsg = "A unknown error has occured with the gameState variable in the packet.\n";
			errorMsg += "The winDraw variable has an unknown error value.";
			break;
	}
	
	if(extraMsg1 != " ")
	{
		errorMsg += "\n";
		errorMsg += extraMsg1;
	}
}

const char* Exception::what() const throw()
{
	return errorMsg.c_str();
}

const int Exception::GetErrorType() const
{
	return errorType;
}