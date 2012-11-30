#pragma warning( disable : 4101 )	//Disables warning about unreferenced local variable. There doesn't seem to be a way to reference it without using it...
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <conio.h>
#include <ctime>
#include "ExceptionClass.h"
#include "ErrorTypes.h"
#include "Game.h"

using namespace std;

typedef auto_ptr<Game> GamePtr;

int main()
{
	srand((unsigned)time(0));
	GamePtr game(new Game());
	ErrorTypes err;

	try
	{
		//Start the game
		game->StartGame();
	
		//Declare game control variable and set to true
		//This will be set to false by the GameLoop when either player wishes to quit or the game is over
		bool gameRunning = true;
		while(gameRunning == true)
		{
			//continue the game
			//This will get called every time the game loops
			gameRunning = game->GameLoop();

			if(gameRunning == false)
			{
				bool end;
				//gameRunning came back false call EndGame
				//So player can start a new round or quit the game entirely
				end = game->EndGame();

				if(end == false)	//No, player doesn't want to quit, wants to start a new round
				{
					game->ResetGame();
					game->StartGame();
					//Reset gameRunning to true so that it continues to loop
					gameRunning = true;
				}
				else				//Yes, player does want to quit. Doesn't want to start a new round
				{
					//gameRunning already set to false, no need to reassign it
					//Clear the screen
					system("cls");
				}
			}
		}
	}
	catch(Exception &e)
	{
		if(e.GetErrorType() != err.Invalid_Variable_Access)
		{
			system("cls");
			cout<<e.what()<<"\n";
			cout<<"The program will now close...\n";
			cout<<"Press any key to continue..."<<endl;
			_getche();
			exit(EXIT_FAILURE);
		}
		else
		{
			system("cls");
			cout<<e.what()<<"\n";
			cout<<"Failed to initialize objects properly.\n";
			cout<<"Press any key to continue..."<<endl;
			_getche();
			exit(EXIT_FAILURE);
		}
	}

	game->DisplayFinalStats();
	cout<<"Hope you enjoyed the game!!\n";
	cout<<"Thanks for playing... ^_^"<<endl;
	_getche();
	
	return 0;
}