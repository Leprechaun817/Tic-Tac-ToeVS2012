#include "ExceptionClass.h"

Exception::Exception(int type, string extraMsg1 = " ")
{
	switch(type)
	{
		case err.Invalid_Variable_Access:
			errorMsg = "Cannot access the variable, object uninitialized";
			break;
		case err.Move_Format_Invalid:
			errorMsg = "The move was invalid";
			break;
		case err.Double_Function_Call:
			break;
		case err.Piece_Exists_At_Location:
			break;
		case err.Move_Out_Of_Bounds:
			break;
		case err.Fatal_Error:
			break;
		case err.Bad_PlayerPiece_Variable_Fatal:
			break;
		case err.Bad_DiagonalLocation_Minor:
			break;
		case err.Bad_DiagonalLocation_Fatal:
			break;
		case err.Bad_DiagonalLocation_Unknown:
			break;
		case err.Bad_AcrossLocation_Minor:
			break;
		case err.Bad_AcrossLocation_Fatal:
			break;
		case err.Bad_AcrossLocation_Unknown:
			break;
		case err.Bad_DownLocation_Minor:
			break;
		case err.Bad_DownLocation_Fatal:
			break;
		case err.Bad_DownLocation_Unknown:
			break;
		case err.Bad_WinType_Variable_Minor:
			break;
		case err.Bad_WinType_Variable_Fatal:
			break;
		case err.Bad_WinType_Variable_Unknown:
			break;
		case err.Bad_GameState_Fatal:
			break;
		case err.Bad_GameState_Unknown:
			break;
		case err.Unknown_Error:
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