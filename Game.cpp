#include "Game.h"

//----Message Constants----
//Win/Draw Messages
const string Game::gameDrawMessage = "The game has ended in a draw.\nYou can now start a new round or end the game...\n";
const string Game::playerOneWinMessage = "Player 1 has won this round!!\nCongratulations!!!^o^\n";
const string Game::playerTwoWinMessage = "Player 2 has won this round!!\nCongratulations!!!^o^\n";
//WinDrawPacket Related Messages
const string Game::gameStateErrorMessage = "An error has occured with the winDraw variable in the packet.\nCheck packet code.\n";
const string Game::playerPieceErrorMessage = "An error has occured with the playerPiece variable in the packet.\nCheck packet code.\n";
const string Game::winTypeErrorMessage = "An error has occured with the winType variable in the packet.\nCheck packet code.\n";
const string Game::diagonalTypeErrorMessage = "An error has occured with the diagonalType variable in the packet.\nCheck packet code.\n";
const string Game::rowAcrossErrorMessage = "An error has occured with the rowAcross variable in the packet.\nCheck packet code.\n";
const string Game::columnDownErrorMessage = "An error has occured with the columnDown variable in the packet.\nCheck packet code.\n";
//Main Error Messages
const string Game::fatalErrorMessage = "A fatal error has occurred.\nThe game will now close.\n";
const string Game::minorErrorMessage = "A minor error has occurred.\nThe game will now close.\n";
const string Game::unknownErrorMessage = "An unknown error has occurred.\nThe game will now close.\n";
//Other Messages
const string Game::anyKey = "Press any key to continue...\n";

//----Constants Strings----
const string Game::noWinDrawState = "noWinDrawState";
const string Game::winState = "winState";
const string Game::drawState = "drawState";
const string Game::acrossWinType = "acrossWinType";
const string Game::downWinType = "downWinType";
const string Game::diagonalWinType = "diagonalWinType";
const string Game::diagonalLeftSubType = "diagonalLeftSubType";
const string Game::diagonalRightSubType = "diagonalRightSubType";
const string Game::noPlayerPiece = "noPlayerPiece";
const string Game::oPlayerPiece = "oPlayerPiece";
const string Game::xPlayerPiece = "xPlayerPiece";
const string Game::columnOne = "columnOne";
const string Game::columnTwo = "columnTwo";
const string Game::columnThree = "columnThree";
const string Game::columnFour = "columnFour";
const string Game::columnFive = "columnFive";
const string Game::rowOne = "rowOne";
const string Game::rowTwo = "rowTwo";
const string Game::rowThree = "rowThree";
const string Game::rowFour = "rowFour";
const string Game::rowFive = "rowFive";
const string Game::nullConstant = "nullConstant";
const string Game::fatalError = "fatalError";

Game::Game()
	: playerOne(), playerTwo(), board()
{
	//C++11 standard -- New array implamentation using the STL
	//Provides more information about the array
	array<const string, 23> constantsNames = {noWinDrawState, winState, drawState, acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType,
							   noPlayerPiece, oPlayerPiece, xPlayerPiece, columnOne, columnTwo, columnThree, columnFour, columnFive, rowOne, rowTwo, 
							   rowThree, rowFour, rowFive, nullConstant, fatalError};
	array<int, 23> constantsValues = {0, 1, 2, 1, 2, 3, 1, 2, 0, 1, 2, 10, 20, 30, 40, 50, 100, 200, 300, 400, 500, -1, -2};
	//Zero gamesPlayed
	roundsPlayed_ = 0;
	//Zero draws as no games have been played yet...
	gameDraws_ = 0;
	//Turn counter set to zero
	turnCounter_ = 0;

	//constantsList must be created before board and the 2 players are initialized becuase otherwise I'd be sending them a empty map container
	for(unsigned int i = 0; i < constantsValues.size(); i++)
	{
		constantsList.insert(pair<const string, int>(constantsNames[i], constantsValues[i]));
	}
	
	//Setup board
	board.SetupBoard(constantsList);
	//set bounds limit, basically players shouldn't be able to enter in values past this number
	//It's also the number used to determine if somebody won the game
	//The value is pulled from the board object
	boundsLimit_ = board.GetMultiplier();
	//Initializing each player
	playerOne.InitializePlayer(boundsLimit_, constantsList);
	playerTwo.InitializePlayer(boundsLimit_, constantsList);

	//First time game is starting so firstPlay is true
	firstPlay_ = true;

	gameFatalError_ = false;

	DecidePlayOrder();
}

void Game::StartGame()
{
	//First board was layed out when the board object was instantiated so all that's left
	//to do is to give the player some instructions
	if(firstPlay_ == true)
	{
		cout<<"Welcome to Tic-Tac-Toe!!!!!!!"<<endl;
		cout<<"Get "<<boundsLimit_<<" in a row to win."<<endl;
		cout<<"Each player will enter his/her choice into the prompt,\n";
		cout<<"your choice will then appear on the board and you will get a chance to\n";
		cout<<"enter in another choice."<<endl;
		cout<<"When somebody wins the game or the game is a draw, you can play another\n";
		cout<<"or, you can quit. The number of wins or draws that you rack up will be\n";
		cout<<"displayed as you play."<<endl;
		cout<<"Remember columns go down and are numbered 1 - "<<boundsLimit_<<" going from\n";
		cout<<"left to right. Rows go across and are number 1 - "<<boundsLimit_<<" going from\n";
		cout<<"top to bottom. So to put an X or O on the first square you would type in\n";
		cout<<"\"1,1\". Don't forget the comma you have to have that."<<endl;
		cout<<"The player who got Xs will go first, this is picked randomly each time a new game is played"<<endl;
		cout<<"Whenever you're ready we can start..."<<endl;
		cout<<"Press any key to continue..."<<endl;
		_getche();
		firstPlay_ = false;
	}
	
	//Set gamesPlayed to 1 as this is the first game, unless that was already the case.
	//When that happens roundsPlayed is incremented by 1
	if(roundsPlayed_ == 0)
		roundsPlayed_ = 1;
	else
		roundsPlayed_++;

	//Clear screen, display first play board
	system("cls");

	//Display the empty starting board
	board.DisplayBoard(roundsPlayed_, gameDraws_, playerOne, playerTwo);
	//Get the first round of player moves
	//Call GameLoop at this point
}

bool Game::GameLoop()
{
	const int playerOneTurn = 1;
	const int playerTwoTurn = 2;
	bool continueGame = true;
	
	if(playOrder_ == 1)
	{
		continueGame = GetPlayerMove(playerOneTurn);
		if(continueGame == false)
			return continueGame;
		
		continueGame = GetPlayerMove(playerTwoTurn);
		if(continueGame == false)
			return continueGame;
	}
	else
	{
		continueGame = GetPlayerMove(playerTwoTurn);
		if(continueGame == false)
			return continueGame;

		continueGame = GetPlayerMove(playerOneTurn);
		if(continueGame == false)
			return continueGame;
	}

	if(board.GetTotalNumOfPiecesOnBoard() >= boundsLimit_)
		continueGame = ProcessPacket(board.FindWinDraw());

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
	turnCounter_ = 0;
	firstPlay_ = false;
	playOrder_ = 0;
	//Reset the board first
	board.ResetBoard();
	
	//Then get multiplier from the board
	//This keeps problems with bounds issues popping up
	boundsLimit_ = board.GetMultiplier();

	//Call this before ResetPlayer or bad things will happen
	playerOne.ResetPlayerPiece();

	//Reset both players
	playerOne.ResetPlayer(boundsLimit_);
	playerTwo.ResetPlayer(boundsLimit_);

	DecidePlayOrder();
}

bool Game::GetPlayerMove(int order)
{
	const int quit = 0;
	bool continuePlay = true;

	if(order == 1)
	{
		int playerOneMove;
		bool playerOneGood = false;
		while(playerOneGood == false)
		{
			system("cls");
			board.DisplayBoard(roundsPlayed_, gameDraws_, playerOne, playerTwo);
			playerOneMove = playerOne.MakeMove();
			if(playerOneMove == quit)
			{
				continuePlay = false;
				return continuePlay;
			}
			
			if(board.UpdateBoard(playerOne.GetPiece(), playerOneMove, playerOne.HasPlayerMadeMove(), playerTwo.HasPlayerMadeMove()) == false)
			{
				if(board.GetFatalError() == true)
				{
					cout<<"Now exiting the program.\n";
					cout<<"There has been a fatal error...\n";
					cout<<"Press any key to continue...\n"<<endl;
					_getche();
					continuePlay = false;
					gameFatalError_ = true;
					return continuePlay;
				}
				else
				{
					cout<<"Please re-enter your choice.\n";
					cout<<anyKey<<endl;
					_getche();
				}
			}
			else
				playerOneGood = true;
		}
	}
	else
	{
		int playerTwoMove;
		bool playerTwoGood = false;
		while(playerTwoGood == false)
		{
			system("cls");
			board.DisplayBoard(roundsPlayed_, gameDraws_, playerOne, playerTwo);
			playerTwoMove = playerTwo.MakeMove();
			if(playerTwoMove == quit)
			{
				continuePlay = false;
				return continuePlay;
			}
			
			if(board.UpdateBoard(playerTwo.GetPiece(), playerTwoMove, playerOne.HasPlayerMadeMove(), playerTwo.HasPlayerMadeMove()) == false)
			{
				if(board.GetFatalError() == true)
				{
					cout<<"Now exiting the program.\n";
					cout<<"There has been a fatal error...\n";
					cout<<"Press any key to continue...\n"<<endl;
					_getche();
					continuePlay = false;
					gameFatalError_ = true;
					return continuePlay;
				}
				else
				{
					cout<<"Please re-enter your choice.\n";
					cout<<anyKey<<endl;
					_getche();
				}
			}
			else
				playerTwoGood = true;
		}
	}

	return continuePlay;
}

bool Game::ProcessPacket(WDPacketPtr packet)
{
	bool continueGame = true;
	int tempType;
	int tempDiagonalLocation;
	int tempAcrossDownLocation;

	//Value from packet
	const int t_gameState = packet->GetWinDraw();
	
	//Error Values
	const int t_nullConstant = GetConstantFromList(nullConstant);
	const int t_fatalError = GetConstantFromList(fatalError);
	
	//Values from the map list to be compared against t_gameState
	const int t_noWinDrawState = GetConstantFromList(noWinDrawState);
	const int t_drawState = GetConstantFromList(drawState);
	const int t_winState = GetConstantFromList(winState);

	if(t_gameState == t_noWinDrawState || t_gameState == t_drawState)
	{
		if(t_gameState == t_drawState)
		{
			gameDraws_++;
			//put message indicating that a draw has occurred and a new game is starting
			cout<<gameDrawMessage;
			cout<<anyKey;
			_getche();
			continueGame = false;
			return continueGame;
		}
		else
			return continueGame;
	}
	else if(t_gameState == t_winState)
	{
		continueGame = false;
		//Get player piece and compare, update their winCounter
		if(packet->GetPlayerPiece() == playerOne.GetPiece())
		{
			playerOne.UpdateScore();
			playerOne.SetPlayerWon();
			//Message telling that player 1 has won the game
			cout<<playerOneWinMessage;
			playerOne.DisplayScore();
			cout<<anyKey;
			_getche();
		}
		else if(packet->GetPlayerPiece() == playerTwo.GetPiece())
		{
			playerTwo.UpdateScore();
			playerTwo.SetPlayerWon();
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

		//Value pulled from packet to be compared, in this case the type of win that occurred
		const int t_winType = packet->GetWinType();
		
		//Values pulled from map list that will be compared against the winType to figure out what it is
		const int t_diagonalWinType = GetConstantFromList(diagonalWinType);
		const int t_acrossWinType = GetConstantFromList(acrossWinType);
		const int t_downWinType = GetConstantFromList(downWinType);
		
		//Find out where player won, store values in temp variables and send to DisplayBoard function
		if(t_winType == t_diagonalWinType)
		{
			//The type of win is a diagonal type, entering that into the tempType variable here
			tempType = t_diagonalWinType;
			
			//Value pulled from packet to be compared, in this case the type of diagonal win
			const int t_winningDiagLocation = packet->GetDiagType();
			
			//Values pulled from the map list to be compared to the t_winningDiagLocation
			const int t_diagonalLeftSubType = GetConstantFromList(diagonalLeftSubType);
			const int t_diagonalRightSubType = GetConstantFromList(diagonalRightSubType);

			if(t_winningDiagLocation == t_diagonalLeftSubType)
				tempDiagonalLocation = t_diagonalLeftSubType;
			else if(t_winningDiagLocation == t_diagonalRightSubType)
				tempDiagonalLocation = t_diagonalRightSubType;
			else //diagType didn't equal 1 or 2 even though the winning move was a diagonal, this is an error
			{	
				if(t_winningDiagLocation == t_nullConstant)
				{
					//Message stating a minor error has occurred and the code should be checked out
					cout<<minorErrorMessage;
					cout<<diagonalTypeErrorMessage;
					//Special message because of the 2 errors that can occur here
					cout<<"The diagonalType variable shouldn't be a -1 when the winType variable is equal to a diagonal.\nPlease check the diagonalType variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else if(t_winningDiagLocation == t_fatalError)
				{
					//Message stating the a fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<diagonalTypeErrorMessage;
					cout<<"The diagonalType variable shouldn't be a -2 when winType variable is equal to a diagonal.\n";
					cout<<"Please check both the winType and diagonalType variables.\n";
					cout<<anyKey;
					_getche();
				}
				else
				{
					//Message stating that an unknown error has occured
					cout<<unknownErrorMessage;
					cout<<diagonalTypeErrorMessage;
					cout<<"The diagonalType variable had an unexpected output.\n";
					cout<<"The number associated with the variable was "<<t_winningDiagLocation<<".\n";
					cout<<"Please look into this right away!\n";
					cout<<anyKey;
					_getche();
				}

				//Both errors will result in the game closing
				continueGame = false;
				gameFatalError_ = true;
				return continueGame;
			}
		}
		else if(t_winType == t_acrossWinType)
		{
			tempType = t_acrossWinType;
			tempDiagonalLocation = t_nullConstant;

			//Value pulled from packet to be compared, in this case it's the row where a win was located
			const int t_winningAcrossLocation = packet->GetRow();
			
			//Values pulled from the map list to be compared with the variable t_winningRowLocation
			const int t_rowOne = GetConstantFromList(rowOne);
			const int t_rowTwo = GetConstantFromList(rowTwo);
			const int t_rowThree = GetConstantFromList(rowThree);
			const int t_rowFour = GetConstantFromList(rowFour);
			const int t_rowFive = GetConstantFromList(rowFive);

			if(t_winningAcrossLocation == t_rowOne)
				tempAcrossDownLocation = t_rowOne;
			else if(t_winningAcrossLocation == t_rowTwo)
				tempAcrossDownLocation = t_rowTwo;
			else if(t_winningAcrossLocation == t_rowThree)
				tempAcrossDownLocation = t_rowThree;
			else if(t_winningAcrossLocation == t_rowFour)
				tempAcrossDownLocation = t_rowFour;
			else if(t_winningAcrossLocation == t_rowFive)
				tempAcrossDownLocation = t_rowFive;
			else //the row didn't match any of the row locations, an error has occurred
			{
				if(t_winningAcrossLocation == t_nullConstant)
				{
					//Message stating minor error has occurred
					cout<<minorErrorMessage;
					cout<<rowAcrossErrorMessage;
					cout<<"The row variable shouldn't be a -1 when the winType variable is equal to an across.\nPlease check the row variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else if(t_winningAcrossLocation == t_fatalError) 
				{
					//Message stating fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<rowAcrossErrorMessage;
					cout<<"The row variable shouldn't be a -2 when the winType is equal to an across.\n";
					cout<<"Please check both the winType and row variables.\n";
					cout<<anyKey;
					_getche();
				}
				else
				{
					//Message stating that an unknown error has occured
					cout<<unknownErrorMessage;
					cout<<rowAcrossErrorMessage;
					cout<<"The row variable had an unexpected output.\n";
					cout<<"The number associated with the variable was "<<t_winningAcrossLocation<<".\n";
					cout<<"Please look into this right away!\n";
					cout<<anyKey;
					_getche();
				}

				//End the game
				continueGame = false;
				gameFatalError_ = true;
				return continueGame;
			}
		}
		else if(t_winType == t_downWinType)
		{
			tempType = t_downWinType;
			tempDiagonalLocation = t_nullConstant;

			//Value pulled from packet to be compared, in this case it's the column where a win was located
			const int t_winningDownLocation = packet->GetColumn();

			//Values pulled from the map list to be compared with the variable t_winningDownLocation
			const int t_columnOne = GetConstantFromList(columnOne);
			const int t_columnTwo = GetConstantFromList(columnTwo);
			const int t_columnThree = GetConstantFromList(columnThree);
			const int t_columnFour = GetConstantFromList(columnFour);
			const int t_columnFive = GetConstantFromList(columnFive);

			if(t_winningDownLocation == t_columnOne)
				tempAcrossDownLocation = t_columnOne;
			else if(t_winningDownLocation == t_columnTwo)
				tempAcrossDownLocation = t_columnTwo;
			else if(t_winningDownLocation == t_columnThree)
				tempAcrossDownLocation = t_columnThree;
			else if(t_winningDownLocation == t_columnFour)
				tempAcrossDownLocation = t_columnFour;
			else if(t_winningDownLocation == t_columnFive)
				tempAcrossDownLocation = t_columnFive;
			else   //column didn't match any column locations, an error has occured
			{
				if(t_winningDownLocation == t_nullConstant)
				{
					//Message stating minor error has occurred
					cout<<minorErrorMessage;
					cout<<columnDownErrorMessage;
					cout<<"The column variable shouldn't be a -1 when the winType is equal to a down.\nPlease check the column variable!!\n";
					cout<<anyKey;
					_getche();
				}
				else if(t_winningDownLocation == t_fatalError)
				{
					//Message stating a fatal error has occurred
					cout<<fatalErrorMessage;
					cout<<columnDownErrorMessage;
					cout<<"The column variable shouldn't be a -2 when the winType is equal to a down.\n";
					cout<<"Please check both the winType and column variables.\n";
					cout<<anyKey;
					_getche();
				}
				else
				{
					//Message stating that an unknown error has occured
					cout<<unknownErrorMessage;
					cout<<columnDownErrorMessage;
					cout<<"The column variable had an unexpected output.\n";
					cout<<"The number associated with the variable was "<<t_winningDownLocation<<".\n";
					cout<<"Please look into this right away!\n";
					cout<<anyKey;
					_getche();
				}

				//End the game
				continueGame = false;
				gameFatalError_ = true;
				return continueGame;
			}
		}
		else //win type didn't equal 1, 2, or 3, an error has occured
		{
			if(t_winType == t_nullConstant)
			{
				//Message stating that minor error has occurred
				//Can't have a win and a winType with a nullConstant
				cout<<minorErrorMessage;
				cout<<winTypeErrorMessage;
				cout<<"The winType variable shouldn't be a -1 when a win exists.\nPlease check the winType variable!!\n";
				cout<<anyKey;
				_getche();
			}
			else if(t_winType == t_fatalError)
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
			else
			{
				//Message stating that unknown error has occurred
				cout<<unknownErrorMessage;
				cout<<winTypeErrorMessage;
				cout<<"The winType definitly shouldn't be a unknown error.\nPlease double check code for serious errors!!\n";
				cout<<anyKey;
				_getche();
			}

			//End the game
			continueGame = false;
			gameFatalError_ = true;
			return continueGame;
		}
	}
	else if(t_gameState == t_fatalError)
	{
		cout<<fatalErrorMessage;
		cout<<gameStateErrorMessage;
		//Change winDraw in this sentence to gameState once all the other changes have been made
		cout<<"The winDraw variable cannot equal -2. Double check the logic in the code, something isn't right!!!\n";
		cout<<anyKey;
		_getche();

		//End the game
		continueGame = false;
		gameFatalError_ = true;
		return continueGame;
	}
	else
	{
		cout<<unknownErrorMessage;
		cout<<gameStateErrorMessage;
		//Change winDraw in this sentence to gameState once all the other changes have been made
		cout<<"The winDraw variable has an unknown error value.\nThere is a major problem in the code that needs attention!!\n";
		cout<<"Check the functions related to the creation of the packet in the WinDrawPAcket class,\n";
		cout<<"as well as the functions related to packet creation and finding the win, draw, or neither right a way.\n";
		cout<<anyKey;
		_getche();

		//End the game
		continueGame = false;
		gameFatalError_ = true;
		return continueGame;
	}

	if(playerOne.DidPlayerWin() == true || playerTwo.DidPlayerWin() == true)
		board.DisplayWinningBoard(tempType, tempDiagonalLocation, tempAcrossDownLocation, playerOne, playerTwo);

	return continueGame;
}

void Game::DecidePlayOrder()
{
	//Figure out play order
	if(playerOne.GetPiece() == 2)
		playOrder_ = 1;
	else
		playOrder_ = 2;
}

int Game::GetConstantFromList(string request)
{
	ConstListIters_C constListIter;
	constListIter = constantsList.find(request);
	int t_request = constListIter->second;

	return t_request;
}

const bool Game::HasGameHadFatalError() const
{
	return gameFatalError_;
}