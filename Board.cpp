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

#include "Board.h"

//----String Constants----//
//Used with the constants list
const std::string Board::noWinDrawState = "noWinDrawState";
const std::string Board::winState = "winState";
const std::string Board::drawState = "drawState";
const std::string Board::acrossWinType = "acrossWinType";
const std::string Board::downWinType = "downWinType";
const std::string Board::diagonalWinType = "diagonalWinType";
const std::string Board::diagonalLeftSubType = "diagonalLeftSubType";
const std::string Board::diagonalRightSubType = "diagonalRightSubType";
const std::string Board::noPlayerPiece = "noPlayerPiece";
const std::string Board::oPlayerPiece = "oPlayerPiece";
const std::string Board::xPlayerPiece = "xPlayerPiece";
const std::string Board::columnOne = "columnOne";
const std::string Board::columnTwo = "columnTwo";
const std::string Board::columnThree = "columnThree";
const std::string Board::columnFour = "columnFour";
const std::string Board::columnFive = "columnFive";
const std::string Board::rowOne = "rowOne";
const std::string Board::rowTwo = "rowTwo";
const std::string Board::rowThree = "rowThree";
const std::string Board::rowFour = "rowFour";
const std::string Board::rowFive = "rowFive";
const std::string Board::nullConstant = "nullConstant";
const std::string Board::fatalError = "fatalError";

const std::string Board::fatalErrorSound = "fatalErrorSound";

Board::Board() throw ()
	: hConsoleWindow_(GetStdHandle(STD_OUTPUT_HANDLE)), totalXsOnBoard_(0), totalOsOnBoard_(0)
{
	const int sizeOfPieceArr = 3, sizeOfErrorArr = 3;
	system("cls");

	//Enter values into the numToCharConversionList
	std::array<const int, sizeOfPieceArr> pieceNumbersArr = {0, 1, 2};
	std::array<char, sizeOfPieceArr> pieceCharactersArr = {' ', 'O', 'X'};

	for(int i = 0; i < sizeOfPieceArr; i++) {
		numToCharConversionList.insert(std::pair<const int, char>(pieceNumbersArr[i], pieceCharactersArr[i]));
	}
}	

void Board::SetupBoard(const ConstList &cList)
{
	char input;
	bool answer = false;
	while(!answer) {
		system("cls");
		std::cout<<"How many spaces would like on the board?\n";
		std::cout<<"Your choices are:\n";
		std::cout<<" A)	9\n";
		std::cout<<" B)	16\n";
		std::cout<<" C)	25\n";
		std::cout<<"Please enter the letter representing your choice below.\n";
		std::cin>>input;

		if(input == 'a' || input == 'A') {
			multiplier_ = typeA;
			numOfSpaces_ = A;
			answer = true;
		}
		else if(input == 'b' || input == 'B') {
			multiplier_ = typeB;
			numOfSpaces_ = B;
			answer = true;
		}
		else if(input == 'c' || input == 'C') {
			multiplier_ = typeC;
			numOfSpaces_ = C;
			answer = true;
		}
		else {
			std::cout<<"Please enter a choice as listed above."<<std::endl;
			std::cout<<"Try again..."<<std::endl;
			_getche();
		}
	}

	(*this).constantsList = cList;

	InitiateBoard();
}

void Board::InitiateBoard()
{
	spaceList.resize (numOfSpaces_);
	const int ROW_CONST = multiplier_ * 100, COLMN_CONST = multiplier_ * 10, t_noPlayerPiece = GetConstantFromList(noPlayerPiece);
	//Inititalize vector with square designations and no x's and o's present
	//So if the multiplier was 4 then the spaceList would look something like this...
	//[110],[120],[130],[140]
	//The ones spot represents the type of piece it has on it
	//		--0 means no piece
	//		--1 means an O
	//		--2 means an X
	//The tens spot represents what column its in
	//And the hundreds spot represent what row its in
	//So, 120 would mean that there is no piece there, its in row 1 and column 2
	
	IntIter spaceListIter;
	spaceListIter = spaceList.begin();
	for(int i = 100; i <= ROW_CONST; i += 100)
		for(int j = 10; j <= COLMN_CONST; j += 10) {
			int space = i + j + t_noPlayerPiece;	//adds i,j, and the nopiece variable together to get us the number for the designated space
			*spaceListIter = space;			//adds number to the vector
			spaceListIter++;				//increments the vector							
		}

	//Initalize piecePlacement with the proper number of spaces
	piecePlacement.resize(numOfSpaces_);
	ProcessPiecePlacementList();
}

void Board::ResetBoard()
{
	spaceList.clear();
	system("cls");
	SetupBoard(constantsList);
	system("cls");
	totalXsOnBoard_ = totalOsOnBoard_ = 0;
}

void Board::DisplayPiece(int &squareCount, int &temp2, int pieceSpacing, bool pieceHasColor)
{
	//Reset the text color if pieceHasColor is false
	if(!pieceHasColor)
		ResetConsoleColor();
	
	char pTemp;
	pTemp = XorO(piecePlacement[squareCount]);
	std::cout<<pTemp;
	temp2 += pieceSpacing;
	squareCount++;

	if(pieceHasColor)
		ResetConsoleColor();
}

char Board::DisplayWinMessage(int playerID, int playerPiece, int playerTextColor)
{
	const int lineSize = 46;
	char piece = XorO(playerPiece);
	system("cls");
	SetConsoleTextAttribute(hConsoleWindow_, playerTextColor);
	std::cout<<"^o^ ---- Player "<<playerID<<" has won the game!!! ---- ^o^"<<"\n";
	std::cout<<"-----------    Congratulations    ------------"<<"\n";
	for(int i = 1; i <= 46; i++) {
		std::cout<<playerPiece;
		Sleep(50);
	}
	ResetConsoleColor();
	std::cout<<"\n";
	std::cout<<"Press any key to continue..."<<std::endl;
	_getche();

	return piece;
}

bool Board::ProcessSpaceList(int location, int playerPiece)
{
	bool error = false; //No errors right now
	
	//Process spaceList adding the new values	
	for(auto &i : spaceList)
		if(location == i)
		{
			//location matched location on grid exactly. No piece already exists here. Add in piece, return noError
			i += playerPiece;
			//If location gets matched, the loop ends.
			break;
		}
		else if((location + 1) == i || (location + 2) == i)
			throw Exception(err.Piece_Exists_At_Location);

	return error;
}

void Board::ProcessPiecePlacementList()
{
	IntIter spaceListIter;
	spaceListIter = spaceList.begin();

	std::string sTemp;
	std::stringstream ssTemp;
	for(auto &i : piecePlacement) {	
		//Convert number from spaceList to a string
		sTemp.clear();
		ssTemp.clear();
		ssTemp<<*spaceListIter;
		ssTemp>>sTemp;
		
		//Take last character of string and convert it into a integer and dump into piecePlacement
		ssTemp.clear();
		ssTemp<<sTemp[2];
		ssTemp>>i;
		
		//Increment spaceListIter
		spaceListIter++;
	}
}

//Board display function, displays the board and extra information line by line and character by character
//TODO:
//Rewrite definition so that it no longer takes Player objects, but instead takes ony the variables it needs from the specific player objects
//It may result in a longer parameter list, but that's ok. I don't want to be passing whole obejcts like this. Ties the functions to the objects
//themselves to much
void Board::DisplayBoard(int numRounds, int numTies, const Player &pOne, const Player &pTwo)
{
	//Constants
	const int sizeOfBoardAcross = (5 * multiplier_) + 1, sizeOfBoardDown = (4 * multiplier_) + 1;

	//Temporary variables
	int temp1 = 1;	//Used for vertical line spacing
	int temp2 = 3;	//Used for piece spacing
	int squareCount = 0;
	
	int	p1Piece = pOne.GetPiece(), p2Piece = pTwo.GetPiece();
	
	const char t_space = GetConstantFromList(GetConstantFromList(noPlayerPiece));

	bool hasColor = true;
	bool noColor = false;
	//Going down then across
	for(int i = 1; i <= sizeOfBoardDown; i++) {
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) {
			if(i == 1 || i == 13 || i == 17 || i == 21) {
				if(j == 1 || j == sizeOfBoardAcross)
					std::cout<<t_space;
				else
					std::cout<<horizontalLine2;
			}
			else if(i == 4 || i == 10 || i == 12 || i == 14 || i == 16 || i == 18 || i == 20) {
				if(j == 1)
					std::cout<<verticalLine;
				else if(j == temp1) {
					std::cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					std::cout<<t_space;
			}
			else if(i == 7 || i == 11 || i == 15 || i == 19) {
				if(j == 1)
					std::cout<<verticalLine;
				else if(j == temp1) {
					std::cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2) {
					if(piecePlacement[squareCount] == p1Piece) {
						pOne.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece) {
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else {
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					}
				}
				else
					std::cout<<t_space;
			}
			else {
				switch (i) {
				case 2:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == sizeOfBoardAcross)
						std::cout<<verticalLine<<"          Round: "<<numRounds;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else
						std::cout<<t_space;
					break;
				case 3:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == sizeOfBoardAcross)
						std::cout<<verticalLine<<"          Ties: "<<numTies;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2) {
						if(piecePlacement[squareCount] == p1Piece) {
							pOne.SetPlayerTextColor();
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
							ResetConsoleColor();
						}
						else if(piecePlacement[squareCount] == p2Piece) {
							pTwo.SetPlayerTextColor();
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
							ResetConsoleColor();
						}
						else {
							ResetConsoleColor();
							DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
						}
					}
					else
						std::cout<<t_space;
					break;
				case 5:
					if(j == 1)
						std::cout<<t_space;
					else if(j == sizeOfBoardAcross)
						std::cout<<t_space<<"          Player 1: "<<pOne.GetName();
					else
						std::cout<<horizontalLine2;
					break;
				case 6:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == sizeOfBoardAcross)
						std::cout<<verticalLine<<"          Player 1's Score: "<<pOne.GetScore();
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else
						std::cout<<t_space;
					break;
				case 8:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == sizeOfBoardAcross)
						std::cout<<verticalLine<<"          Player 2: "<<pTwo.GetName();
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else
						std::cout<<t_space;
					break;
				case 9:
					if(j == 1)
						std::cout<<t_space;
					else if(j == sizeOfBoardAcross)
						std::cout<<t_space<<"          Player 2's Score: "<<pTwo.GetScore();
					else
						std::cout<<horizontalLine2;
					break;
				}
			}
		}
		//Move to next line
		std::cout<<std::endl;
		//Reset temporary values
		//temp1 will reset to 1
		//temp2 will reset to 3
		temp1 = 1;
		temp2 = 3;
	}
}

void Board::DisplaySampleBoard()
{
	//Constants
	const int sizeOfBoardAcross = (5 * multiplier_) + 1, sizeOfBoardDown = (4 * multiplier_) + 1;

	//Temporary Values
	int temp1 = 1;

	const char t_space = GetConstantFromList(GetConstantFromList(noPlayerPiece));

	//Going down then across
	for(int i = 1; i <= sizeOfBoardDown; i++) {
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) {
			if(i == 1 || i == 5 || i == 9 || i == 13 || i == 17 || i == 21) {
				if(j == 1 || j == sizeOfBoardAcross)
					std::cout<<t_space;
				else
					std::cout<<horizontalLine2;
			}
			else if(i == 2 || i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 10 || i == 11 || i == 12 ||
					i == 14 || i == 15 || i == 16 || i == 18 || i == 19 || i == 20)
			{
				if(j == 1)
					std::cout<<verticalLine;
				else if(j == temp1) {
					std::cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					std::cout<<t_space;
			}
		}
		//Move to next line
		std::cout<<std::endl;
		//Reset temporary values
		temp1 = 1;
	}
}

void Board::DisplayWinningBoard(int type, int diagonalLocation, int acrossDownLocation, const Player &pOne, const Player &pTwo)
{
	//Constants
	const int sizeOfBoardAcross = (5 * multiplier_) + 1, sizeOfBoardDown = (4 * multiplier_) + 1;
	const int boardStart = 0;

	const int endOfRowOneA = 2, endOfRowOneB = 3, endOfRowOneC = 4;
	
	const int startOfRowTwoA = 3, startOfRowTwoB = 4, startOfRowTwoC = 5;
	const int endOfRowTwoA = 5, endOfRowTwoB = 7, endOfRowTwoC = 9;
	
	const int startOfRowThreeA = 6, startOfRowThreeB = 8, startOfRowThreeC = 10;
	const int endOfRowThreeA = 8, endOfRowThreeB = 11, endOfRowThreeC = 14;
	
	const int startOfRowFourB = 12, startOfRowFourC = 15;
	const int endOfRowFourB = 15, endOfRowFourC = 19;
	
	const int startOfRowFiveC = 20;
	const int endOfRowFiveC = 24;
 
	const int startOfColumnTwo = 1, startOfColumnThree = 2, startOfColumnFour = 3, startOfColumnFive = 4;

	//Constants for processing
	const int t_columnOne = GetConstantFromList(columnOne), t_columnTwo = GetConstantFromList(columnTwo), t_columnThree = GetConstantFromList(columnThree),
			  t_columnFour = GetConstantFromList(columnFour), t_columnFive = GetConstantFromList(columnFive);

	const int t_rowOne = GetConstantFromList(rowOne), t_rowTwo = GetConstantFromList(rowTwo), t_rowThree = GetConstantFromList(rowThree), t_rowFour = GetConstantFromList(rowFour),
			  t_rowFive = GetConstantFromList(rowFive);

	const char t_space = GetConstantFromList(GetConstantFromList(noPlayerPiece));

	bool playerOneWon;
	
	//Bool values to decide what pieces get highlighted on the board
	bool across, down, diagonal, diagonalLeft, diagonalRight;
	across = down = diagonal = diagonalLeft = diagonalRight = false;
	
	//Temp values
	int temp1 = 1;	//Used for vertical line spacing
	int temp2 = 3;	//Used for piece spacing
	int squareCount = 0;
	
	char winningPlayerPiece;
	
	//Winning player string
	std::string winningPlayer;
	
	if(pOne.DidPlayerWin()) {
		winningPlayerPiece = DisplayWinMessage(pOne.GetID(), pOne.GetPiece(), pOne.GetPlayerTextColor());
		winningPlayer = "Player 1";
		playerOneWon = true;
	}
	else {
		winningPlayerPiece = DisplayWinMessage(pTwo.GetID(), pTwo.GetPiece(), pTwo.GetPlayerTextColor());
		winningPlayer = "Player 2";
		playerOneWon = false;
	}
		
	//Figure out where the pieces on the board should be highlighted
	if(type == GetConstantFromList(acrossWinType))
		across = true;
	else if(type == GetConstantFromList(downWinType))
		down = true;
	else if(type == GetConstantFromList(diagonalWinType)) {
		diagonal = true;
		if(diagonalLocation == GetConstantFromList(diagonalLeftSubType))
			diagonalLeft = true;
		else
			diagonalRight = true;
	}

	bool hasColor = true;
	bool noColor = false;
	//Now iterate through and display the board with the proper highlights applied to the winning pieces
	for(int i = 1; i <= sizeOfBoardDown; i++) {
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) {
			if(i == 1 || i == 5 || i == 9 || i == 13 || i == 17 || i == 21) {
				if(j == 1 || j == sizeOfBoardAcross)
					std::cout<<t_space;
				else
					std::cout<<horizontalLine2;
			}
			else if(i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 12 || i == 14 || i == 16 || i == 18) {
				if(j == 1)
					std::cout<<verticalLine;
				else if(j == temp1) {
					std::cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					std::cout<<t_space;
			}
			else {
				switch(i) {
				case 3:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2 && diagonal && diagonalLeft && squareCount == boardStart) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && diagonal && diagonalRight) {
						if((numOfSpaces_ == A && squareCount == endOfRowOneA) ||
						   (numOfSpaces_ == B && squareCount == endOfRowOneB) ||
						   (numOfSpaces_ == C && squareCount == endOfRowOneC))
						{
							SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						}
					}		 
					else if(j == temp2 && down && !across && !diagonal) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(acrossDownLocation == t_columnOne)
							if(squareCount == boardStart)
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnTwo)
							if(squareCount == startOfColumnTwo)
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnThree)
							if(squareCount == startOfColumnThree)
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
							if(squareCount == startOfColumnFour)
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
							if(squareCount == startOfColumnFive)
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);

						ResetConsoleColor();
					}
					else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowOne) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && !diagonal && !across && !down)
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					else
						std::cout<<t_space;
					break;
				case 7:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2 && diagonal && diagonalLeft) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == A && squareCount == (startOfRowTwoA + 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == B && squareCount == (startOfRowTwoB + 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (startOfRowTwoC + 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && diagonal && diagonalRight) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == A && squareCount == (endOfRowTwoA - 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == B && squareCount == (endOfRowTwoB - 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (endOfRowTwoC - 1))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && down && !across && !diagonal) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(acrossDownLocation == t_columnOne)
							if(squareCount == (boardStart + multiplier_))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnTwo)
							if(squareCount == (startOfColumnTwo + multiplier_))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnThree)
							if(squareCount == (startOfColumnThree + multiplier_))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
							if(squareCount == (startOfColumnFour + multiplier_))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
							if(squareCount == (startOfColumnFive + multiplier_))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					
						ResetConsoleColor();
					}
					else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowTwo) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && !diagonal && !across && !down)
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					else
						std::cout<<t_space;
					break;
				case 11:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2 && diagonal && diagonalLeft) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == A && squareCount == endOfRowThreeA)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == B && squareCount == (startOfRowThreeB + 2))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (startOfRowThreeC + 2))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && diagonal && diagonalRight) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == A && squareCount == startOfRowThreeA)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == B && squareCount == (endOfRowThreeB - 2))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (endOfRowThreeC - 2))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && down && !across && !diagonal) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						int addMultiplier = multiplier_ * 2;
						if(acrossDownLocation == t_columnOne)
							if(squareCount == (boardStart + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnTwo)
							if(squareCount == (startOfColumnTwo + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnThree)
							if(squareCount == (startOfColumnThree + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
							if(squareCount == (startOfColumnFour + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
							if(squareCount == (startOfColumnFive + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);

						ResetConsoleColor();
					}
					else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowThree) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && !diagonal && !across && !down)
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					else
						std::cout<<t_space;
					break;
				case 15:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2 && diagonal && diagonalLeft) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == B && squareCount == endOfRowFourB)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (startOfRowFourC + 3))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && diagonal && diagonalRight) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						if(numOfSpaces_ == B && squareCount == startOfRowFourB)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(numOfSpaces_ == C && squareCount == (endOfRowFourC - 3))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && down && !across && !diagonal) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						int addMultiplier = multiplier_ * 3;
						if(acrossDownLocation == t_columnOne)
							if(squareCount == (boardStart + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnTwo)
							if(squareCount == (startOfColumnTwo + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnThree)
							if(squareCount == (startOfColumnThree + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
							if(squareCount == (startOfColumnFour + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
							if(squareCount == (startOfColumnFour + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFour) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && !diagonal && !across && !down)
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					else
						std::cout<<t_space;
					break;
				case 19:
					if(j == 1)
						std::cout<<verticalLine;
					else if(j == temp1) {
						std::cout<<verticalLine;
						temp1 += sizeOfSquareAcross;
					}
					else if(j == temp2 && diagonal && diagonalLeft && squareCount == endOfRowFiveC) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && diagonal && diagonalRight && squareCount == startOfRowFiveC) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && down && !across && !diagonal) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						int addMultiplier = multiplier_ * 4;
						if(acrossDownLocation == t_columnOne)
							if(squareCount == (boardStart + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnTwo)
							if(squareCount == (startOfColumnTwo + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnThree)
							if(squareCount == (startOfColumnThree + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFour)
							if(squareCount == (startOfColumnFour + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						else if(acrossDownLocation == t_columnFive)
							if(squareCount == (startOfColumnFive + addMultiplier))
								DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);

						ResetConsoleColor();
					}
					else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFive) {
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(j == temp2 && !diagonal && !across && !down)
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					else
						std::cout<<t_space;
					break;
				}
			}
		}
		//Move to next line
		std::cout<<std::endl;
		//Reset temporary values
		//temp1 will reset to 1
		//temp2 will reset to 3
		temp1 = 1;
		temp2 = 3;
	}
	//Skip a line, for spacing
	std::cout<<std::endl;

	SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);

	//Tell the winning player how they won
	DisplayWinLocationMessage(across, down, diagonal, diagonalLeft, diagonalRight, acrossDownLocation, winningPlayer, winningPlayerPiece);

	ResetConsoleColor();
	std::cout<<std::endl<<"Press any key to continue..."<<std::endl;
	_getche();
	system("cls");
}

void Board::DisplayWinLocationMessage(bool across, bool down, bool diagonal, bool diagonalLeft, bool diagonalRight, int acrossDownLocation, std::string winningPlayer, char winningPlayerPiece)
{
	const int t_columnOne = GetConstantFromList(columnOne), t_columnTwo = GetConstantFromList(columnTwo), t_columnThree = GetConstantFromList(columnThree),
			  t_columnFour = GetConstantFromList(columnFour), t_columnFive = GetConstantFromList(columnFive);
	const int t_rowOne = GetConstantFromList(rowOne), t_rowTwo = GetConstantFromList(rowTwo), t_rowThree = GetConstantFromList(rowThree), t_rowFour = GetConstantFromList(rowFour),
			  t_rowFive = GetConstantFromList(rowFive);
	
	if(diagonal && !across && !down) {
		if(diagonalLeft)
			std::cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from left to right"<<std::endl;
		else if(diagonalRight)
			std::cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from right to left"<<std::endl;
	}
	else if(across && !down && !diagonal) {
		if(acrossDownLocation == t_rowOne)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 1"<<std::endl;
		else if(acrossDownLocation == t_rowTwo)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 2"<<std::endl;
		else if(acrossDownLocation == t_rowThree)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 3"<<std::endl;
		else if(acrossDownLocation == t_rowFour)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 4"<<std::endl;
		else if(acrossDownLocation == t_rowFive)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 5"<<std::endl;
	}
	else if(down && !across && !diagonal) {
		if(acrossDownLocation == t_columnOne)
			std::cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going down on column 1"<<std::endl;
		else if(acrossDownLocation == t_columnTwo)
			std::cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 2"<<std::endl;
		else if(acrossDownLocation == t_columnThree)
			std::cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 3"<<std::endl;
		else if(acrossDownLocation == t_columnFour)
			std::cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 4"<<std::endl;
		else if(acrossDownLocation == t_columnFive)
			std::cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 5"<<std::endl;
	}
}

bool Board::CheckMoveLocation(int location)
{
	int tens = 10, hundreds = 100;
	int locationCheckDown = ((tens * multiplier_) + (hundreds * multiplier_));
	bool checkOK = true;

	if(location > locationCheckDown)
		checkOK = false;
	else {
		int locationCheckAcross = locationCheckDown - (hundreds * multiplier_);
		int boundsCheck = location - ((location / hundreds) * hundreds);
		if(boundsCheck > locationCheckAcross)
			checkOK = false;
	}

	return checkOK;
}

bool Board::UpdateBoard(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus)
{
	if(!playerOneMoveStatus && !playerTwoMoveStatus)
		throw Exception(err.Fatal_Error);
	
	if(!(CheckMoveLocation(location)))
		throw Exception(err.Move_Out_Of_Bounds);

	ProcessSpaceList(location, playerPiece);
	
	const int t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	ProcessPiecePlacementList();

	return true;
}

char Board::XorO(int num)
{
	//Remember...
	//1 = O
	//2 = X
	//Constants for pieces
	const int t_noPlayerPiece = GetConstantFromList(noPlayerPiece), t_oPlayerPiece = GetConstantFromList(oPlayerPiece), t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	if(num == t_noPlayerPiece)
		return (GetConstantFromList(t_noPlayerPiece));
	else if(num == t_oPlayerPiece)
		return (GetConstantFromList(t_oPlayerPiece));
	else if(num == t_xPlayerPiece)
		return GetConstantFromList(t_xPlayerPiece);
	else {
		std::string errorMsg = "DEBUG MESSAGE - If you're seeing this check the calls for the XorO function\n";
		throw Exception(err.Fatal_Error, errorMsg);
	}
}

void Board::SetWinningPlayersTextColor(bool p, const Player &p1, const Player &p2)
{
	if(p)
		p1.SetPlayerTextColor();
	else
		p2.SetPlayerTextColor();
}

WDPacketPtr Board::GetGameState()
{
	//bool array to keep track of win
	//depending on the element in the array thats comes out to true, this will
	//correspond to which spot on the board has a win. If they're all false, there is
	//either no win or a draw
	//0 = diagonalLeft
	//1 = diagonalRight
	//2 = rowOne
	//3 = rowTwo
	//4 = rowThree
	//5 = rowFour
	//6 = rowFive
	//7 = columnOne
	//8 = columnTwo
	//9 = columnThree
	//10 = columnFour
	//11 = columnFive
	bool winArray[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
	bool xWin = false;
	bool oWin = false;

	const int totalSquares = multiplier_ * 2;

	int numOfXsInRow = 0;
	int numOfOsInRow = 0;

	//Figure out how many possible wins there are
	int waysToWin = 0;
	int addToCounter = 5;
	if(multiplier_ == typeA || multiplier_ == typeB || multiplier_ == typeC) {
		waysToWin = typeA + addToCounter;
		if(multiplier_ == typeB || multiplier_ == typeC) {
			waysToWin = typeB + (++addToCounter);
			if(multiplier_ == typeC)
				waysToWin = typeC + (++addToCounter);
		}
	}

	//Figure out possiblity of a draw
	int totalPiecesOnBoard = GetTotalNumOfPiecesOnBoard();
	bool possibleDraw = false;
	if(totalPiecesOnBoard == totalSquares)
		possibleDraw = true;

	const int startingBoardLocation = 110;
	const int boardLimit = startingBoardLocation * multiplier_;
	int currentBoardLocation = startingBoardLocation;
	bool noReset = false;
	bool AcrossOrDown = false;	//Across is false, Down is true
	bool loop = true;
	int i = 0;
	while(i < waysToWin) { 
		if(i == 0) {     //Test left diagonal
			for(int j = 0; j < multiplier_; j++) {
				CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
				//Increment currentBoardLocation by necessay amount
				currentBoardLocation += startingBoardLocation;
				if(currentBoardLocation > boardLimit)
					break;
			}

			if(numOfXsInRow == multiplier_) {
				winArray[0] = true;
				xWin = true;
				break;
			}
			else if(numOfOsInRow == multiplier_) {
				winArray[0] = true;
				oWin = true;
				break;
			}
		}
		else if(i == 1) {     //Test right diagonal
			const int incrementBoard = 90;
			currentBoardLocation = (startingBoardLocation + (multiplier_ * 10)) - 10;
			for(int j = 0; j < multiplier_; j++) {
				CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
				//Increment currentBoardLocation by necessary amount
				currentBoardLocation += incrementBoard;
				if(currentBoardLocation > boardLimit)
					break;
			}

			if(numOfXsInRow == multiplier_) {
				winArray[1] = true;
				xWin = true;
				break;
			}
			else if(numOfOsInRow == multiplier_) {
				winArray[1] = true;
				oWin = true;
				break;
			}
		}
		else {
			if(multiplier_ == typeA) {
				if(i == 2 || i == 3 || i == 4) {     //Test for rowOne, rowTwo, rowThree
					const int incrementBoard = 10;
					if(i == 2) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
					}
					else if(i == 3) 
						currentBoardLocation += 100;
					else {
						currentBoardLocation += 100;
						noReset = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[i] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[i] = true;
						oWin = true;
						break;
					}
				}
				else if(i == 5 || i == 6 || i == 7) {     //Test for columnOne, columnTwo, columnThree
					const int incrementBoard = 100;
					if(i == 5) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
						AcrossOrDown = true;
					}
					else if(i == 6)
						currentBoardLocation += 10;
					else {
						currentBoardLocation += 10;
						noReset = false;
						AcrossOrDown = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[(i + 2)] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[(i + 2)] = true;
						oWin = true;
						break;
					}
				}
			}
			else if(multiplier_ == typeB) {
				if(i == 2 || i == 3 || i == 4 || i == 5) { //Test for rowOne, rowTwo, rowThree, rowFour
					const int incrementBoard = 10;
					if(i == 2) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
					}
					else if(i == 3 || i == 4)
						currentBoardLocation += 100;
					else {
						currentBoardLocation += 100;
						noReset = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[i] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[i] = true;
						oWin = true;
						break;
					}
				}
				else if(i == 6 || i == 7 || i == 8 || i == 9) { //Test for columnOne, columnTwo, columnThree, columnFour
					const int incrementBoard = 100;
					if(i == 6) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
						AcrossOrDown = true;
					}
					else if(i == 7 || i == 8)
						currentBoardLocation += 10;
					else {
						currentBoardLocation += 10;
						noReset = false;
						AcrossOrDown = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[i + 1] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[i + 1] = true;
						oWin = true;
						break;
					}
				}
			}
			else if(multiplier_ == typeC) {
				if(i == 2 || i == 3|| i == 4 || i == 5 || i == 6) { //Test for rowOne, rowTwo, rowThree, rowFour, rowFive
					const int incrementBoard = 10;
					if(i == 2) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
					}
					else if(i == 3 || i == 4 || i == 5)
						currentBoardLocation += 100;
					else {
						currentBoardLocation += 100;
						noReset = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[i] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[i] = true;
						oWin = true;
						break;
					}
				}
				else if(i == 7 || i == 8 || i == 9 || i == 10 || i == 11) { //Test for columnOne, columnTwo, columnThree, columnFour, columnFive
					const int incrementBoard = 100;
					if(i == 7) {
						currentBoardLocation = startingBoardLocation;
						noReset = true;
						AcrossOrDown = true;
					}
					else if(i == 8 || i == 9 || i == 10)
						currentBoardLocation += 10;
					else {
						currentBoardLocation += 10;
						noReset = false;
						AcrossOrDown = false;
					}

					for(int j = 0; j < multiplier_; j++) {
						CheckForXsAndOs(currentBoardLocation, numOfXsInRow, numOfOsInRow);
						currentBoardLocation += incrementBoard;
					}

					if(numOfXsInRow == multiplier_) {
						winArray[i] = true;
						xWin = true;
						break;
					}
					else if(numOfOsInRow == multiplier_) {
						winArray[i] = true;
						oWin = true;
						break;
					}
				}
			}
		}

		//Reset counters/boardLocation
		numOfXsInRow = 0;
		numOfOsInRow = 0;

		if(!noReset)
			currentBoardLocation = startingBoardLocation;
		else {
			if(!AcrossOrDown)
				currentBoardLocation -= (multiplier_ * 10);
			else
				currentBoardLocation -= (multiplier_ * 100);
		}
		i++;
	}
	
	int gameOutcome = 0;
	int gamePiece = 0;
	int winType = 0;
	int diagonalLocation = 0;
	int rowLocation = 0;
	int columnLocation = 0;
	if(!xWin && !oWin && !possibleDraw)
		gameOutcome = GetConstantFromList(noWinDrawState);
	else if(!xWin && !oWin && possibleDraw)
		gameOutcome = GetConstantFromList(drawState);
	else if(xWin && !oWin) {
		gameOutcome = GetConstantFromList(winState);
		gamePiece = GetConstantFromList(xPlayerPiece);	
	}
	else if(!xWin && oWin) {
		gameOutcome = GetConstantFromList(winState);
		gamePiece = GetConstantFromList(oPlayerPiece);
	}
	else
		throw Exception(err.Fatal_Error, "DEBUG MESSAGE - If you see this there is a bug in the code...");

	if(gameOutcome == GetConstantFromList(winState)) {
		bool parsingIsDone = false;
		for(int i = 0; i < 11; i++) {
			if(i == 0 || i == 1) {
				winType = GetConstantFromList(diagonalWinType);
				if(i == 0 && winArray[i] && !parsingIsDone) {
					diagonalLocation = GetConstantFromList(diagonalLeftSubType);
					parsingIsDone = true;
				}
				else if(i == 1 && winArray[i] && !parsingIsDone) {
					diagonalLocation = GetConstantFromList(diagonalRightSubType);
					parsingIsDone = true;
				}
				if(parsingIsDone) {
					rowLocation = GetConstantFromList(nullConstant);
					columnLocation = GetConstantFromList(nullConstant);
					break;
				}
			}
			else if(i >= 2 && i <=6) {
				winType = GetConstantFromList(acrossWinType);
				if(i == 2 && winArray[i] && !parsingIsDone) {
					rowLocation = GetConstantFromList(rowOne);
					parsingIsDone = true;
				}
				else if(i == 3 && winArray[i] && !parsingIsDone) {
					rowLocation = GetConstantFromList(rowTwo);
					parsingIsDone = true;
				}
				else if(i == 4 && winArray[i] && !parsingIsDone) {
					rowLocation = GetConstantFromList(rowThree);
					parsingIsDone = true;
				}
				else if(i == 5 && winArray[i] && !parsingIsDone) {
					rowLocation = GetConstantFromList(rowFour);
					parsingIsDone = true;
				}
				else if(i == 6 && winArray[i] && !parsingIsDone) {
					rowLocation = GetConstantFromList(rowFive);
					parsingIsDone = true;
				}
				if(parsingIsDone) {
					diagonalLocation = GetConstantFromList(nullConstant);
					columnLocation = GetConstantFromList(nullConstant);
					break;
				}
			}
			else if(i >= 7 && i <= 11) {
				winType = GetConstantFromList(downWinType);
				if(i == 7 && winArray[i] && !parsingIsDone) {
					columnLocation = GetConstantFromList(columnOne);
					parsingIsDone = true;
				}
				else if(i == 8 && winArray[i] && !parsingIsDone) {
					columnLocation = GetConstantFromList(columnTwo);
					parsingIsDone = true;
				}
				else if(i == 9 && winArray[i] && !parsingIsDone) {
					columnLocation = GetConstantFromList(columnThree);
					parsingIsDone = true;
				}
				else if(i == 10 && winArray[i] && !parsingIsDone) {
					columnLocation = GetConstantFromList(columnFour);
					parsingIsDone = true;
				}
				else if(i == 11 && winArray[i] && !parsingIsDone) {
					columnLocation = GetConstantFromList(columnFive);
					parsingIsDone = true;
				}
				if(parsingIsDone) {
					diagonalLocation = GetConstantFromList(nullConstant);
					rowLocation = GetConstantFromList(nullConstant);
					break;
				}
			}
		}
		if(!parsingIsDone)
			throw Exception(err.Fatal_Error, "Check code in FindWin Function, there is a problem");
	}

	WDPacketPtr packet(new WinDrawPacket(constantsList));
	packet->CreatePacket(gameOutcome, gamePiece, winType, diagonalLocation, rowLocation, columnLocation);

	return packet;
}

void Board::ResetConsoleColor()
{
	int dark_white = 7 % 16;
	SetConsoleTextAttribute(hConsoleWindow_, dark_white);
}

int Board::GetConstantFromList(std::string request) const
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

char Board::GetConstantFromList(int request) const
{
	int returnValue = -5;
	for(const auto &i : numToCharConversionList)
		if((i.first) == request) {
			return (i.second);
			break;
		}

	if(returnValue == -5) {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Unknown_Constant_Error);
	}

	return returnValue;
}

int Board::FindSpaceListLocation(int spaceRequest)
{
	int returnValue = -5;
	int tens = 10;
	int hundreds = 100;
	int x = 0;
	for( auto i : spaceList)
		if(spaceRequest == ((i / tens) * tens))
			returnValue = x;
		else
			x++;

	if(returnValue == -5)
		throw Exception(err.Fatal_Error, "DEBUG MESSAGE - Please check values being used, something isn't right\nFindSpaceListLocation()");

	return returnValue;
}

void Board::CheckForXsAndOs(int boardLocation, int &xCounter, int &oCounter)
{
	int xNumber = GetConstantFromList(xPlayerPiece);
	int oNumber = GetConstantFromList(oPlayerPiece);
	if((spaceList.at(FindSpaceListLocation(boardLocation)) - boardLocation) == xNumber)
		xCounter++;
	else if((spaceList.at(FindSpaceListLocation(boardLocation)) - boardLocation) == oNumber)
		oCounter++;
}

const int Board::GetMultiplier() const
{
	return multiplier_;
}

const int Board::GetTotalNumOfPiecesOnBoard() const
{
	return (totalOsOnBoard_ + totalXsOnBoard_);
}

void Board::UpdateXs()
{
	totalXsOnBoard_++;
}

void Board::UpdateOs()
{
	totalOsOnBoard_++;
}