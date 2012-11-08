#include "Game.h"

//----Message Constants----
//Win/Draw Messages
const string Game::gameDrawMessage = "The game has ended in a draw.\nYou can now start a new round or end the game...\n";
const string Game::playerOneWinMessage = "Player 1 has won this round!!\nCongratulations!!!^o^\n";
const string Game::playerTwoWinMessage = "Player 2 has won this round!!\nCongratulations!!!^o^\n";
//WinDrawPacket Related Messages
const string Game::winDrawErrorMessage = "An error has occured with the winDraw variable in the packet.\nCheck packet code.\n";
const string Game::playerPieceErrorMessage = "An error has occured with the playerPiece variable in the packet.\nCheck packet code.\n";
const string Game::winTypeErrorMessage = "An error has occured with the winType variable in the packet.\nCheck packet code.\n";
const string Game::diagonalTypeErrorMessage = "An error has occured with the diagonalType variable in the packet.\nCheck packet code.\n";
const string Game::rowAcrossErrorMessage = "An error has occured with the rowAcross variable in the packet.\nCheck packet code.\n";
const string Game::columnDownErrorMessage = "An error has occured with the columnDown variable in the packet.\nCheck packet code.\n";
//Main Error Messages
const string Game::fatalErrorMessage = "A fatal error has occurred.\nThe game will now close.\n";
const string Game::minorErrorMessage = "A minor error has occurred.\nThe game will now close.\n";
//Other Messages
const string Game::anyKey = "Press any key to continue...\n";

Game::Game()
	: playerOne(), playerTwo(), board(), gameConstants()
{
	//Zero gamesPlayed
	roundsPlayed = 0;
	//Zero draws as no games have been played yet...
	gameDraws = 0;
	//Turn counter set to zero
	turnCounter = 0;

	//set bounds limit, basically players shouldn't be able to enter in values past this number
	//It's also the number used to determine if somebody won the game
	//The value is pulled from the board object
	boundsLimit = board.GetMultiplier();
	//Setting bounds limits for each player
	playerOne.SetBoundsLimit(boundsLimit);
	playerTwo.SetBoundsLimit(boundsLimit);

	//First time game is starting so firstPlay is true
	firstPlay = true;

	//Figure out play order
	if(playerOne.GetPieceNum() == 2)
	{
		playOrder = 1;
	}
	else
	{
		playOrder = 2;
	}
}

void Game::StartGame()
{
	//First board was layed out when the board object was instantiated so all that's left
	//to do is to give the player some instructions
	if(firstPlay == true)
	{
		cout<<"Welcome to Tic-Tac-Toe!!!!!!!"<<endl;
		cout<<"Get "<<boundsLimit<<" in a row to win."<<endl;
		cout<<"Each player will enter his/her choice into the prompt,\n";
		cout<<"your choice will then appear on the board and you will get a chance to\n";
		cout<<"enter in another choice."<<endl;
		cout<<"When somebody wins the game or the game is a draw, you can play another\n";
		cout<<"or, you can quit. The number of wins or draws that you rack up will be\n";
		cout<<"displayed as you play."<<endl;
		cout<<"Remember columns go down and are numbered 1 - "<<boundsLimit<<" going from\n";
		cout<<"left to right. Rows go across and are number 1 - "<<boundsLimit<<" going from\n";
		cout<<"top to bottom. So to put an X or O on the first square you would type in\n";
		cout<<"\"1,1\". Don't forget the comma you have to have that."<<endl;
		cout<<"The player who got Xs will go first, this is picked randomly each time a new game is played"<<endl;
		cout<<"Whenever you're ready we can start..."<<endl;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		firstPlay = false;
	}
	
	//Set gamesPlayed to 1 as this is the first game, unless that was already the case.
	//When that happens roundsPlayed is incremented by 1
	if(roundsPlayed == 0)
	{
		roundsPlayed = 1;
	}
	else
	{
		roundsPlayed++;
	}

	//Clear screen, display first play board
	system("cls");

	//Display the empty starting board
	board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
	//Get the first round of player moves
	//Call GameLoop at this point
}

bool Game::GameLoop()
{
	bool continueGame = true;
	
	//Let players make their moves
	continueGame = GetPlayerMoves();
	
	//Check for win or draw, only after the amounts of total turns taken equals the multiplier
	if(turnCounter >= boundsLimit)
	{
		continueGame = ProcessPacket(board.FindWinDraw());
	}

	return continueGame;
}

bool Game::EndGame()
{
	bool endSession;
	char answer;

	//Clear the screen
	system("cls");
	//Show results of the last round played
	//Ask player/s whether they want to play another round
	bool loop = false;
	while(loop == false)
	{
		cout<<"Would you like to play for another round? y or n"<<endl;
		cin>>answer;

		if(answer == 'Y' || answer == 'y')
		{
			endSession = false;		//Player doesn't want to end the game. Wants to go for another round
			loop = true;
		}
		else if(answer == 'N' || answer == 'n')
		{
			endSession = true;		//Player does want to end the game. Doesn't want to keep playing
			loop = true;
		}
		else
		{
			cout<<"Please enter y or n"<<endl;
			cout<<"Press any key to continue..."<<endl;
			_getche();
			system("cls");
		}
	}

	return endSession;
}

void Game::ResetGame()
{
	//Game object specific stuff
	turnCounter = 0;
	firstPlay = false;
	
	//Reset the board first
	board.ResetBoard();
	
	//Then get multiplier from the board
	//This keeps problems with bounds issues popping up
	boundsLimit = board.GetMultiplier();

	//Reset the player piece using one of the players
	//This works because otherPlayerPiece in the Player class is static
	//and doesn't change when a new player is instaniated. Unless you go in
	//and chnage it through a call or manually
	playerOne.ResetPlayerPiece();

	//Reset both players
	playerOne.ResetPlayer();
	playerTwo.ResetPlayer();

	//Reset BoundsLimits for both players
	playerOne.SetBoundsLimit(boundsLimit);
	playerTwo.SetBoundsLimit(boundsLimit);
}

bool Game::GetPlayerMoves()
{
	bool continuePlay = true;

	if(playOrder == 1)
	{
		continuePlay = PlayerOneMove();
		if(continuePlay == true)
		{
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
		}
		else
		{
			return continuePlay;
		}
		
		continuePlay = PlayerTwoMove();
		if(continuePlay == true)
		{
			//Now that both players have made their moves increment the turnCounter by 1
			turnCounter++;
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
		}
		else
		{
			return continuePlay;
		}
	}
	else
	{
		continuePlay = PlayerTwoMove();
		if(continuePlay == true)
		{
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
		}
		else
		{
			return continuePlay;
		}

		continuePlay = PlayerOneMove();
		if(continuePlay == true)
		{
			//Same thing, both players have made their moves. Increment the turnCounter by 1
			turnCounter++;
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
		}
		else
		{
			return continuePlay;
		}
	}

	return continuePlay;
}

bool Game::PlayerOneMove()
{
	bool moveIsGood = false;
	bool continuePlay = true;
	while(moveIsGood == false)
	{
		continuePlay = playerOne.MakeMove();
		if(continuePlay == false)
		{
			//Break out of loop and continue quit propogation
			break;
		}

		playerOne.SetMadeMove(true);
		cout<<endl;
		moveIsGood = CheckAndUpdateBoard(FormatMove(playerOne.GetMove()));
		//If move is no good, move through loop until player enters a good move
		if(moveIsGood == false)
		{
			playerOne.SetMove(" ");
			//playerOne->SetMadeMove(false);
			//SetMadeMove will be called in CheckAndUpdateBoard in the event that the move is no good
			//If this doesn't work, uncomment the first line as an insurance policy to make sure that madeMove is
			//made false. Otherwise the move check might get messed up.
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerOne.GetName(), playerOne.GetScore(), playerOne.GetPieceNum(), playerOne.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
			cout<<endl;
			cout<<"Please re-enter your move."<<endl;
			_getche();
		}
		else
		{
			//If move checked out ok and was entered into the vector in preperation for the board refresh
			//Reset players move and set players madeMove variable to false in preperation for next turn
			playerOne.SetMove(" ");
			playerOne.SetMadeMove(false);
		}
	}

	return continuePlay;
}

bool Game::PlayerTwoMove()
{
	bool moveIsGood = false;
	bool continuePlay = true;
	while(moveIsGood == false)
	{
		continuePlay = playerTwo.MakeMove();
		if(continuePlay == false)
		{
			//Break out of loop and continue quit propogation
			break;
		}

		playerTwo.SetMadeMove(true);
		cout<<endl;
		moveIsGood = CheckAndUpdateBoard(FormatMove(playerTwo.GetMove()));
		//If move is no good, move through if,then statement and reset everything.
		//Then player will be told to re-enter the move
		if(moveIsGood == false)
		{
			playerTwo.SetMove(" ");
			//playerTwo->SetMadeMove(false);
			//SetMadeMove will be called in CheckAndUpdateBoard in the event that the move is no good
			system("cls");
			board.DisplayBoard(roundsPlayed, gameDraws, playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor(), playerTwo.GetName(), playerTwo.GetScore(), playerTwo.GetPieceNum(), playerTwo.GetTextColor());
			cout<<endl;
			cout<<"Please re-enter your move."<<endl;
			_getche();
		}
		else
		{
			//If move checked out ok and was entered into the vector in preperation for the board refresh
			//Reset players move and set players madeMove variable to false in preperation for next turn
			playerTwo.SetMove(" ");
			playerTwo.SetMadeMove(false);
		}
	}

	return continuePlay;
}

int Game::FormatMove(string move)
{
	stringstream s;
	string temp;
	int newMove = 0;

	temp += move[0];
	temp += move[2];

	s<<temp;
	s>>newMove;
	
	newMove *= 10;

	return newMove;
}

bool Game::CheckAndUpdateBoard(int move)
{
	//string constants for error codes...
	//I would of put them in the class, but they're specific to this function so it makes more sense
	//to me to just put them in the function instead of the class
	const string error0 = "No moves made, check GetPlayerMoves, as well as PlayerOneMove and\nPlayerTwoMove";
	const string error1 = "This location already has a piece on it\n";
	const string error2 = "This location doesn't match any of the locations on the grid\n";
	const string error3 = "Fatal error, something is wrong with the code. (DEBUG MESSAGE)\n";	//Only used during debuging, remove afterwards
	const string anyKey = "Press any key to continue...\n";
	int moveError = 4;	//moveCheck is declared with 4 because 0 - 3 are error codes.
						//Basically, if this still equals 4 after the if...then...else, then there are no errors
	bool moveCheck = false;		//moveCheck is false until the moveError has been evaluated. If moveError still equals 4
								//then there are no errors and the check passes, therefore moveCheck will be true.
								//Less code this way, moveCheck is only made true if no errors are found, so the moveCheck needs to be changed
								//exactly once
	
	if(playerOne.CheckMadeMove() == false && playerTwo.CheckMadeMove() == false)
	{
		moveError = 0;
	}
	else if(playerOne.CheckMadeMove() == true)
	{
		moveError = board.BoardRefresh(playerOne.GetPieceNum(), move, playerOne.CheckMadeMove(), playerTwo.CheckMadeMove());
	}
	else if(playerTwo.CheckMadeMove() == true)
	{
		moveError = board.BoardRefresh(playerTwo.GetPieceNum(), move, playerOne.CheckMadeMove(), playerTwo.CheckMadeMove());
	}
	else	//This is else is purely for debug purposes. Under normal circumstances this should never get called!!!
	{
		moveError = 3;
	}

	switch (moveError)
	{
	case 0:
		cout<<error0<<anyKey;
		_getche();
		break;
	case 1:
		cout<<error1<<anyKey;
		_getche();
		break;
	case 2:
		cout<<error2<<anyKey;
		_getche();
		break;
	case 3:
		cout<<error3<<anyKey;
		_getche();
		break;
	case 4:
		//No errors made, move is good
		moveCheck = true;
		break;
	}

	return moveCheck;
}

bool Game::ProcessPacket(WDPacketPtr packet)
{
	bool continueGame = true;
	int tempType;
	int tempDiagonalLocation;
	int tempAcrossDownLocation;
	if(packet->GetWinDraw() == gameConstants.GetConstNoWinDraw() || packet->GetWinDraw() == gameConstants.GetConstDraw())
	{
		if(packet->GetWinDraw() == gameConstants.GetConstDraw())
		{
			gameDraws++;
			//put message indicating that a draw has occurred and a new game is starting
			cout<<gameDrawMessage;
			cout<<anyKey;
			_getche();
			continueGame = false;
			return continueGame;
		}
		else
		{
			return continueGame;
		}
	}
	else if(packet->GetWinDraw() == gameConstants.GetConstWin())
	{
		//Get player piece and compare, update their winCounter
		if(packet->GetPlayerPiece() == playerOne.GetPieceNum())
		{
			playerOne.UpdateScore();
			//Message telling that player 1 has won the game
			cout<<playerOneWinMessage;
			playerOne.DisplayScore();
			cout<<anyKey;
			_getche();
		}
		else if(packet->GetPlayerPiece() == playerTwo.GetPieceNum())
		{
			playerTwo.UpdateScore();
			//Message telling that player 2 has won the game
			cout<<playerTwoWinMessage;
			playerTwo.DisplayScore();
			cout<<anyKey;
			_getche();
		}
		else
		{
			//Message saying there has been a fatal error in the packet
			cout<<fatalErrorMessage;
			cout<<playerPieceErrorMessage;
			cout<<anyKey;
			_getche();
			continueGame = false;
			return continueGame;
		}

		//Find out where player won, store values in temp variables and send to DisplayBoard function
		if(packet->GetWinType() == gameConstants.GetConstDiagonal())
		{
			tempType = gameConstants.GetConstDiagonal();
			if(packet->GetDiagType() == gameConstants.GetConstDiagonalLeft())
			{
				tempDiagonalLocation = gameConstants.GetConstDiagonalLeft();
			}
			else if(packet->GetDiagType() == gameConstants.GetConstDiagonalRight())
			{
				tempDiagonalLocation = gameConstants.GetConstDiagonalRight();
			}
			else //diagType didn't equal 1 or 2 even though the winning move was a diagonal, this is an error
			{
				if(packet->GetDiagType() == gameConstants.GetConstNullConstant())
				{
					//Message stating a minor error has occurred and the code should be checked out
					cout<<minorErrorMessage;
					cout<<diagonalTypeErrorMessage;
					//Special message because of the 2 errors that can occur here
					cout<<"The diagonalType variable shouldn't be a -1 when the winType variable is equal to a diagonal.\nPlease check the diagonalType variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else //if packet->GetDiagType() returns a -2 -- Fatal Error
				{
					//Message stating the a fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<diagonalTypeErrorMessage;
					cout<<"The diagonalType variable shouldn't be a -2 when winType variable is equal to a diagonal.\n";
					cout<<"Please check both the winType and diagonalType variables.\n";
					cout<<anyKey;
					_getche();
				}

				//Both errors will result in the game closing
				continueGame = false;
				return continueGame;
			}
		}
		else if(packet->GetWinType() == gameConstants.GetConstAcross())
		{
			tempType = gameConstants.GetConstAcross();
			tempDiagonalLocation = gameConstants.GetConstNullConstant();
			if(packet->GetRow() == gameConstants.GetConstRowOne())
			{
				tempAcrossDownLocation = gameConstants.GetConstRowOne();
			}
			else if(packet->GetRow() == gameConstants.GetConstRowTwo())
			{
				tempAcrossDownLocation = gameConstants.GetConstRowTwo();
			}
			else if(packet->GetRow() == gameConstants.GetConstRowThree())
			{
				tempAcrossDownLocation = gameConstants.GetConstRowThree();
			}
			else if(packet->GetRow() == gameConstants.GetConstRowFour())
			{
				tempAcrossDownLocation = gameConstants.GetConstRowFour();
			}
			else if(packet->GetRow() == gameConstants.GetConstRowFive())
			{
				tempAcrossDownLocation = gameConstants.GetConstRowFive();
			}
			else //the row didn't match any of the row locations, an error has occurred
			{
				if(packet->GetRow() == gameConstants.GetConstNullConstant())
				{
					//Message stating minor error has occurred
					cout<<minorErrorMessage;
					cout<<rowAcrossErrorMessage;
					cout<<"The row variable shouldn't be a -1 when the winType variable is equal to an across.\nPlease check the row variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else //if row didn't equal -1 then it must equal -2, which means a fatal error has occurred
				{
					//Message stating fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<rowAcrossErrorMessage;
					cout<<"The row variable shouldn't be a -2 when the winType is equal to an across.\n";
					cout<<"Please check both the winType and row variables.\n";
					cout<<anyKey;
					_getche();
				}

				//End the game
				continueGame = false;
				return continueGame;
			}
		}
		else if(packet->GetWinType() == gameConstants.GetConstDown())
		{
			tempType = gameConstants.GetConstDown();
			tempDiagonalLocation = gameConstants.GetConstNullConstant();
			if(packet->GetColumn() == gameConstants.GetConstColumnOne())
			{
				tempAcrossDownLocation = gameConstants.GetConstColumnOne();
			}
			else if(packet->GetColumn() == gameConstants.GetConstColumnTwo())
			{
				tempAcrossDownLocation = gameConstants.GetConstColumnTwo();
			}
			else if(packet->GetColumn() == gameConstants.GetConstColumnThree())
			{
				tempAcrossDownLocation = gameConstants.GetConstColumnThree();
			}
			else if(packet->GetColumn() == gameConstants.GetConstColumnFour())
			{
				tempAcrossDownLocation = gameConstants.GetConstColumnFour();
			}
			else if(packet->GetColumn() == gameConstants.GetConstColumnFive())
			{
				tempAcrossDownLocation = gameConstants.GetConstColumnFive();
			}
			else   //column didn't match any column locations, an error has occured
			{
				if(packet->GetColumn() == gameConstants.GetConstNullConstant())
				{
					//Message stating minor error has occurred
					cout<<minorErrorMessage;
					cout<<columnDownErrorMessage;
					cout<<"The column variable shouldn't be a -1 when the winType is equal to a down.\nPlease check the column variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else //if column wasn't -1, then it must be -2, which means a fatal error has occured
				{
					//Message stating a fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<columnDownErrorMessage;
					cout<<"The column variable shouldn't be a -2 when the winType is equal to a down.\n";
					cout<<"Please check both the winType and column variables.\n";
					cout<<anyKey;
					_getche();
				}

				//End the game
				continueGame = false;
				return continueGame;
			}
		}
		else //win type didn't equal 1, 2, or 3, an error has occured
		{
			if(packet->GetWinType() == gameConstants.GetConstNullConstant())
			{
				//Message stating that minor error has occurred
				//Can't have a win and a winType with a nullConstant
				cout<<minorErrorMessage;
				cout<<winTypeErrorMessage;
				cout<<"The winType variable shouldn't be a -1 when a win exists.\nPlease check the winType variable!!\n";
				cout<<anyKey;
				_getche();
			}
			else
			{
				//Message stating that fatal error has occurred
				//Can't have a win and a winType with a fatal error
				cout<<fatalErrorMessage;
				cout<<winTypeErrorMessage;
				cout<<"The winType variable shouldn't be a -2 when a win exists.\n";
				cout<<"Please check both the win and winType variables.\n";
				cout<<anyKey;
				_getche();
			}

			//End the game
			continueGame = false;
			return continueGame;
		}
	}
	else //winDraw had a fatalError
	{
		cout<<fatalErrorMessage;
		cout<<winDrawErrorMessage;
		cout<<"The winDraw variable cannot equal -2. Double check the logic in the code, something isn't right!!!\n";
		cout<<anyKey;
		_getche();

		//End the game
		continueGame = false;
		return continueGame;
	}

	//Send temporary values to a display board function
	//TODO:
	//May need special board draw function for this, as this is a special case
	//Putting code in to process these values may make the original display function unnecessarily complicated
	
	return continueGame;
}