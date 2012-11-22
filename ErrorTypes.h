#pragma once

struct ErrorTypes
{
	enum types
	{
		Invalid_Variable_Access = 0,
		Move_Format_Invalid,
		Double_Function_Call,
		Piece_Exists_At_Location,
		Move_Out_Of_Bounds,
		Fatal_Error,
		Bad_PlayerPiece_Variable_Fatal,
		Bad_DiagonalLocation_Minor,
		Bad_DiagonalLocation_Fatal,
		Bad_DiagonalLocation_Unknown,
		Bad_AcrossLocation_Minor,
		Bad_AcrossLocation_Fatal,
		Bad_AcrossLocation_Unknown,
		Bad_DownLocation_Minor,
		Bad_DownLocation_Fatal,
		Bad_DownLocation_Unknown,
		Bad_WinType_Variable_Minor,
		Bad_WinType_Variable_Fatal,
		Bad_WinType_Variable_Unknown,
		Bad_GameState_Fatal,
		Bad_GameState_Unknown,
		Unknown_Error
	};
};
