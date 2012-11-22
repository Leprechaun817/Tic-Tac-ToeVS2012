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
const string Board::horizontalLine1 = "-----";
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

Board::Board()
{
	const int sizeOfPieceArr = 3;
	const int sizeOfErrorArr = 3;
	hConsoleWindow_ = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	//Enter values into the numToCharConversionList
	array<const int, sizeOfPieceArr> pieceNumbersArr = {0, 1, 2};
	array<char, sizeOfPieceArr> pieceCharactersArr = {' ', 'O', 'X'};

	for(int i = 0; i < sizeOfPieceArr; i++)
	{
		numToCharConversionList.insert(pair<const int, char>(pieceNumbersArr[i], pieceCharactersArr[i]));
	}

	totalXsOnBoard_ = 0;
	totalOsOnBoard_ = 0;

	boardFatalError_ = false;
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
	const int ROW_CONST = multiplier_ * 100;
	const int COLMN_CONST = multiplier_ * 10;
	const int t_noPlayerPiece = GetConstantFromList(noPlayerPiece);
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
	//This makes errors less likely to happen later on
	
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
	totalOsOnBoard_ = 0;
	totalXsOnBoard_ = 0;
}

void Board::DisplayPiece(int &squareCount, int &temp2, int pieceSpacing)
{
	//Reset the text color just to be sure
	ResetConsoleColor();
	
	char pTemp;
	pTemp = XorO(piecePlacement[squareCount]);
	cout<<pTemp;
	temp2 += pieceSpacing;
	squareCount++;
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
	const int sizeOfBoardAcross = (5 * multiplier_) + 1;
	const int sizeOfBoardDown = (5 * multiplier_) + 1;
	
	const int boardStart = 0;

	const int endOfRowOneA = 2;
	const int endOfRowOneB = 3;
	const int endOfRowOneC = 4;
	
	const int startOfRowTwoA = 3;
	const int startOfRowTwoB = 4;
	const int startOfRowTwoC = 5;
	const int endOfRowTwoA = 5;
	const int endOfRowTwoB = 7;
	const int endOfRowTwoC = 9;
	
	const int startOfRowThreeA = 6;
	const int startOfRowThreeB = 8;
	const int startOfRowThreeC = 10;
	const int endOfRowThreeA = 8;
	const int endOfRowThreeB = 11;
	const int endOfRowThreeC = 14;
	
	const int startOfRowFourB = 12;
	const int startOfRowFourC = 15;
	const int endOfRowFourB = 15;
	const int endOfRowFourC = 19;
	
	const int startOfRowFiveC = 20;
	const int endOfRowFiveC = 24;	
 
	const int startOfColumnTwo = 1;
	const int startOfColumnThree = 2;
	const int startOfColumnFour = 3;
	const int startOfColumnFive = 4;

	//Constants for processing
	const int t_columnOne = GetConstantFromList(columnOne);
	const int t_columnTwo = GetConstantFromList(columnTwo);
	const int t_columnThree = GetConstantFromList(columnThree);
	const int t_columnFour = GetConstantFromList(columnFour);
	const int t_columnFive = GetConstantFromList(columnFive);

	const int t_rowOne = GetConstantFromList(rowOne);
	const int t_rowTwo = GetConstantFromList(rowTwo);
	const int t_rowThree = GetConstantFromList(rowThree);
	const int t_rowFour = GetConstantFromList(rowFour);
	const int t_rowFive = GetConstantFromList(rowFive);

	const char t_space = GetConstantFromList(GetConstantFromList(noPlayerPiece));

	bool playerOneWon = false;
	
	//Bool values to decide what pieces get highlighted on the board
	bool across = false;
	bool down = false;
	bool diagonal = false;
	bool diagonalLeft = false;
	bool diagonalRight = false;
	
	//Temp values
	int temp1 = 1;	//Used for vertical line spacing
	int temp2 = 3;	//Used for piece spacing
	int squareCount = 0;
	
	char winningPlayerPiece;
	
	//Winning player string
	string winningPlayer;
	
	try
	{
		if(pOne.DidPlayerWin())
		{
			const int lineSize = 46;
			system("cls");
			winningPlayerPiece = XorO(pOne.GetPiece());
			pOne.SetPlayerTextColor();
			cout<<"^o^ ---- Player 1 has won the game!!! ---- ^o^"<<endl;
			cout<<"-----------    Congratulations    ------------"<<endl;
			for(int i = 1; i <= 46; i++)
			{
				cout<<winningPlayerPiece;
				Sleep(50);
			}
			cout<<endl;
			cout<<"Press any key to continue..."<<endl;
			_getche();
			ResetConsoleColor();
			winningPlayer = "Player 1";
			playerOneWon = true;
		}
		else
		{
			const int lineSize = 46;
			system("cls");
			winningPlayerPiece = XorO(pTwo.GetPiece());
			pTwo.SetPlayerTextColor();
			cout<<"^o^ ---- Player 2 has won the game!!! ---- ^o^"<<endl;
			cout<<"-----------    Congratulations    ------------"<<endl;
			for(int i = 1; i <= 46; i++)
			{
				cout<<winningPlayerPiece;
				Sleep(50);
			}
			cout<<endl;
			cout<<"Press any key to continue..."<<endl;
			_getche();
			ResetConsoleColor();
			winningPlayer = "Player 2";
		}
	}
	catch(Exception &e)
	{
		if(e.GetErrorType() == err.Invalid_Variable_Access)
		{
			cout<<e.what()<<"\n";
			cout<<"Press any key to continue...\n";
			_getche();
			throw;
		}
		else
			throw;
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

	//Now iterate through and display the board with the proper highlights applied to the winning pieces
	for(int i = 1; i <= sizeOfBoardDown; i++)
	{
		temp1 += sizeOfSquareAcross;
		for(int j = 1; i <= sizeOfBoardAcross; i++)
		{
			switch(i)
			{
			case 1:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 2:
				ResetConsoleColor();
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
				if(playerOneWon)
					pOne.SetPlayerTextColor();
				else
					pTwo.SetPlayerTextColor();

				if(j == 1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft && squareCount == boardStart)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && diagonal && diagonalRight)
				{
					if((numOfSpaces_ == A && squareCount == endOfRowOneA) ||
					   (numOfSpaces_ == B && squareCount == endOfRowOneB) ||
					   (numOfSpaces_ == C && squareCount == endOfRowOneC))
					{
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}		 
				else if(j == temp2 && down && !across && !diagonal)
				{
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == boardStart)
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == startOfColumnTwo)
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == startOfColumnThree)
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == startOfColumnFour)
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == startOfColumnFive)
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowOne)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && !diagonal && !across && !down)
				{
					//If piece not winning, then reset the console color to a plain white
					//This only applies to the DisplayWinningBoard function
					ResetConsoleColor();
					DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else
				{
					ResetConsoleColor();
					cout<<t_space;
				}
				ResetConsoleColor();
				break;
			case 4:
				ResetConsoleColor();
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
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 6:
				ResetConsoleColor();
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
			case 7:
				if(playerOneWon)
					pOne.SetPlayerTextColor();
				else
					pTwo.SetPlayerTextColor();
				
				if(j == 1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					if(numOfSpaces_ == A && squareCount == (startOfRowTwoA + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == B && squareCount == (startOfRowTwoB + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (startOfRowTwoC + 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					if(numOfSpaces_ == A && squareCount == (endOfRowTwoA - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == B && squareCount == (endOfRowTwoB - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (endOfRowTwoC - 1))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFive + multiplier_))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowTwo)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && !diagonal && !across && !down)
				{
					ResetConsoleColor();
					DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else
				{
					ResetConsoleColor();
					cout<<t_space;
				}
				break;
			case 8:
				ResetConsoleColor();
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
			case 9:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 10:
				ResetConsoleColor();
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
			case 11:
				if(playerOneWon)
					pOne.SetPlayerTextColor();
				else
					pTwo.SetPlayerTextColor();

				if(j == 1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					if(numOfSpaces_ == A && squareCount == endOfRowThreeA)
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == B && squareCount == (startOfRowThreeB + 2))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (startOfRowThreeC + 2))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					if(numOfSpaces_ == A && squareCount == startOfRowThreeA)
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == B && squareCount == (endOfRowThreeB - 2))
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (endOfRowThreeC - 2))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + (multiplier_ * 2)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + (multiplier_ * 2)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + (multiplier_ * 2)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + (multiplier_ * 2)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFive + (multiplier_ * 2)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowThree)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && !diagonal && !across && !down)
				{
					ResetConsoleColor();
					DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else
				{
					ResetConsoleColor();
					cout<<t_space;
				}
				ResetConsoleColor();
				break;
			case 12:
				ResetConsoleColor();
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
			case 13:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 14:
				ResetConsoleColor();
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
			case 15:
				if(playerOneWon)
					pOne.SetPlayerTextColor();
				else
					pTwo.SetPlayerTextColor();

				if(j == 1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft)
				{
					if(numOfSpaces_ == B && squareCount == endOfRowFourB)
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (startOfRowFourC + 3))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && diagonal && diagonalRight)
				{
					if(numOfSpaces_ == B && squareCount == startOfRowFourB)
						DisplayPiece(squareCount, temp2, pieceSpacing);
					else if(numOfSpaces_ == C && squareCount == (endOfRowFourC - 3))
						DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else if(j == temp2 && down && !across && !diagonal)
				{
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + (multiplier_ * 3)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + (multiplier_ * 3)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + (multiplier_ * 3)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFour && (numOfSpaces_ == B || numOfSpaces_ == C))
					{
						if(squareCount == (startOfColumnFour + (multiplier_ * 3)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFive && numOfSpaces_ == C)
					{
						if(squareCount == (startOfColumnFour + (multiplier_ * 3)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFour)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && !diagonal && !across && !down)
				{
					ResetConsoleColor();
					DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else
				{
					ResetConsoleColor();
					cout<<t_space;
				}
				ResetConsoleColor();
				break;
			case 16:
				ResetConsoleColor();
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
			case 17:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 18:
				ResetConsoleColor();
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
			case 19:
				if(playerOneWon)
					pOne.SetPlayerTextColor();
				else
					pTwo.SetPlayerTextColor();

				if(j == 1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					ResetConsoleColor();
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal && diagonalLeft && squareCount == endOfRowFiveC)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && diagonal && diagonalRight && squareCount == startOfRowFiveC)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && down && !across && !diagonal)
				{
					if(acrossDownLocation == t_columnOne)
					{
						if(squareCount == (boardStart + (multiplier_ * 4)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnTwo)
					{
						if(squareCount == (startOfColumnTwo + (multiplier_ * 4)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnThree)
					{
						if(squareCount == (startOfColumnThree + (multiplier_ * 4)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFour)
					{
						if(squareCount == (startOfColumnFour + (multiplier_ * 4)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
					else if(acrossDownLocation == t_columnFive)
					{
						if(squareCount == (startOfColumnFive + (multiplier_ * 4)))
							DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else if(j == temp2 && across && !down && !diagonal && acrossDownLocation == t_rowFive)
					DisplayPiece(squareCount, temp2, pieceSpacing);
				else if(j == temp2 && !diagonal && !across && !down)
				{
					ResetConsoleColor();
					DisplayPiece(squareCount, temp2, pieceSpacing);
				}
				else
				{
					ResetConsoleColor();
					cout<<t_space;
				}
				ResetConsoleColor();
				break;
			case 20:
				ResetConsoleColor();
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
			case 21:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
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
	//Skip a line, for spacing
	cout<<endl;

	//Change color of text to that of winning players
	if(playerOneWon)
		pOne.SetPlayerTextColor();
	else
		pTwo.SetPlayerTextColor();

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
	const int sizeOfBoardAcross = (5 * multiplier_) + 1;
	const int sizeOfBoardDown = (4 * multiplier_) + 1;
	//Temporary variables
	int temp1 = 1;	//Used for vertical line spacing
	int temp2 = 3;	//Used for piece spacing
	int squareCount = 0;
	
	int p1Piece;
	int p2Piece;
	try
	{
		p1Piece = pOne.GetPiece();
		p2Piece = pTwo.GetPiece();
	}
	catch(Exception &e)
	{
		throw;
	}

	const char t_space = GetConstantFromList(GetConstantFromList(noPlayerPiece));

	//Going down then across
	for(int i = 1; i <= sizeOfBoardDown; i++) //Starting by going down 1
	{
		
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) //Then we go across, one character at a time. May get incremented further in for loop
		{
			switch (i)
			{
			case 1:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 2:
				ResetConsoleColor();
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
				ResetConsoleColor();
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
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else
					cout<<t_space;
				break;
			case 4:
				ResetConsoleColor();
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
				ResetConsoleColor();
				try
				{
					if(j == 1)
						cout<<t_space;
					else if(j == sizeOfBoardAcross)
						cout<<t_space<<"          Player 1: "<<pOne.GetName();
					else
						cout<<horizontalLine2;
				}
				catch(Exception &e)
				{
					cout<<e.what()<<"\n";
					cout<<"Press any key to continue...\n";
					_getche();
					throw;
				}
				break;
			case 6:
				ResetConsoleColor();
				try
				{
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
				}
				catch(Exception &e)
				{
					cout<<e.what()<<"\n";
					cout<<"Press any key to continue...\n";
					_getche();
					throw;
				}
				break;
			case 7:
				ResetConsoleColor();
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
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else
					cout<<t_space;
				break;
			case 8:
				ResetConsoleColor();
				try
				{
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
				}
				catch(Exception &e)
				{
					cout<<e.what()<<"\n";
					cout<<"Press any key to continue...\n";
					_getche();
					throw;
				}
				break;
			case 9:
				ResetConsoleColor();
				try
				{
					if(j == 1)
						cout<<t_space;
					else if(j == sizeOfBoardAcross)
						cout<<t_space<<"          Player 2's Score: "<<pTwo.GetScore();
					else
						cout<<horizontalLine2;
				}
				catch(Exception &e)
				{
					cout<<e.what()<<"\n";
					cout<<"Press any key to continue...\n";
					_getche();
					throw;
				}
				break;
			case 10:
				ResetConsoleColor();
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
			case 11:
				ResetConsoleColor();
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
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else
					cout<<t_space;
				break;
			case 12:
				ResetConsoleColor();
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
			case 13:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 14:
				ResetConsoleColor();
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
			case 15:
				ResetConsoleColor();
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
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else
					cout<<t_space;
				break;
			case 16:
				ResetConsoleColor();
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
			case 17:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
				else
					cout<<horizontalLine2;
				break;
			case 18:
				ResetConsoleColor();
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
			case 19:
				ResetConsoleColor();
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
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						pTwo.SetPlayerTextColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
						ResetConsoleColor();
					}
					else
					{
						ResetConsoleColor();
						DisplayPiece(squareCount, temp2, pieceSpacing);
					}
				}
				else
					cout<<t_space;
				break;
			case 20:
				ResetConsoleColor();
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
			case 21:
				ResetConsoleColor();
				if(j == 1 || j == sizeOfBoardAcross)
					cout<<t_space;
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
	int tens = 10 * multiplier_;
	int hundreds = 100 * multiplier_;
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

	try
	{
		ProcessSpaceList(location, playerPiece);
	}
	catch(Exception &e)
	{
		cout<<e.what()<<"\n";
		throw;
	}
	
	const int t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	if(playerPiece == t_xPlayerPiece)
		totalXsOnBoard_++;
	else
		totalOsOnBoard_++;

	ProcessSpaceList(location, playerPiece);
	ProcessPiecePlacementList();

	return true;
}

char Board::XorO(int num)
{
	//Remember...
	//1 = O
	//2 = X
	char returnPieceValue;
	
	
	//Constants for pieces
	const int t_noPlayerPiece = GetConstantFromList(noPlayerPiece);
	const int t_oPlayerPiece = GetConstantFromList(oPlayerPiece);
	const int t_xPlayerPiece = GetConstantFromList(xPlayerPiece);

	const char tempFatalErrorCharacter = '2';

	if(num == t_noPlayerPiece)
		returnPieceValue = GetConstantFromList(t_noPlayerPiece);
	else if(num == t_oPlayerPiece)
		returnPieceValue = GetConstantFromList(t_oPlayerPiece);
	else if(num == t_xPlayerPiece)
		returnPieceValue = GetConstantFromList(t_xPlayerPiece);
	else
	{
		//Error
		cout<<"There has beem a fatal error something happened in the function that\n";
		cout<<"called this one. Please take a look at the code for bugs...\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();

		returnPieceValue = tempFatalErrorCharacter;
	}

	return returnPieceValue;
}

WDPacketPtr Board::FindWinDraw()
{
	//Put these constants here because they only have to do with this function
	//Basically these are the same constants foung in the WinDrawPacket class
	//Ensures that there aren't any mistakes with the different codes

	
	//----TEMPORARY VALUES FOR TESTING ONLY----
	int tempGameOutcome = GetConstantFromList(winState);
	int tempPiece = GetConstantFromList(xPlayerPiece);
	int tempWinLocation = GetConstantFromList(diagonalWinType);
	int tempDiagonalLocation = GetConstantFromList(diagonalRightSubType);
	int tempRowLocation = GetConstantFromList(nullConstant);
	int tempColumnLocation = GetConstantFromList(nullConstant);
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
	int t_request = constListIter->second;

	return t_request;
}

char Board::GetConstantFromList(int request)
{
	PieceListIters_C CharConvListIter;
	CharConvListIter = numToCharConversionList.find(request);
	char t_request = CharConvListIter->second;

	return t_request;
}

const int Board::GetMultiplier() const
{
	return multiplier_;
}

const bool Board::GetFatalError() const
{
	return boardFatalError_;
}

const int Board::GetTotalNumOfPiecesOnBoard() const
{
	return (totalOsOnBoard_ + totalXsOnBoard_);
}