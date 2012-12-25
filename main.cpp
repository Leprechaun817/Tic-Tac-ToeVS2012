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

#pragma warning( disable : 4101 )	//Disables warning about unreferenced local variable.
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <conio.h>
#include <ctime>
#include "ExceptionClass.h"
#include "ErrorTypes.h"
#include "Game.h"
#include "SoundEngine.h"

typedef std::unique_ptr<Game> GamePtr;

int main()
{
	const std::string fatalErrorSound = "fatalErrorSound";
	const std::string minorErrorSound = "minorErrorSound";
	const std::string endOfGameSound = "endOfGameSound";
	const std::string clickSound = "clickSound";

	srand((unsigned)time(0));
	GamePtr game(new Game());
	ErrorTypes err;
	
	try {
		//Start the game
		game->StartGame();
	
		//Declare game control variable and set to true
		//This will be set to false by the GameLoop when either player wishes to quit or the game is over
		bool gameRunning = true;
		while(gameRunning == true) {
			//continue the game
			//This will get called every time the game loops
			gameRunning = game->GameLoop();

			if(gameRunning == false) {
				bool end;
				//gameRunning came back false call EndGame
				//So player can start a new round or quit the game entirely
				end = game->EndGame();

				if(end == false) {	//No, player doesn't want to quit, wants to start a new round
					game->ResetGame();
					game->StartGame();
					//Reset gameRunning to true so that it continues to loop
					gameRunning = true;
				}
				else				//Yes, player does want to quit. Doesn't want to start a new round
					system("cls");
			}
		}
	}
	catch(Exception &e) {
		int errorType = e.GetErrorType();
		if(errorType == err.Invalid_Variable_Access) {
			system("cls");
			std::cout<<e.what()<<"\n";
			std::cout<<"DEBUG MESSAGE - Failed to initialize objects properly.\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			exit(EXIT_FAILURE);	
		}
		else if(errorType == err.NonAcceptance_Of_Notices) {
			SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);	//temporary - will remove this later. I just want to test it...
			system("cls");
			std::cout<<e.what()<<"\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			exit(EXIT_SUCCESS);
		}
		else if(errorType == err.Unknown_Constant_Error) {
			system("cls");
			std::cout<<e.what()<<"\n";
			std::cout<<"DEBUG MESSAGE - Check the call in the code, probably a misspelled argument or something...\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			exit(EXIT_FAILURE);
		}
		else if(errorType == err.Minor_Error || errorType == err.Bad_DiagonalLocation_Minor || errorType == err.Bad_AcrossLocation_Minor || errorType == err.Bad_DownLocation_Minor ||
				errorType == err.Bad_WinType_Variable_Minor)
		{
			SoundEngine::GetInstance()->PlaySoundFromQueue(minorErrorSound);
			system("cls");
			std::cout<<e.what()<<"\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			exit(EXIT_FAILURE);
		}
		else {
			SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
			system("cls");
			std::cout<<e.what()<<"\n";
			std::cout<<"The program will now close...\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			exit(EXIT_FAILURE);
		}
	}

	game->DisplayFinalStats();
	std::cout<<"Hope you enjoyed the game!!\n";
	std::cout<<"Thanks for playing... ^_^"<<std::endl;
	SoundEngine::GetInstance()->PlaySoundFromQueue(endOfGameSound);
	_getche();
	
	return 0;
}