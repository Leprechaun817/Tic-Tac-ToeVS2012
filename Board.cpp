#include "Board.h"

//----String Constants----//
//Used with the constants list
const string Board::noWinDrawState = "noWinDrawState";
const string Board::winState = "winState";
const string Board::drawState = "drawState";
const string Board::acrossWinType = "acrossWinType";
const string Board::downWinType = "downWinType";
const string Board::diagonalWinType = "diagonalWinType";
const string Board::diagonalLeftSubType = "diagonalLeftSubType";
const string Board::diagonalRightSubType = "diagonalRightSubType";
const string Board::noPlayerPiece = "noPlayerPiece";
const string Board::oPlayerPiece = "oPlayerPiece";
const string Board::xPlayerPiece = "xPlayerPiece";
const string Board::columnOne = "columnOne";
const string Board::columnTwo = "columnTwo";
const string Board::columnThree = "columnThree";
const string Board::columnFour = "columnFour";
const string Board::columnFive = "columnFive";
const string Board::rowOne = "rowOne";
const string Board::rowTwo = "rowTwo";
const string Board::rowThree = "rowThree";
const string Board::rowFour = "rowFour";
const string Board::rowFive = "rowFive";
const string Board::nullConstant = "nullConstant";
const string Board::fatalError = "fatalError";

//These constants are the characters/strings that make up the board
const char Board::horizontalLine2 = '-';
const char Board::verticalLine = '|';

//Constants for character measurements of board
const int Board::sizeOfSquareAcross = 5;
const int Board::sizeOfSquareDown = 4;
const int Board::pieceSpacing = 5;
//These next 3 are the total number of squares that can make up a board at once
const int Board::A = 9;
const int Board::B = 16;
const int Board::C = 25;

Board::Board() throw ()
	: hConsoleWindow_(GetStdHandle(STD_OUTPUT_HANDLE)), totalXsOnBoard_(0), totalOsOnBoard_(0)
{
	const int sizeOfPieceArr = 3, sizeOfErrorArr = 3;
	system("cls");

	//Enter values into the numToCharConversionList
	array<const int, sizeOfPieceArr> pieceNumbersArr = {0, 1, 2};
	array<char, sizeOfPieceArr> pieceCharactersArr = {' ', 'O', 'X'};

	for(int i = 0; i < sizeOfPieceArr; i++)
	{
		numToCharConversionList.insert(pair<const int, char>(pieceNumbersArr[i], pieceCharactersArr[i]));
	}
}	

Board::~Board()
{
	//Clean up
	spaceList.clear();
}

void Board::SetupBoard(const ConstList &cList)
{
	char input;
	bool answer = false;
	const int DIVIDER = 3;
	while(!answer)	//Makes sure user enter in either a,b or c and not something else. It also alerts the user when this happens...
	{
		//Give user chance to select how big the board should. This also dictates the length of the game.
		//Bigger board = Longer game
		system("cls");
		cout<<"How many spaces would like on the board?\n";
		cout<<"Your choices are:\n";
		cout<<" A)	9\n";
		cout<<" B)	16\n";
		cout<<" C)	25\n";
		cout<<"Please enter the letter representing your choice below.\n";
		cin>>input;

		if(input == 'a' || input == 'A')
		{
			multiplier_ = A / DIVIDER;
			numOfSpaces_ = A;
			answer = true;
		}
		else if(input == 'b' || input == 'B')
		{
			multiplier_ = B / (DIVIDER + 1);
			numOfSpaces_ = B;
			answer = true;
		}
		else if(input == 'c' || input == 'C')
		{
			multiplier_ = C / (DIVIDER + 2);
			numOfSpaces_ = C;
			answer = true;
		}
		else
		{
			cout<<"Please enter a choice as listed above."<<endl;
			cout<<"Try again..."<<endl;
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
		for(int j = 10; j <= COLMN_CONST; j += 10)
		{
			int space = i + j + t_noPlayerPiece;	//adds i,j, and the nopiece variable together to get us the number for the designated space
			*spaceListIter = space;			//adds number to the vector
			spaceListIter++;				//increments the vector							
		}

	//Initalize piecePlacement with the proper number of spaces as well
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
	cout<<pTemp;
	temp2 += pieceSpacing;
	squareCount++;

	if(pieceHasColor)
		ResetConsoleColor();
}

//TODO:
//To be re-written, instead of it getting a player object, it will get the neccessary play information sent to it only
//Will beed to add function to player so that the text color of the player can be accessed
char Board::DisplayWinMessage(const Player &p)
{
	const int lineSize = 46;
	char winningPiece = XorO(p.GetPiece());
	system("cls");
	p.SetPlayerTextColor();
	cout<<"^o^ ---- Player "<<p.GetID()<<" has won the game!!! ---- ^o^"<<"\n";
	cout<<"-----------    Congratulations    ------------"<<"\n";
	for(int i = 1; i <= 46; i++)
	{
		cout<<winningPiece;
		Sleep(50);
	}
	ResetConsoleColor();
	cout<<"\n";
	cout<<"Press any key to continue..."<<endl;
	_getche();

	return winningPiece;
}

bool Board::ProcessSpaceList(int location, int playerPiece)
{
	bool error = false; //No errors right now
	//Only error that can be produced here is where the piece already exists at the
	//specified spot in the spaceList at which point error would become true
	
	//Process spaceList adding the new values
	IntIter spaceListIter;
	for(spaceListIter = spaceList.begin(); spaceListIter != spaceList.end(); spaceListIter++)
	{
		if(location == *spaceListIter)
		{
			//location matched location on grid exactly. No piece already exists here. Add in piece, return noError
			*spaceListIter += playerPiece;
			//If location gets matched, the loop ends.
			break;
		}
		else if((location + 1) == *spaceListIter || (location + 2) == *spaceListIter)
			throw Exception(err.Piece_Exists_At_Location);
	}

	return error;
}

void Board::ProcessPiecePlacementList()
{
	IntIter piecePlaceIter;
	//Iterator for spaceList
	IntIter spaceListIter;
	spaceListIter = spaceList.begin();

	//TODO:
	//Need to find a way to use an array of piece values instead of a vector which is computationally expensive.
	//It won't matter much right now, but later if graphics are added on things like this will make all the difference
	//in the refresh rate of the graphics
	string sTemp;
	stringstream ssTemp;
	for(piecePlaceIter = piecePlacement.begin(); piecePlaceIter != piecePlacement.end(); piecePlaceIter++)
	{	
		//Convert number from spaceList to a string
		sTemp.clear();
		ssTemp.clear();
		ssTemp<<*spaceListIter;
		ssTemp>>sTemp;
		
		//Take last character of string and convert it into a integer and dump into piecePlacement
		ssTemp.clear();
		ssTemp<<sTemp[2];
		ssTemp>>*piecePlaceIter;
		
		//Increment spaceListIter
		spaceListIter++;
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
	string winningPlayer;
	
	if(pOne.DidPlayerWin())
	{
		winningPlayerPiece = DisplayWinMessage(pOne);
		winningPlayer = "Player 1";
		playerOneWon = true;
	}
	else
	{
		winningPlayerPiece = DisplayWinMessage(pTwo);
		ResetConsoleColor();
		winningPlayer = "Player 2";
		playerOneWon = false;
	}
		
	//Figure out where the pieces on the board should be highlighted
	if(type == GetConstantFromList(acrossWinType))
		across = true;
	else if(type == GetConstantFromList(downWinType))
		down = true;
	else if(type == GetConstantFromList(diagonalWinType))
	{
		diagonal = true;
		if(diagonalLocation == GetConstantFromList(diagonalLeftSubType))
			diagonalLeft = true;
		else
			diagonalRight = true;
	}

	bool hasColor = true;
	bool noColor = false;
	//Now iterate through and display the board with the proper highlights applied to the winning pieces
	for(int i = 1; i <= sizeOfBoardDown; i++)
	{
		temp1 += sizeOfSquareAcross;
		for(int j = 1; i <= sizeOfBoardAcross; i++)
		{
			switch(i)
			{
			case 1:
			case 5:
			case 9:
			case 13:
			case 17:
			case 21:
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 2:
			case 4:
			case 6:
			case 8:
			case 10:
			case 12:
			case 14:
			case 16:
			case 18:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					cout<<t_space;
				break;
			case 3:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft && squareCount == boardStart)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					if((numOfSpaces_ == A && squareCount == endOfRowOneA) ||
					   (numOfSpaces_ == B && squareCount == endOfRowOneB) ||
					   (numOfSpaces_ == C && squareCount == endOfRowOneC))
					{
						SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}		 
				else if(j == temp2 && down && !across && !diagonal)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == boardStart)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == startOfColumnTwo)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == startOfColumnThree)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == startOfColumnFour)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == startOfColumnFive)
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowOne)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && !diagonal && !across && !down)
					DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
				else
					cout<<t_space;
				break;
			case 7:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == A && squareCount == (startOfRowTwoA + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == B && squareCount == (startOfRowTwoB + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (startOfRowTwoC + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == A && squareCount == (endOfRowTwoA - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == B && squareCount == (endOfRowTwoB - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (endOfRowTwoC - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFive + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowTwo)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && !diagonal && !across && !down)
					DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
				else
					cout<<t_space;
				break;
			case 11:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == A && squareCount == endOfRowThreeA)
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == B && squareCount == (startOfRowThreeB + 2))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (startOfRowThreeC + 2))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == A && squareCount == startOfRowThreeA)
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == B && squareCount == (endOfRowThreeB - 2))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (endOfRowThreeC - 2))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					int addMultiplier = multiplier_ * 2;
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFive + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowThree)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && !diagonal && !across && !down)
					DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
				else
					cout<<t_space;
				break;
			case 15:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == B && squareCount == endOfRowFourB)
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (startOfRowFourC + 3))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					if(numOfSpaces_ == B && squareCount == startOfRowFourB)
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					else if(numOfSpaces_ == C && squareCount == (endOfRowFourC - 3))
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					int addMultiplier = multiplier_ * 3;
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFour + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFour)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && !diagonal && !across && !down)
					DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
				else
					cout<<t_space;
				break;
			case 19:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft && squareCount == endOfRowFiveC)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && diagonal && diagonalRight && squareCount == startOfRowFiveC)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					int addMultiplier = multiplier_ * 4;
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFour)
					{
						if(squareCount == (startOfColumnFour + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
					else if(acrossDownLocation == t_columnFive)
					{
						if(squareCount == (startOfColumnFive + addMultiplier))
							DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFive)
				{
					SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);
					DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
				}
				else if(j == temp2 && !diagonal && !across && !down)
					DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
				else
					cout<<t_space;
				break;
			}
		}
		//Move to next line
		cout<<endl;
		//Reset temporary values
		//temp1 will reset to 1
		//temp2 will reset to 3
		temp1 = 1;
		temp2 = 3;
	}
	//Skip a line, for spacing
	cout<<endl;

	SetWinningPlayersTextColor(playerOneWon, pOne, pTwo);

	//Tell how the player won
	if(diagonal && !across && !down)
	{
		if(diagonalLeft)
			cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from left to right"<<endl;
		if(diagonalRight)
			cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from right to left"<<endl;
	}
	else if(across && !down && !diagonal)
	{
		if(acrossDownLocation == t_rowOne)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 1"<<endl;
		else if(acrossDownLocation == t_rowTwo)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 2"<<endl;
		else if(acrossDownLocation == t_rowThree)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 3"<<endl;
		else if(acrossDownLocation == t_rowFour)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 4"<<endl;
		else if(acrossDownLocation == t_rowFive)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 5"<<endl;
	}
	else if(down && !across && !diagonal)
	{
		if(acrossDownLocation == t_columnOne)
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going down on column 1"<<endl;
		else if(acrossDownLocation == t_columnTwo)
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 2"<<endl;
		else if(acrossDownLocation == t_columnThree)
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 3"<<endl;
		else if(acrossDownLocation == t_columnFour)
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 4"<<endl;
		else if(acrossDownLocation == t_columnFive)
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 5"<<endl;
	}
	ResetConsoleColor();
	cout<<endl<<"Press any key to continue..."<<endl;
	_getche();
	system("cls");
}

//Board display function, displays the board and extra information line by line and character by character
//TODO:
//Add code to process win information from the WinDrawPacket generated by FindWinDraw function
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
	for(int i = 1; i <= sizeOfBoardDown; i++) //Starting by going down 1
	{
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) //Then we go across, one character at a time. May get incremented further in for loop
		{
			switch (i)
			{
			case 1:
			case 13:
			case 17:
			case 21:
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 2:
				if(j == 1)
					cout<<verticalLine;
				else if(j == sizeOfBoardAcross)
					cout<<verticalLine<<"          Round: "<<numRounds;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					cout<<t_space;
				break;
			case 3:
				if(j == 1)
					cout<<verticalLine;
				else if(j == sizeOfBoardAcross)
					cout<<verticalLine<<"          Ties: "<<numTies;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						pOne.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					}
				}
				else
					cout<<t_space;
				break;
			case 4:
			case 10:
			case 12:
			case 14:
			case 16:
			case 18:
			case 20:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					cout<<t_space;
				break;
			case 5:
				if(j == 1)
					cout<<t_space;
				else if(j == sizeOfBoardAcross)
					cout<<t_space<<"          Player 1: "<<pOne.GetName();
				else
					cout<<horizontalLine2;
				break;
			case 6:
				if(j == 1)
					cout<<verticalLine;
				else if(j == sizeOfBoardAcross)
					cout<<verticalLine<<"          Player 1's Score: "<<pOne.GetScore();
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					cout<<t_space;
				break;
			case 7:
			case 11:
			case 15:
			case 19:
				if(j == 1)
					cout<<verticalLine;
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						pOne.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, hasColor);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing, noColor);
					}
				}
				else
					cout<<t_space;
				break;
			case 8:
				if(j == 1)
					cout<<verticalLine;
				else if(j == sizeOfBoardAcross)
					cout<<verticalLine<<"          Player 2: "<<pTwo.GetName();
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
					cout<<t_space;
				break;
			case 9:
				if(j == 1)
					cout<<t_space;
				else if(j == sizeOfBoardAcross)
					cout<<t_space<<"          Player 2's Score: "<<pTwo.GetScore();
				else
					cout<<horizontalLine2;
				break;
			}
		}
		//Move to next line
		cout<<endl;
		//Reset temporary values
		//temp1 will reset to 1
		//temp2 will reset to 3
		temp1 = 1;
		temp2 = 3;
	}
}

bool Board::CheckMoveLocation(int location)
{
	int tens = 10 * multiplier_, hundreds = 100 * multiplier_;
	int locationCheck = (tens + hundreds);

	if(location > locationCheck)
		return false;
	else
		return true;
}

bool Board::UpdateBoard(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus)
{
	if(!playerOneMoveStatus && !playerTwoMoveStatus)
	{
		throw Exception(err.Fatal_Error);
	}
	
	if(!(CheckMoveLocation(location)))
	{
		throw Exception(err.Move_Out_Of_Bounds);
	}

	ProcessSpaceList(location, playerPiece);
	
	const int t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	if(playerPiece == t_xPlayerPiece)
		totalXsOnBoard_++;
	else
		totalOsOnBoard_++;

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
	else
	{
		string errorMsg = "DEBUG MESSAGE - If you're seeing this check the calls for the XorO function\n";
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

WDPacketPtr Board::FindWinDraw()
{
	//Put these constants here because they only have to do with this function
	//Basically these are the same constants foung in the WinDrawPacket class
	//Ensures that there aren't any mistakes with the different codes

	
	//----TEMPORARY VALUES FOR TESTING ONLY----
	int tempGameOutcome = GetConstantFromList(winState), tempPiece = GetConstantFromList(xPlayerPiece), tempWinLocation = GetConstantFromList(diagonalWinType),
		tempDiagonalLocation = GetConstantFromList(diagonalRightSubType), tempRowLocation = GetConstantFromList(nullConstant), tempColumnLocation = GetConstantFromList(nullConstant);
	//----ABOVE VALUES ARE TEMPORARY----
	//----FOR TESTING PURPOSES ONLY----

	WDPacketPtr packet(new WinDrawPacket(constantsList));
	packet->CreatePacket(tempGameOutcome, tempPiece, tempWinLocation, tempDiagonalLocation, tempRowLocation, tempColumnLocation);

	return packet;
}

void Board::ResetConsoleColor()
{
	int dark_white = 7 % 16;
	SetConsoleTextAttribute(hConsoleWindow_, dark_white);
}

int Board::GetConstantFromList(string request)
{
	ConstListIters_C constListIter;
	constListIter = constantsList.find(request);

	return (constListIter->second);
}

char Board::GetConstantFromList(int request)
{
	PieceListIters_C charConvListIter;
	charConvListIter = numToCharConversionList.find(request);

	return (charConvListIter->second);
}

const int Board::GetMultiplier() const
{
	return multiplier_;
}

const int Board::GetTotalNumOfPiecesOnBoard() const
{
	return (totalOsOnBoard_ + totalXsOnBoard_);
}