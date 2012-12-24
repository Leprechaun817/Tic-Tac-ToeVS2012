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

#include "Game.h"

//----Message Constants----
//Win/Draw Messages
const std::string Game::gameDrawMessage = "The game has ended in a draw.\nYou can now start a new round or end the game...\n";
const std::string Game::playerOneWinMessage = "Player 1 has won this round!!\nCongratulations!!!^o^\n";
const std::string Game::playerTwoWinMessage = "Player 2 has won this round!!\nCongratulations!!!^o^\n";

//----Other Messages----
const std::string Game::anyKey = "Press any key to continue...\n";

//----Constants Strings----
const std::string Game::noWinDrawState = "noWinDrawState";
const std::string Game::winState = "winState";
const std::string Game::drawState = "drawState";
const std::string Game::acrossWinType = "acrossWinType";
const std::string Game::downWinType = "downWinType";
const std::string Game::diagonalWinType = "diagonalWinType";
const std::string Game::diagonalLeftSubType = "diagonalLeftSubType";
const std::string Game::diagonalRightSubType = "diagonalRightSubType";
const std::string Game::noPlayerPiece = "noPlayerPiece";
const std::string Game::oPlayerPiece = "oPlayerPiece";
const std::string Game::xPlayerPiece = "xPlayerPiece";
const std::string Game::columnOne = "columnOne";
const std::string Game::columnTwo = "columnTwo";
const std::string Game::columnThree = "columnThree";
const std::string Game::columnFour = "columnFour";
const std::string Game::columnFive = "columnFive";
const std::string Game::rowOne = "rowOne";
const std::string Game::rowTwo = "rowTwo";
const std::string Game::rowThree = "rowThree";
const std::string Game::rowFour = "rowFour";
const std::string Game::rowFive = "rowFive";
const std::string Game::nullConstant = "nullConstant";
const std::string Game::fatalError = "fatalError";

//Constants for sounds
const std::string Game::playerOneWinSound = "playerOneWinSound";
const std::string Game::playerTwoWinSound = "playerTwoWinSound";
const std::string Game::gameOverSound = "gameOverSound";
const std::string Game::pieceClickSound = "pieceClickSound";
const std::string Game::badMoveErrorSound = "badMoveErrorSound";
const std::string Game::fatalErrorSound = "fatalErrorSound";
const std::string Game::clickSound = "clickSound";
const std::string Game::endOfGameSound = "endOfGameSound";
const std::string Game::minorErrorSound = "minorErrorSound";

Game::Game() throw()
	: playerOne_(), playerTwo_(), board_(), roundsPlayed_(0), gameDraws_(0), turnCounter_(0), firstPlay_(true)
{
	std::array<const std::string, 23> constantsNames = {noWinDrawState, winState, drawState, acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType,
							   noPlayerPiece, oPlayerPiece, xPlayerPiece, columnOne, columnTwo, columnThree, columnFour, columnFive, rowOne, rowTwo, 
							   rowThree, rowFour, rowFive, nullConstant, fatalError};
	std::array<int, 23> constantsValues = {0, 1, 2, 1, 2, 3, 1, 2, 0, 1, 2, 10, 20, 30, 40, 50, 100, 200, 300, 400, 500, -1, -2};
	
	//constantsList must be created before board and the 2 players are initialized becuase otherwise I'd be sending them a empty map container
	for(unsigned int i = 0; i < constantsValues.size(); i++)
		constantsList.insert(std::pair<const std::string, int>(constantsNames[i], constantsValues[i]));

	//Initialize the sound engine ptr
	SoundEngine::InitPtr();

	//Set titile of window
	SetConsoleTitle((TCHAR*)"Tic-Tac-Toe");

	//Get console handle
	hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
	hWnd_ = FindWindow(NULL, (TCHAR*)"Tic-Tac-Toe");
}

//TODO:
//Rewrite the introduction in this function to include a diagram of the board and coordinates to make
//it a little easier to undertand for people...
void Game::StartGame()
{
	if(firstPlay_) {
		//Initialize the sound first before anything else is done
		SoundEngine::GetInstance()->InitializeSoundEngine();
		
		SetGameFullscreen();

		//Display all legal notices before anyone is allowed to play the game
		DisplayNotices();

		//Setup board
		board_.SetupBoard(constantsList);
	
		//set bounds limit, basically players shouldn't be able to enter in values past this number
		//It's also the number used to determine if somebody won the game
		//The value is pulled from the board object
		boundsLimit_ = board_.GetMultiplier();
	
		//Initializing each player
		playerOne_.InitializePlayer(boundsLimit_);
		playerTwo_.InitializePlayer(boundsLimit_);

		DecidePlayOrder();
		
		system("cls");
		DisplayGameInstructions();

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
	board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
}

bool Game::GameLoop()
{
	const int playerOneTurn = 1, playerTwoTurn = 2;
	int totalPiecesOnBoard = board_.GetTotalNumOfPiecesOnBoard();
	int boundsLimitTest = boundsLimit_ - 1;
	bool continueGame = true;
	
	if(playOrder_ == playerOneTurn) {
		continueGame = GetPlayerMove(playerOneTurn);
		if(!continueGame)
			return continueGame;
		else {
			if(totalPiecesOnBoard > boundsLimitTest) {
				continueGame = CheckGameState(board_.GetGameState());
				return continueGame;
			}
		}

		continueGame = GetPlayerMove(playerTwoTurn);
		if(!continueGame)
			return continueGame;
		else {
			if(totalPiecesOnBoard > boundsLimitTest) {
				continueGame = CheckGameState(board_.GetGameState());
				return continueGame;
			}
		}
	}
	else {
		continueGame = GetPlayerMove(playerTwoTurn);
		if(!continueGame)
			return continueGame;
		else {
			if(totalPiecesOnBoard > boundsLimitTest) {
				continueGame = CheckGameState(board_.GetGameState());
				return continueGame;
			}
		}

		continueGame = GetPlayerMove(playerOneTurn);
		if(!continueGame)
			return continueGame;
		else {
			if(totalPiecesOnBoard > boundsLimitTest) {
				continueGame = CheckGameState(board_.GetGameState());
				return continueGame;
			}
		}
	}
	
	return continueGame;
}

bool Game::EndGame()
{
	char answer;

	//Clear the screen
	system("cls");

	SoundEngine::GetInstance()->PlaySoundFromQueue(gameOverSound);

	DisplayLastRoundStats();
	//Ask player/s whether they want to play another round
	bool quitGame;
	bool loop = false;
	while(!loop) {
		//Play game over noise here
		std::cout<<"Would you like to play for another round? y or n"<<std::endl;
		std::cin>>answer;

		if(answer == 'Y' || answer == 'y') {
			//Player wants to go for another round
			loop = true;
			quitGame = false;
		}				  
		else if(answer == 'N' || answer == 'n') {
			//Player does want to go for another round
			loop = true;
			quitGame = true;
		}				 
		else {
			SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
			std::cout<<"Please enter y or n"<<std::endl;
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
			system("cls");
		}
	}

	return quitGame;
}

void Game::ResetGame()
{
	//Game object specific stuff
	turnCounter_ = playOrder_ = 0;
	firstPlay_ = false;
	//Reset the board first
	board_.ResetBoard();
	
	//Then get multiplier from the board
	//This keeps problems with bounds issues popping up
	boundsLimit_ = board_.GetMultiplier();

	try {
		//Call this before ResetPlayer or bad things will happen
		playerOne_.ResetPlayerPiece();
	}
	catch(Exception &e) {
		std::cout<<e.what()<<"\n";
		std::cout<<"DEBUG ERROR - If you see this something is wrong with the code!!!\n";
		std::cout<<"Press any key to continue..."<<std::endl;
		_getche();
	}

	//Reset both players
	playerOne_.ResetPlayer(boundsLimit_);
	playerTwo_.ResetPlayer(boundsLimit_);

	DecidePlayOrder();
}

bool Game::GetPlayerMove(int order)
{
	const int t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	bool continuePlay = true;

	if(order == 1) {
		bool playerOneContinueGame;
		bool playerOneGood = false;
		while(!playerOneGood) {	
			try {
				system("cls");
				board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
				playerOneContinueGame = playerOne_.MakeMove();
				SoundEngine::GetInstance()->PlaySoundFromQueue(pieceClickSound);
				if(!playerOneContinueGame) {
					continuePlay = false;
					playerOneGood = true;
				}
				else {
					playerOneGood = board_.UpdateBoard(playerOne_.GetPiece(), playerOne_.GetMove(), playerOne_.HasPlayerMadeMove(), playerTwo_.HasPlayerMadeMove());
					system("cls");
					board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
					if(playerOne_.GetPiece() == t_xPlayerPiece)
						board_.UpdateXs();
					else
						board_.UpdateOs();
				}
			}
			catch(Exception &e) {
				if(e.GetErrorType() == err.Move_Out_Of_Bounds || e.GetErrorType() == err.Piece_Exists_At_Location) {
					SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
					std::cout<<e.what()<<"\n";
					std::cout<<"Please re-enter your choice.\n";
					std::cout<<anyKey<<std::endl;
					_getche();
				}
				else
					throw;
			}
		}
	}
	else {
		bool playerTwoContinueGame;
		bool playerTwoGood = false;
		while(!playerTwoGood) {
			try {
				system("cls");
				board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
				playerTwoContinueGame = playerTwo_.MakeMove();
				SoundEngine::GetInstance()->PlaySoundFromQueue(pieceClickSound);
				if(!playerTwoContinueGame) {
					continuePlay = false;
					playerTwoGood = true;
				}
				else {
					playerTwoGood = board_.UpdateBoard(playerTwo_.GetPiece(), playerTwo_.GetMove(), playerOne_.HasPlayerMadeMove(), playerTwo_.HasPlayerMadeMove());
					system("cls");
					board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
					if(playerTwo_.GetPiece() == t_xPlayerPiece)
						board_.UpdateXs();
					else
						board_.UpdateOs();
				}
			}
			catch(Exception &e) {
				if(e.GetErrorType() == err.Move_Out_Of_Bounds || e.GetErrorType() == err.Piece_Exists_At_Location) {
					SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
					std::cout<<e.what()<<"\n";
					std::cout<<"Please re-enter your choice.\n";
					std::cout<<anyKey<<std::endl;
					_getche();
				}
				else
					throw;
			}
		}
	}

	return continuePlay;
}

bool Game::CheckGameState(WDPacketPtr packet)
{
	bool continueGame = true;
	int tempType = GetConstantFromList(fatalError), tempDiagonalLocation = GetConstantFromList(fatalError), tempAcrossDownLocation = GetConstantFromList(fatalError);

	//Error Values
	const int t_nullConstant = GetConstantFromList(nullConstant);
	const int t_fatalError = GetConstantFromList(fatalError);
	
	//Values from the map list to be compared against t_gameState
	const int t_noWinDrawState = GetConstantFromList(noWinDrawState), t_drawState = GetConstantFromList(drawState), t_winState = GetConstantFromList(winState);

	int t_gameState = packet->GetGameState();
	if(t_gameState == t_noWinDrawState || t_gameState == t_drawState) {
		if(t_gameState == t_drawState) {
			gameDraws_++;
			std::cout<<gameDrawMessage;
			std::cout<<anyKey;
			_getche();
			continueGame = false;
			return continueGame;
		}
		else
			return continueGame;
	}
	else if(t_gameState == t_winState) {
		continueGame = false;
		//Get player piece and compare, update their winCounter
		if(packet->GetPlayerPiece() == playerOne_.GetPiece()) {
			playerOne_.UpdateScore();
			playerOne_.SetPlayerWon();
			SoundEngine::GetInstance()->PlaySoundFromQueue(playerOneWinSound);
			std::cout<<"\n"<<playerOneWinMessage;
			playerOne_.DisplayScore();
			std::cout<<"\n"<<anyKey;
			_getche();
		}
		else if(packet->GetPlayerPiece() == playerTwo_.GetPiece()) {
			playerTwo_.UpdateScore();
			playerTwo_.SetPlayerWon();
			SoundEngine::GetInstance()->PlaySoundFromQueue(playerTwoWinSound);
			std::cout<<"\n"<<playerTwoWinMessage;
			playerTwo_.DisplayScore();
			std::cout<<"\n"<<anyKey;
			_getche();
		}
		else
			throw Exception(err.Bad_PlayerPiece_Variable_Fatal);

		//Values pulled from map list that will be compared against the winType to figure out what it is
		const int t_diagonalWinType = GetConstantFromList(diagonalWinType), t_acrossWinType = GetConstantFromList(acrossWinType), t_downWinType = GetConstantFromList(downWinType);
		
		int t_winType = packet->GetWinType();
		//Find out where player won, store values in temp variables and send to DisplayBoard function
		if(t_winType == t_diagonalWinType) {
			//The type of win is a diagonal type, entering that into the tempType variable here
			tempType = t_diagonalWinType;
			
			//Values pulled from the map list to be compared to the t_winningDiagLocation
			const int t_diagonalLeftSubType = GetConstantFromList(diagonalLeftSubType), t_diagonalRightSubType = GetConstantFromList(diagonalRightSubType);

			int t_winningDiagLocation = packet->GetDiagType();
			if(t_winningDiagLocation == t_diagonalLeftSubType)
				tempDiagonalLocation = t_diagonalLeftSubType;
			else if(t_winningDiagLocation == t_diagonalRightSubType)
				tempDiagonalLocation = t_diagonalRightSubType;
			//diagType didn't equal 1 or 2 even though the winning move was a diagonal, this is an error
			else {	
				if(t_winningDiagLocation == t_nullConstant)
					throw Exception(err.Bad_DiagonalLocation_Minor);
				else if(t_winningDiagLocation == t_fatalError)
					throw Exception(err.Bad_DiagonalLocation_Fatal);
				else
					throw Exception(err.Bad_DiagonalLocation_Unknown);
			}
		}
		else if(t_winType == t_acrossWinType) {
			tempType = t_acrossWinType;
			tempDiagonalLocation = t_nullConstant;

			//Values pulled from the map list to be compared with the variable t_winningRowLocation
			const int t_rowOne = GetConstantFromList(rowOne), t_rowTwo = GetConstantFromList(rowTwo), t_rowThree = GetConstantFromList(rowThree), t_rowFour = GetConstantFromList(rowFour),
					  t_rowFive = GetConstantFromList(rowFive);

			int t_winningAcrossLocation = packet->GetRow();
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
			//the row didn't match any of the row locations, an error has occurred
			else {
				if(t_winningAcrossLocation == t_nullConstant)
					throw Exception(err.Bad_AcrossLocation_Minor);
				else if(t_winningAcrossLocation == t_fatalError)
					throw Exception(err.Bad_AcrossLocation_Fatal);
				else
					throw Exception(err.Bad_AcrossLocation_Unknown);
			}
		}
		else if(t_winType == t_downWinType) {
			tempType = t_downWinType;
			tempDiagonalLocation = t_nullConstant;

			//Values pulled from the map list to be compared with the variable t_winningDownLocation
			const int t_columnOne = GetConstantFromList(columnOne), t_columnTwo = GetConstantFromList(columnTwo), t_columnThree = GetConstantFromList(columnThree), 
					  t_columnFour = GetConstantFromList(columnFour), t_columnFive = GetConstantFromList(columnFive);

			int t_winningDownLocation = packet->GetColumn();
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
			//column didn't match any column locations, an error has occured
			else {
				if(t_winningDownLocation == t_nullConstant)
					throw Exception(err.Bad_DownLocation_Minor);
				else if(t_winningDownLocation == t_fatalError)
					throw Exception(err.Bad_DownLocation_Fatal);
				else
					throw Exception(err.Bad_DownLocation_Unknown);
			}
		}
		//win type didn't equal 1, 2, or 3, an error has occured
		else {
			if(t_winType == t_nullConstant)
				throw Exception(err.Bad_WinType_Variable_Minor);
			else if(t_winType == t_fatalError)
				throw Exception(err.Bad_WinType_Variable_Fatal);
			else
				throw Exception(err.Bad_WinType_Variable_Unknown);
		}
	}
	else if(t_gameState == t_fatalError)
		throw Exception(err.Bad_GameState_Fatal);
	else
		throw Exception(err.Bad_GameState_Unknown);

	if((playerOne_.DidPlayerWin()) || (playerTwo_.DidPlayerWin()))
		board_.DisplayWinningBoard(tempType, tempDiagonalLocation, tempAcrossDownLocation, playerOne_, playerTwo_);
		
	return continueGame;
}

void Game::DecidePlayOrder()
{
	if(playerOne_.GetPiece() == 2)
		playOrder_ = 1;
	else
		playOrder_ = 2;
}

void Game::DisplayFinalStats()
{
	std::cout<<"Player 1's name: "<<playerOne_.GetName()<<"\n";
	std::cout<<playerOne_.GetName()<<"\'s final score is: "<<playerOne_.GetScore()<<"\n\n";
	std::cout<<"Player 2's name: "<<playerTwo_.GetName()<<"\n";
	std::cout<<playerTwo_.GetName()<<"\'s final score is: "<<playerTwo_.GetScore()<<"\n\n";
	std::cout<<"There were a total of "<<roundsPlayed_<<" round\\s played and\n";
	std::cout<<"there were a total of "<<gameDraws_<<" draws during the game."<<std::endl;
}

void Game::DisplayLastRoundStats()
{
	std::cout<<"Player 1's name: "<<playerOne_.GetName()<<"\n";
	std::cout<<playerOne_.GetName()<<"\'s final score is: "<<playerOne_.GetScore()<<"\n\n";
	std::cout<<"Player 2's name: "<<playerTwo_.GetName()<<"\n";
	std::cout<<playerTwo_.GetName()<<"\'s final score is: "<<playerTwo_.GetScore()<<"\n\n";
	std::cout<<"There were a total of "<<turnCounter_<<" turns taken last round\n";
	std::cout<<"You have both played "<<roundsPlayed_<<" round\\s so far in this game\n";
	std::cout<<"and there have been a total of "<<gameDraws_<<" draw\\s so far in this game"<<std::endl;
}

int Game::GetConstantFromList(std::string request) const
{
	int returnValue = -5;
	for(const auto &i : constantsList)
		if((i.first) == request) {
			returnValue = (i.second);
			break;
		}

	if(returnValue == -5) {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Unknown_Constant_Error);
	}
	return returnValue;
}

void Game::DisplayGameInstructions()
{
	std::cout<<"Welcome to Tic-Tac-Toe!!!!!!!"<<std::endl;
	std::cout<<"Get "<<boundsLimit_<<" in a row going across, down or diagonally to win."<<std::endl;
	std::cout<<"When somebody wins the game or the game is a draw, you can play another round\n";
	std::cout<<"or, you can quit.\n\n";
	std::cout<<"The board looks something like this:\n";
	board_.DisplaySampleBoard();
	std::cout<<"The columns going across are numbered 1 to "<<boundsLimit_<<" going from left to right and\n";
	std::cout<<"The rows going down are numbered 1 to "<<boundsLimit_<<" going from top to bottom.\n";
	std::cout<<"To enter in a choice just type the number of the row first and then the column number seperated by a comma.\n";
	std::cout<<"Ex: 1,1\n\n";
	std::cout<<"The player who got Xs will go first and this is picked randomly each time a new game is played"<<std::endl;
	std::cout<<"Whenever you're ready we can start..."<<std::endl;
	std::cout<<"Press any key to continue..."<<std::endl;
	_getche();
	SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
}

void Game::DisplayNotices()
{
	const std::string acceptance = "I AGREE";
	const std::string nonacceptance = "I DISAGREE";
	const std::string showWarranty = "SHOW W";
	const std::string showCopyright = "SHOW C";
	
	char warrantyNotice = 'w';
	char copyrightNotice = 'c';
	
	bool loop = true;
	while(loop) {
		std::string choice;
		system("cls");
		std::cout<<"Aaron's Tic-Tac-Toe Clone\t-\tCOPYRIGHT 2012 Aaron Gagern\n";
		std::cout<<"This program comes with ABSOLUTELY NO WARRANTY\n";
		std::cout<<"This is free software, and you are welcome to redistribute it\n";
		std::cout<<"under certain conditions\n\n";
		std::cout<<"For more details on the warranty, type SHOW W\n";
		std::cout<<"To see the GPLv3 license, type SHOW C\n";
		std::cout<<"If you accept this license, please type I AGREE\n";
		std::cout<<"If you don't wish to do this type, I DISAGREE\n";
		std::cout<<"The program will then exit.\n";
		std::cout<<"Please type your choice below."<<std::endl;
		std::getline(std::cin, choice);
		SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);

		if(choice == acceptance)
			loop = false;
		else if(choice == nonacceptance)
			throw Exception(err.NonAcceptance_Of_Notices);
		else if(choice == showWarranty)
			DisplayNoticeFile(warrantyNotice);
		else if(choice == showCopyright)
			DisplayNoticeFile(copyrightNotice);
		else {
			SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
			std::cout<<"You choice didn't match any of the available choices.\n";
			std::cout<<"Please try again.\n";
			std::cout<<"Press any key to continue..."<<std::endl;
			_getche();
			SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);
		}
	}
}

void Game::DisplayNoticeFile(char noticeType)
{
	std::string line;
	int lineStop = 0;
	
	std::ifstream f;
	if(noticeType == 'w') {
		f.open("WARRANTY.txt", std::ios::in);
		lineStop = 10;
	}
	if(noticeType == 'c') {
		f.open("COPYING.txt", std::ios::in);
		lineStop = 20;
	}

	if((!f.is_open()) || (!f.good()))
		throw Exception(err.Fatal_Error, "Could not find the notice,\nor notice files have been corrupted.");

	int lineCount = 0;
	while(!f.eof()) {
		getline(f, line);
		std::cout<<line;
		lineCount++;

		bool loop = true;
		bool quit = false;
		if((lineCount % lineStop) == 0) {
			while(loop) {
				char choice;
				std::cout<<"\n\n\nTo continue reading this notice, type c and press enter.\n";
				std::cout<<"To stop reading this and go back, type q and press enter.\n";
				std::cin>>choice;
				SoundEngine::GetInstance()->PlaySoundFromQueue(clickSound);

				if(choice == 'c' || choice == 'C') {
					loop = false;
					std::cout<<"\n\n";
				}
				else if(choice == 'q' || choice == 'Q') {
					loop = false;
					quit = true;
				}
				else {
					SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
					std::cout<<"\n\nPlease enter in your choice again.\n";
				}
			}
		}

		if(!loop && quit)
			break;
	}

	//Close the file
	f.close();

	std::cout<<"Press any key to continue..."<<std::endl;
	_getche();

	//Remove any remaining junk from cin stream
	std::cin.clear();
	std::cin.ignore(1000, '\n');
}

void Game::SetGameFullscreen()
{
	hWnd_ = FindWindow(NULL, (TCHAR*)"Tic-Tac-Toe");
	COORD NewWindowSize = GetLargestConsoleWindowSize(hConsole_);
	SMALL_RECT DisplayArea = {0, 0, 0, 0};

	SetConsoleScreenBufferSize(hConsole_, NewWindowSize);

	DisplayArea.Right = (NewWindowSize.X - 1);
	DisplayArea.Bottom = (NewWindowSize.Y - 1);

	SetConsoleWindowInfo(hConsole_, TRUE, &DisplayArea);

	ShowWindow(hWnd_, SW_MAXIMIZE);
}

//TODO:
//Finish this later. Will look very similar to the function above.
//Will need to figure out later how to store the original size of the current window when it first opens up in normal screen mode
void Game::SetGameWindowed()
{
	//SetConsoleDisplayMode(hConsole_, CONSOLE_WINDOWED_MODE);
}