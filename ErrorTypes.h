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

struct ErrorTypes
{
	enum types
	{
		Invalid_Variable_Access = 0,
		Move_Format_Invalid,
		Double_Function_Call,
		Piece_Exists_At_Location,
		Move_Out_Of_Bounds,
		Minor_Error,
		Fatal_Error,
		Unknown_Error,
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
		NonAcceptance_Of_Notices
	};
};
