#include <iostream>
#include <conio.h>
#include <ctime>
#include <conio.h>
#include "Game.h"

using namespace std;

int main()
{
	srand((unsigned)time(0));
	Game *game;		//Declare the game object
	game = new Game();	//Instantiate the game object
	
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

	//TODO:
	//Show final stats here right after the screen is cleared
	cout<<"Hope you enjoyed the game!!"<<endl;
	cout<<"Thanks for playing... ^_^"<<endl;
	_getche();

	return 0;
}