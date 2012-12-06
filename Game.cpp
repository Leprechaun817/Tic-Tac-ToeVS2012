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
const string Game::gameDrawMessage = "The game has ended in a draw.\nYou can now start a new round or end the game...\n";
const string Game::playerOneWinMessage = "Player 1 has won this round!!\nCongratulations!!!^o^\n";
const string Game::playerTwoWinMessage = "Player 2 has won this round!!\nCongratulations!!!^o^\n";

//----Other Messages----
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

//Constants for sounds
const string Game::playerOneWinSound = "playerOneWinSound";
const string Game::playerTwoWinSound = "playerTwoWinSound";
const string Game::gameOverSound = "gameOverSound";
const string Game::pieceClickSound = "pieceClickSound";
const string Game::badMoveErrorSound = "badMoveErrorSound";
const string Game::fatalErrorSound = "fatalErrorSound";

Game::Game() throw()
	: playerOne_(), playerTwo_(), board_(), soundEng_(), roundsPlayed_(0), gameDraws_(0), turnCounter_(0), firstPlay_(true)
{
	array<const string, 23> constantsNames = {noWinDrawState, winState, drawState, acrossWinType, downWinType, diagonalWinType, diagonalLeftSubType, diagonalRightSubType,
							   noPlayerPiece, oPlayerPiece, xPlayerPiece, columnOne, columnTwo, columnThree, columnFour, columnFive, rowOne, rowTwo, 
							   rowThree, rowFour, rowFive, nullConstant, fatalError};
	array<int, 23> constantsValues = {0, 1, 2, 1, 2, 3, 1, 2, 0, 1, 2, 10, 20, 30, 40, 50, 100, 200, 300, 400, 500, -1, -2};
	
	//constantsList must be created before board and the 2 players are initialized becuase otherwise I'd be sending them a empty map container
	for(unsigned int i = 0; i < constantsValues.size(); i++)
		constantsList.insert(pair<const string, int>(constantsNames[i], constantsValues[i]));
}

//TODO:
//Rewrite the introduction in this function to include a diagram of the board and coordinates to make
//it a little easier to undertand for people...
void Game::StartGame()
{
	if(firstPlay_) {
		//Initialize the sound first before anything else is done
		soundEng_.InitializeSoundEngine();
		
		DisplayNotices();

		//Setup board
		board_.SetupBoard(constantsList);
	
		//set bounds limit, basically players shouldn't be able to enter in values past this number
		//It's also the number used to determine if somebody won the game
		//The value is pulled from the board object
		boundsLimit_ = board_.GetMultiplier();
	
		//Initializing each player
		playerOne_.InitializePlayer(boundsLimit_, constantsList);
		playerTwo_.InitializePlayer(boundsLimit_, constantsList);

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
	bool continueGame = true;
	
	if(playOrder_ == 1) {
		continueGame = GetPlayerMove(playerOneTurn);
		if(!continueGame)
			return continueGame;
		
		continueGame = GetPlayerMove(playerTwoTurn);
		if(!continueGame)
			return continueGame;
	}
	else {
		continueGame = GetPlayerMove(playerTwoTurn);
		if(!continueGame)
			return continueGame;

		continueGame = GetPlayerMove(playerOneTurn);
		if(!continueGame)
			return continueGame;
	}
	
	if(board_.GetTotalNumOfPiecesOnBoard() >= boundsLimit_)
		continueGame = ProcessPacket(board_.FindWinDraw());
	
	return continueGame;
}

bool Game::EndGame()
{
	char answer;

	//Clear the screen
	system("cls");
	
	DisplayLastRoundStats();
	//Ask player/s whether they want to play another round
	bool quitGame;
	bool loop = false;
	while(!loop) {
		//Play game over noise here
		cout<<"Would you like to play for another round? y or n"<<endl;
		cin>>answer;

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
			cout<<"Please enter y or n"<<endl;
			cout<<"Press any key to continue..."<<endl;
			_getche();
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
		cout<<e.what()<<"\n";
		cout<<"DEBUG ERROR - If you see this something is wrong with the code!!!\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();
	}

	//Reset both players
	playerOne_.ResetPlayer(boundsLimit_);
	playerTwo_.ResetPlayer(boundsLimit_);

	DecidePlayOrder();
}

bool Game::GetPlayerMove(int order)
{
	bool continuePlay = true;

	if(order == 1) {
		bool playerOneContinueGame;
		bool playerOneGood = false;
		while(!playerOneGood) {	
			try {
				system("cls");
				board_.DisplayBoard(roundsPlayed_, gameDraws_, playerOne_, playerTwo_);
				playerOneContinueGame = playerOne_.MakeMove();
				if(!playerOneContinueGame) {
					continuePlay = false;
					playerOneGood = true;
				}
				else
					playerOneGood = board_.UpdateBoard(playerOne_.GetPiece(), playerOne_.GetMove(), playerOne_.HasPlayerMadeMove(), playerTwo_.HasPlayerMadeMove());
			}
			catch(Exception &e) {
				if(e.GetErrorType() == err.Move_Out_Of_Bounds || e.GetErrorType() == err.Piece_Exists_At_Location) {
					//Play bad move noise here
					cout<<e.what()<<"\n";
					cout<<"Please re-enter your choice.\n";
					cout<<anyKey<<endl;
					_getche();
				}
				else
					throw;
					//Play fatal error noise here
			}
			//Play click noise here
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
				if(!playerTwoContinueGame) {
					continuePlay = false;
					playerTwoGood = true;
				}
				else
					playerTwoGood = board_.UpdateBoard(playerTwo_.GetPiece(), playerTwo_.GetMove(), playerOne_.HasPlayerMadeMove(), playerTwo_.HasPlayerMadeMove());
			}
			catch(Exception &e) {
				if(e.GetErrorType() == err.Move_Out_Of_Bounds || e.GetErrorType() == err.Piece_Exists_At_Location) {
					//Play bad move noise here
					cout<<e.what()<<"\n";
					cout<<"Please re-enter your choice.\n";
					cout<<anyKey<<endl;
					_getche();
				}
				else
					throw;
					//Play fatal error noise here
			}
			//Play click noise here
		}
	}

	return continuePlay;
}

bool Game::ProcessPacket(WDPacketPtr packet)
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
	else if(t_gameState == t_winState) {
		continueGame = false;
		//Get player piece and compare, update their winCounter
		if(packet->GetPlayerPiece() == playerOne_.GetPiece()) {
			playerOne_.UpdateScore();
			playerOne_.SetPlayerWon();
			//Play playerOne Win noise here
			//Message telling that player 1 has won the game
			cout<<playerOneWinMessage;
			playerOne_.DisplayScore();
			cout<<anyKey;
			_getche();
		}
		else if(packet->GetPlayerPiece() == playerTwo_.GetPiece()) {
			playerTwo_.UpdateScore();
			playerTwo_.SetPlayerWon();
			//Play PlayerTwo Win noise here
			//Message telling that player 2 has won the game
			cout<<playerTwoWinMessage;
			playerTwo_.DisplayScore();
			cout<<anyKey;
			_getche();
		}
		else
			throw Exception(err.Bad_PlayerPiece_Variable_Fatal);
			//Play fatal error noise here

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
				//play fatal error noise here
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
				//play fatal error noise here
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
			//play fatal error noise here
		}
	}
	else if(t_gameState == t_fatalError)
		throw Exception(err.Bad_GameState_Fatal);	//play fatal error noise here
	else
		throw Exception(err.Bad_GameState_Unknown);	//play fatal error noise here

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
	cout<<"Player 1's name: "<<playerOne_.GetName()<<"\n";
	cout<<playerOne_.GetName()<<"\'s final score is: "<<playerOne_.GetScore()<<"\n\n";
	cout<<"Player 2's name: "<<playerTwo_.GetName()<<"\n";
	cout<<playerTwo_.GetName()<<"\'s final score is: "<<playerTwo_.GetScore()<<"\n\n";
	cout<<"There were a total of "<<roundsPlayed_<<" round\\s played and\n";
	cout<<"there were a total of "<<gameDraws_<<" draws during the game."<<endl;
}

void Game::DisplayLastRoundStats()
{
	cout<<"Player 1's name: "<<playerOne_.GetName()<<"\n";
	cout<<playerOne_.GetName()<<"\'s final score is: "<<playerOne_.GetScore()<<"\n\n";
	cout<<"Player 2's name: "<<playerTwo_.GetName()<<"\n";
	cout<<playerTwo_.GetName()<<"\'s final score is: "<<playerTwo_.GetScore()<<"\n\n";
	cout<<"There were a total of "<<turnCounter_<<" turns taken last round\n";
	cout<<"You have both played "<<roundsPlayed_<<" round\\s so far in this game\n";
	cout<<"and there have been a total of "<<gameDraws_<<" draw\\s so far in this game"<<endl;
}

int Game::GetConstantFromList(string request)
{
	int returnValue = -5;
	for(auto &i : constantsList)
		if((i.first) == request) {
			returnValue = (i.second);
			break;
		}

	if(returnValue == -5)
		throw Exception(err.Unknown_Constant_Error);	//play fatal error noise here
	return returnValue;
}

void Game::DisplayGameInstructions()
{
	cout<<"Welcome to Tic-Tac-Toe!!!!!!!"<<endl;
	cout<<"Get "<<boundsLimit_<<" in a row going across, down or diagonally to win."<<endl;
	cout<<"When somebody wins the game or the game is a draw, you can play another round\n";
	cout<<"or, you can quit.\n\n";
	cout<<"The board looks something like this:\n";
	board_.DisplaySampleBoard();
	cout<<"The columns going across are numbered 1 to "<<boundsLimit_<<" going from left to right and\n";
	cout<<"The rows going down are numbered 1 to "<<boundsLimit_<<" going from top to bottom.\n";
	cout<<"To enter in a choice just type the number of the row first and then the column number seperated by a comma.\n";
	cout<<"Ex: 1,1\n\n";
	cout<<"The player who got Xs will go first and this is picked randomly each time a new game is played"<<endl;
	cout<<"Whenever you're ready we can start..."<<endl;
	cout<<"Press any key to continue..."<<endl;
	_getche();
}

void Game::DisplayNotices()
{
	const string acceptance = "I AGREE";
	const string nonacceptance = "I DISAGREE";
	const string showWarranty = "SHOW W";
	const string showCopyright = "SHOW C";
	
	char warrantyNotice = 'w';
	char copyrightNotice = 'c';
	
	bool loop = true;
	while(loop) {
		string choice;
		system("cls");
		cout<<"Aaron's Tic-Tac-Toe Clone\t-\tCOPYRIGHT 2012 Aaron Gagern\n";
		cout<<"This program comes with ABSOLUTELY NO WARRANTY\n";
		cout<<"This is free software, and you are welcome to redistribute it\n";
		cout<<"under certain conditions\n\n";
		cout<<"For more details on the warranty, type SHOW W\n";
		cout<<"To see the GPLv3 license, type SHOW C\n";
		cout<<"If you accept this license, please type I AGREE\n";
		cout<<"If you don't wish to do this type, I DISAGREE\n";
		cout<<"The program will then exit.\n";
		cout<<"Please type your choice below."<<endl;
		getline(cin, choice);

		if(choice == acceptance)
			loop = false;
		else if(choice == nonacceptance)
			throw Exception(err.NonAcceptance_Of_Notices);
		else if(choice == showWarranty)
			DisplayNoticeFile(warrantyNotice);
		else if(choice == showCopyright)
			DisplayNoticeFile(copyrightNotice);
		else {
			cout<<"You choice didn't match any of the available choices.\n";
			cout<<"Please try again.\n";
			cout<<"Press any key to continue..."<<endl;
			_getche();
		}
	}
}

void Game::DisplayNoticeFile(char noticeType)
{
	string line;
	int lineStop = 0;
	
	ifstream f;
	if(noticeType == 'w') {
		f.open("WARRANTY.txt", ios::in);
		lineStop = 10;
	}
	if(noticeType == 'c') {
		f.open("COPYING.txt", ios::in);
		lineStop = 20;
	}

	if((!f.is_open()) || (!f.good()))
		throw Exception(err.Fatal_Error, "Could not find the notice,\nor notice files have been corrupted.");	//play fatal error noise here

	int lineCount = 0;
	while(!f.eof()) {
		getline(f, line);
		cout<<line;
		lineCount++;

		bool loop = true;
		bool quit = false;
		if((lineCount % lineStop) == 0) {
			while(loop) {
				char choice;
				cout<<"\n\n\nTo continue reading this notice, type c and press enter.\n";
				cout<<"To stop reading this and go back, type q and press enter.\n";
				cin>>choice;

				if(choice == 'c' || choice == 'C') {
					loop = false;
					cout<<"\n\n";
				}
				else if(choice == 'q' || choice == 'Q') {
					loop = false;
					quit = true;
				}
				else
					cout<<"\n\nPlease enter in your choice again.\n";
			}
		}

		if(!loop && quit)
			break;
	}

	//Close the file
	f.close();

	cout<<"Press any key to continue..."<<endl;
	_getche();

	//Remove any remaining junk from cin stream
	cin.clear();
	cin.ignore(1000, '\n');
}