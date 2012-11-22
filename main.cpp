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
				if(game->HasGameHadFatalError() == false)
				{
					game->ResetGame();
					game->StartGame();
					//Reset gameRunning to true so that it continues to loop
					gameRunning = true;
				}
			}
			else				//Yes, player does want to quit. Doesn't want to start a new round
			{
				//gameRunning already set to false, no need to reassign it
				//Clear the screen
				system("cls");
			}
		}
	}

	//TODO:
	//Show final stats here right after the screen is cleared
	if(game->HasGameHadFatalError() == false)
	{
		cout<<"Hope you enjoyed the game!!"<<endl;
		cout<<"Thanks for playing... ^_^"<<endl;
		_getche();
	}
	else
	{
		//Message here about what to do in the event of an error.
	}

	return 0;
}