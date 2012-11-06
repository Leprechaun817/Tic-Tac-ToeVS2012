#include "Board.h"

//These constants are the characters/strings that make up the board
const string Board::horizontalLine1 = "-----";
const char Board::horizontalLine2 = '-';
const char Board::verticalLine = '|';
const char Board::space = ' ';
const char Board::oPiece = 'O';
const char Board::xPiece = 'X';

//Constants for character measurements of board
const int Board::sizeOfSquareAcross = 5;
const int Board::sizeOfSquareDown = 4;
const int Board::pieceSpacing = 5;
//The next 3 constants are the pieces that can be placed on the board. They are represented by their respective numbers 0,1, and 2
const int Board::noPiece = 0;
const int Board::O = 1;
const int Board::X = 2;
//These next 3 are the total number of squares that can make up a board at once
const int Board::A = 9;
const int Board::B = 16;
const int Board::C = 25;

Board::Board()
{
	hConsoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
	gameConstants = new WinDrawPacket();
	SetupBoard();
	system("cls");
	InitiateBoard();
}	

Board::~Board()
{
	//Clean up
	spaceList.clear();
	gameConstants->~WinDrawPacket();
	delete gameConstants;
}

void Board::SetupBoard()
{
	char input;
	bool answer = false;
	const int DIVIDER = 3;
	while(answer == false)	//Makes sure user enter in either a,b or c and not something else. It also alerts the user when this happens...
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
			multiplier = A / DIVIDER;
			numOfSpaces = A;
			answer = true;
		}
		else if(input == 'b' || input == 'B')
		{
			multiplier = B / (DIVIDER + 1);
			numOfSpaces = B;
			answer = true;
		}
		else if(input == 'c' || input == 'C')
		{
			multiplier = C / (DIVIDER + 2);
			numOfSpaces = C;
			answer = true;
		}
		else
		{
			cout<<"Please enter a choice as listed above."<<endl;
			cout<<"Try again..."<<endl;
			_getche();
		}
	}
}

void Board::InitiateBoard()
{
	spaceList.resize (numOfSpaces);
	const int ROW_CONST = multiplier * 100;
	const int COLMN_CONST = multiplier * 10;
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
	vector<int>::iterator spaceListIter;
	spaceListIter = spaceList.begin();
	for(int i = 100; i <= ROW_CONST; i += 100)
	{
		for(int j = 10; j <= COLMN_CONST; j += 10)
		{
			int space = i + j + noPiece;	//adds i,j, and the nopiece variable together to get us the number for the designated space
			*spaceListIter = space;			//adds number to the vector
			spaceListIter++;				//increments the vector							
		}
	}
}

void Board::DisplayPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing, int pieceColor)
{
	char pTemp;
	pTemp = XorO((*piecePlacement)[(*squareCount)], true);
	SetConsoleTextAttribute(hConsoleWindow, pieceColor);
	cout<<pTemp;
	ResetConsoleColor();
	*temp2 += pieceSpacing;
	*squareCount++;
}

void Board::DisplayWinningPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing, int playerColor)
{
	char pTemp;
	pTemp = XorO((*piecePlacement)[(*squareCount)], true);
	SetConsoleTextAttribute(hConsoleWindow, playerColor);
	cout<<pTemp;
	ResetConsoleColor();
	*temp2 += pieceSpacing;
	*squareCount++;
}

void Board::DisplayNonWinningPiece(const vector<int> *piecePlacement, int *squareCount, int *temp2, int pieceSpacing)
{
	//Reset the text color just to be sure
	ResetConsoleColor();
	
	char pTemp;
	pTemp = XorO((*piecePlacement)[(*squareCount)], true);
	cout<<pTemp;
	*temp2 += pieceSpacing;
	*squareCount++;
}

//TODO:
//Handle the winning player conditions, which will change the color of the piece
//Handle the text color change ahead of time so that all that will be necessary is a simple function call
//Must handle different board sizes as well
void Board::DisplayWinningBoard(bool playerOneWin, bool playerTwoWin, int type, int diagonalLocation, int acrossDownLocation, int playerOneColor, int playerTwoColor, int playerOnePiece, int playerTwoPiece)
{
	//Constants
	const int sizeOfBoardAcross = (5 * multiplier) + 1;
	const int sizeOfBoardDown = (5 * multiplier) + 1;
	
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
	
	//Winning players color
	int winningPieceColor;
	char winningPlayerPiece;
	
	//Winning player string
	string winningPlayer;
	//Vector to hold piece places
	vector<int> piecePlacement;
	piecePlacement.resize(numOfSpaces);

	//Iterators
	vector<int>::iterator piecePlaceIter;
	vector<int>::iterator spaceListIter;
	spaceListIter = spaceList.begin();

	string sTemp;
	stringstream ssTemp;
	for(piecePlaceIter = piecePlacement.begin(); piecePlaceIter != piecePlacement.end(); piecePlaceIter++)
	{
		sTemp.clear();
		ssTemp.clear();
		ssTemp<<*spaceListIter;
		ssTemp>>sTemp;

		ssTemp.clear();
		ssTemp<<sTemp[2];
		ssTemp>>*piecePlaceIter;

		spaceListIter++;
	}

	//----DEBUGGING CODE ONLY----//
	//Used to make sure that playerOneWin and playerTwoWin don't equal true at the same time or false at the same time
	//Produces an error message if any of the above conditions are true
	//This will get modified later to decide the color of the text
	if(playerOneWin == true && playerTwoWin == true)
	{
		cout<<"Error has occured. You can't have both players winning at the same time\n";
		cout<<"Press any key to continue...\n";
		_getche();
		return;
	}
	else if(playerOneWin == false && playerTwoWin == false)
	{
		cout<<"Error has occured. You can't have both players losing at the same time\n";
		cout<<"Press any key to continue...\n";
		_getche();
		return;
	}
	else if(playerOneWin == true && playerTwoWin == false)
	{
		const int lineSize = 46;
		system("cls");
		winningPieceColor = playerOneColor;
		winningPlayerPiece = XorO(playerOnePiece, true);
		SetConsoleTextAttribute(hConsoleWindow, winningPieceColor);
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
	}
	else if(playerOneWin == false && playerTwoWin == true)
	{
		const int lineSize = 46;
		system("cls");
		winningPieceColor = playerTwoColor;
		winningPlayerPiece = XorO(playerTwoPiece, true);
		SetConsoleTextAttribute(hConsoleWindow, winningPieceColor);
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
	//----!!!!END OF DEBUGGING CODE!!!!----//

	//Figure out where the pieces on the board should be highlighted
	if(type == gameConstants->GetConstAcross())
	{
		across = true;
	}
	else if(type == gameConstants->GetConstDown())
	{
		down = true;
	}
	else if(type == gameConstants->GetConstDiagonal())
	{
		diagonal = true;
		if(diagonalLocation == gameConstants->GetConstDiagonalLeft())
		{
			diagonalLeft = true;
		}
		else
		{
			diagonalRight = true;
		}
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
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 2:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 3:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal == true && diagonalLeft == true && squareCount == boardStart)
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == true && diagonalRight == true)
				{
					if((numOfSpaces == A && squareCount == endOfRowOneA) ||
					   (numOfSpaces == B && squareCount == endOfRowOneB) ||
					   (numOfSpaces == C && squareCount == endOfRowOneC))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}		 
				else if(j == temp2 && down == true && across == false && diagonal == false)
				{
					if(acrossDownLocation == gameConstants->GetConstColumnOne())
					{
						if(squareCount == boardStart)
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
					{
						if(squareCount == startOfColumnTwo)
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnThree())
					{
						if(squareCount == startOfColumnThree)
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFour() && (numOfSpaces == B || numOfSpaces == C))
					{
						if(squareCount == startOfColumnFour)
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFive() && numOfSpaces == C)
					{
						if(squareCount == startOfColumnFive)
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
				}
				else if(j == temp2 && across == true && down == false && diagonal == false && acrossDownLocation == gameConstants->GetConstRowOne())
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == false && across == false && down == false)
				{
					DisplayNonWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
				}
				else
				{
					cout<<space;
				}
				break;
			case 4:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 5:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 6:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 7:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal == true && diagonalLeft == true)
				{
					if(numOfSpaces == A && squareCount == (startOfRowTwoA + 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == B && squareCount == (startOfRowTwoB + 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (startOfRowTwoC + 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && diagonal == true && diagonalRight == true)
				{
					if(numOfSpaces == A && squareCount == (endOfRowTwoA - 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == B && squareCount == (endOfRowTwoB - 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (endOfRowTwoC - 1))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && down == true && across == false && diagonal == false)
				{
					if(acrossDownLocation == gameConstants->GetConstColumnOne())
					{
						if(squareCount == (boardStart + multiplier))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
					{
						if(squareCount == (startOfColumnTwo + multiplier))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnThree())
					{
						if(squareCount == (startOfColumnThree + multiplier))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFour() && (numOfSpaces == B || numOfSpaces == C))
					{
						if(squareCount == (startOfColumnFour + multiplier))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFive() && numOfSpaces == C)
					{
						if(squareCount == (startOfColumnFive + multiplier))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
				}
				else if(j == temp2 && across == true && down == false && diagonal == false && acrossDownLocation == gameConstants->GetConstRowTwo())
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == false && across == false && down == false)
				{
					DisplayNonWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
				}
				else
				{
					cout<<space;
				}
				break;
			case 8:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 9:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 10:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 11:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal == true && diagonalLeft == true)
				{
					if(numOfSpaces == A && squareCount == endOfRowThreeA)
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == B && squareCount == (startOfRowThreeB + 2))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (startOfRowThreeC + 2))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && diagonal == true && diagonalRight == true)
				{
					if(numOfSpaces == A && squareCount == startOfRowThreeA)
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == B && squareCount == (endOfRowThreeB - 2))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (endOfRowThreeC - 2))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && down == true && across == false && diagonal == false)
				{
					if(acrossDownLocation == gameConstants->GetConstColumnOne())
					{
						if(squareCount == (boardStart + (multiplier * 2)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
					{
						if(squareCount == (startOfColumnTwo + (multiplier * 2)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnThree())
					{
						if(squareCount == (startOfColumnThree + (multiplier * 2)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFour() && (numOfSpaces == B || numOfSpaces == C))
					{
						if(squareCount == (startOfColumnFour + (multiplier * 2)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFive() && numOfSpaces == C)
					{
						if(squareCount == (startOfColumnFive + (multiplier * 2)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
				}
				else if(j == temp2 && across == true && down == false && diagonal == false && acrossDownLocation == gameConstants->GetConstRowThree())
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == false && across == false && down == false)
				{
					DisplayNonWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
				}
				else
				{
					cout<<space;
				}
				break;
			case 12:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 13:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 14:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 15:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal == true && diagonalLeft == true)
				{
					if(numOfSpaces == B && squareCount == endOfRowFourB)
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (startOfRowFourC + 3))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && diagonal == true && diagonalRight == true)
				{
					if(numOfSpaces == B && squareCount == startOfRowFourB)
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
					else if(numOfSpaces == C && squareCount == (endOfRowFourC - 3))
					{
						DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
					}
				}
				else if(j == temp2 && down == true && across == false && diagonal == false)
				{
					if(acrossDownLocation == gameConstants->GetConstColumnOne())
					{
						if(squareCount == (boardStart + (multiplier * 3)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
					{
						if(squareCount == (startOfColumnTwo + (multiplier * 3)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnThree())
					{
						if(squareCount == (startOfColumnThree + (multiplier * 3)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFour() && (numOfSpaces == B || numOfSpaces == C))
					{
						if(squareCount == (startOfColumnFour + (multiplier * 3)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFive() && numOfSpaces == C)
					{
						if(squareCount == (startOfColumnFour + (multiplier * 3)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
				}
				else if(j == temp2 && across == true && down == false && diagonal == false && acrossDownLocation == gameConstants->GetConstRowFour())
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == false && across == false && down == false)
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else
				{
					cout<<space;
				}
				break;
			case 16:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 17:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 18:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 19:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2 && diagonal == true && diagonalLeft == true && squareCount == endOfRowFiveC)
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == true && diagonalRight == true && squareCount == startOfRowFiveC)
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && down == true && across == false && diagonal == false)
				{
					if(acrossDownLocation == gameConstants->GetConstColumnOne())
					{
						if(squareCount == (boardStart + (multiplier * 4)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
					{
						if(squareCount == (startOfColumnTwo + (multiplier * 4)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnThree())
					{
						if(squareCount == (startOfColumnThree + (multiplier * 4)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFour())
					{
						if(squareCount == (startOfColumnFour + (multiplier * 4)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
					else if(acrossDownLocation == gameConstants->GetConstColumnFive())
					{
						if(squareCount == (startOfColumnFive + (multiplier * 4)))
						{
							DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
						}
					}
				}
				else if(j == temp2 && across == true && down == false && diagonal == false && acrossDownLocation == gameConstants->GetConstRowFive())
				{
					DisplayWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, winningPieceColor);
				}
				else if(j == temp2 && diagonal == false && across == false && down == false)
				{
					DisplayNonWinningPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
				}
				else
				{
					cout<<space;
				}
				break;
			case 20:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 21:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
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
	SetConsoleTextAttribute(hConsoleWindow, winningPieceColor);

	//Tell how the player won
	if(diagonal == true && across == false && down == false)
	{
		if(diagonalLeft == true)
		{
			cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from left to right"<<endl;
		}
		if(diagonalRight == true)
		{
			cout<<winningPlayer<<" won with a diagonal line of "<<winningPlayerPiece<<"'s going from right to left"<<endl;
		}
	}
	else if(across == true && down == false && diagonal == false)
	{
		if(acrossDownLocation == gameConstants->GetConstRowOne())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 1"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstRowTwo())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 2"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstRowThree())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 3"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstRowFour())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 4"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstRowFive())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going across on row 5"<<endl;
		}
	}
	else if(down == true && across == false && diagonal == false)
	{
		if(acrossDownLocation == gameConstants->GetConstColumnOne())
		{
			cout<<winningPlayer<<" won with a line of "<<winningPlayerPiece<<"'s going down on column 1"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstColumnTwo())
		{
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 2"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstColumnThree())
		{
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 3"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstColumnFour())
		{
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 4"<<endl;
		}
		else if(acrossDownLocation == gameConstants->GetConstColumnFive())
		{
			cout<<winningPlayer<<" win with a line of "<<winningPlayerPiece<<"'s going down on column 5"<<endl;
		}
	}
	ResetConsoleColor();
	cout<<endl<<"Press any key to continue..."<<endl;
	_getche();
	system("cls");
}

//Board display function, displays the board and extra information line by line and character by character
//TODO:
//Add code to process win information from the WinDrawPacket generated by FindWinDraw function
void Board::DisplayBoard(int numRounds, int numTies, string p1Name, int p1Score, int p1Piece, int p1PieceColor, string p2Name, int p2Score, int p2Piece, int p2PieceColor)
{
	//Constants
	const int sizeOfBoardAcross = (5 * multiplier) + 1;
	const int sizeOfBoardDown = (4 * multiplier) + 1;
	//Temporary variables
	int temp1 = 1;	//Used for vertical line spacing
	int temp2 = 3;	//Used for piece spacing
	char pTemp;
	int squareCount = 0;
	//Vector to hold piece places
	vector<int> piecePlacement;
	piecePlacement.resize(numOfSpaces);
	
	//Iterator for vector piecePlacement
	vector<int>::iterator piecePlaceIter;
	//Iterator for spaceList
	vector<int>::iterator spaceListIter;
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
		

	//Going down then across
	for(int i = 1; i <= sizeOfBoardDown; i++) //Starting by going down 1
	{
		
		temp1 += sizeOfSquareAcross;
		for(int j = 1; j <= sizeOfBoardAcross; j++) //Then we go across, one character at a time. May get incremented further in for loop
		{
			switch (i)
			{
			case 1:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 2:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<verticalLine<<"          Round: "<<numRounds;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 3:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<verticalLine<<"          Ties: "<<numTies;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					//This is a test. Don't delete the old lines yet until this has been tested
					if(piecePlacement[squareCount] == p1Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p1PieceColor);
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p2PieceColor);
					}
					else
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
					}
					//pTemp = XorO(piecePlacement[squareCount], true);
					//cout<<pTemp;
					//temp2 += pieceSpacing;
					//squareCount++;
				}
				else
				{
					cout<<space;
				}
				//Reset pTemp here because it will get used again before this for loop cycles again
				//Just to be on the safe side, this way if there is an error. You don't get a board full
				//of Xs or Os
				pTemp = ' ';
				break;
			case 4:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 5:
				if(j == 1)
				{
					cout<<space;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<space<<"          Player 1: "<<p1Name;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 6:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<verticalLine<<"          Player 1's Score: "<<p1Score;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 7:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p1PieceColor);
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p2PieceColor);
					}
					else
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
					}
					//pTemp = XorO(piecePlacement[squareCount], true);
					//cout<<pTemp;
					//temp2 += pieceSpacing;
					//squareCount++;
				}
				else
				{
					cout<<space;
				}
				pTemp = ' ';
				break;
			case 8:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<verticalLine<<"          Player 2: "<<p2Name;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 9:
				if(j == 1)
				{
					cout<<space;
				}
				else if(j == sizeOfBoardAcross)
				{
					cout<<space<<"          Player 2's Score: "<<p2Score;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 10:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 11:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p1PieceColor);
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p2PieceColor);
					}
					else
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
					}
					//pTemp = XorO(piecePlacement[squareCount], true);
					//cout<<pTemp;
					//temp2 += pieceSpacing;
					//squareCount++;
				}
				else
				{
					cout<<space;
				}
				pTemp = ' ';
				break;
			case 12:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 13:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 14:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 15:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p1PieceColor);
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p2PieceColor);
					}
					else
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
					}
					//pTemp = XorO(piecePlacement[squareCount], true);
					//cout<<pTemp;
					//temp2 += pieceSpacing;
					//squareCount++;
				}
				else
				{
					cout<<space;
				}
				pTemp = ' ';
				break;
			case 16:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 17:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
				break;
			case 18:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 19:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else if(j == temp2)
				{
					if(piecePlacement[squareCount] == p1Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p1PieceColor);
					}
					else if(piecePlacement[squareCount] == p2Piece)
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing, p2PieceColor);
					}
					else
					{
						DisplayPiece(&piecePlacement, &squareCount, &temp2, pieceSpacing);
					}
					//pTemp = XorO(piecePlacement[squareCount], true);
					//cout<<pTemp;
					//temp2 += pieceSpacing;
					//squareCount++;
				}
				else
				{
					cout<<space;
				}
				pTemp = ' ';
				break;
			case 20:
				if(j == 1)
				{
					cout<<verticalLine;
				}
				else if(j == temp1)
				{
					cout<<verticalLine;
					temp1 += sizeOfSquareAcross;
				}
				else
				{
					cout<<space;
				}
				break;
			case 21:
				if(j == 1 || j == sizeOfBoardAcross)
				{
					cout<<space;
				}
				else
				{
					cout<<horizontalLine2;
				}
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
		//Reset pTemp, just to be sure
		pTemp = ' ';
	}
}

void Board::ResetBoard()
{
	spaceList.clear();
	system("cls");
	SetupBoard();
	system("cls");
	InitiateBoard();
}

int Board::BoardRefresh(int playerPiece, int location, bool playerOneMoveStatus, bool playerTwoMoveStatus)
{
	const int noError = 4;
	const int error0 = 0;
	const int error1 = 1;
	const int error2 = 2;
	int valueGood = -1;
	vector<int>::iterator spaceListIter;
	for(spaceListIter = spaceList.begin(); spaceListIter != spaceList.end(); spaceListIter++)
	{
		if(location == *spaceListIter)
		{
			//location matched location on grid exactly. No piece already exists here. Add in piece, return noError
			*spaceListIter += playerPiece;
			valueGood = noError;
			//If location gets matched, the loop ends. No reason to stay in the loop at this point
			break;
		}
		else if((location + 1) == *spaceListIter || (location + 2) == *spaceListIter)
		{
			//location given already has a piece added into it, return error1
			valueGood = error1;
			//Error found, loop ending
			break;
		}
	}

	if((valueGood != error1 && valueGood != noError) && (playerOneMoveStatus == false && playerTwoMoveStatus == false))
	{
		valueGood = 0;
	}

	return valueGood;
}

char Board::XorO(int num, bool special)
{
	//Remember...
	//1 = O
	//2 = X
	string number;
	int pieceType;
	char returnPiece;
	stringstream s; //Declared a stringstream variable for input and output only to convert the interger num into a string.
	                                                        //Makes it easier to evaluate what the last number is in the sequence.
	s<<num;
	s>>number;

	if(special == false)
	{
		s.clear();
		s<<number[2];
		s>>pieceType;
		
		if(pieceType == noPiece)
		{
			returnPiece = space;
		}
		else if(pieceType == O)
		{
			returnPiece = oPiece;
		}
		else if(pieceType = X)
		{
			returnPiece = xPiece;
		}
		else	//Added this else as a just in case, it'll probably never get run. But I'm going to leave it for now.
		{
			returnPiece = space;
		}
	}
	else
	{
		s.clear();
		s<<number[0];
		s>>pieceType;
		
		if(pieceType == noPiece)
		{
			returnPiece = space;
		}
		else if(pieceType == O)
		{
			returnPiece = oPiece;
		}
		else if(pieceType == X)
		{
			returnPiece = xPiece;
		}
		else
		{
			returnPiece = space;
		}
	}
	return returnPiece;
}

string Board::CreatePrePacket(int gameOutcome, int piece, int winLocation, int diagonalLocation, int rowLocation, int columnLocation)
{
	//Function Constants
	const int entries = 6;
	const int streamSize = 11;

	//Regular Variables
	string prePacket;
	string prePacketStream[streamSize];
	stringstream ss;
	
	//If there is no win or draw just fill the stream with nullConstants as there is no win data anyways
	if(gameOutcome == gameConstants->GetConstNoWinDraw() || gameOutcome == gameConstants->GetConstDraw())
	{
		char tempDelimiter = gameConstants->GetConstDelimiter();
		int tempNullConstant = gameConstants->GetConstNullConstant();
		
		ss.clear();
		ss<<gameOutcome;
		ss>>prePacketStream[0];
		ss.clear();

		prePacketStream[1] = tempDelimiter;
		if(gameOutcome == gameConstants->GetConstDraw())
		{
			ss<<piece;
			ss>>prePacketStream[2];
			ss.clear();
		}
		else
		{
			prePacketStream[2] = tempNullConstant;
		}
		prePacketStream[3] = tempDelimiter;
		prePacketStream[4] = tempNullConstant;
		prePacketStream[5] = tempDelimiter;
		prePacketStream[6] = tempNullConstant;
		prePacketStream[7] = tempDelimiter;
		prePacketStream[8] = tempNullConstant;
		prePacketStream[9] = tempDelimiter;
		prePacketStream[10] = tempNullConstant;
	}
	//If there is a win go through and build a complete prePacket
	else if(gameOutcome == gameConstants->GetConstWin())
	{
		ss.clear();
		int entryCount = 1;
		for(int i = 0; i < streamSize; i++)
		{
			if((i % 2) != 0)
			{
				prePacketStream[i] = gameConstants->GetConstDelimiter();
			}
			else
			{
				switch(entryCount)
				{
				case 1:
					ss<<gameOutcome;
					ss>>prePacketStream[i];
					ss.clear();
					entryCount++;
					break;
				case 2:
					if(piece == O)
					{
						prePacketStream[i] = oPiece;
					}
					else if(piece == X)
					{
						prePacketStream[i] = xPiece;
					}
					else
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					entryCount++;
					break;
				case 3:
					if(winLocation == gameConstants->GetConstAcross() || winLocation == gameConstants->GetConstDown())
					{
						ss<<winLocation;
						ss>>prePacketStream[i];
						ss.clear();
						entryCount++;
					}
					else if(winLocation == gameConstants->GetConstDiagonal())
					{
						ss<<winLocation;
						ss>>prePacketStream[i];
						ss.clear();
						if(diagonalLocation == gameConstants->GetConstDiagonalLeft() || diagonalLocation == gameConstants->GetConstDiagonalRight())
						{
							ss<<diagonalLocation;
							ss>>prePacketStream[(i + 2)];
							ss.clear();
						}
						else
						{
							ss<<gameConstants->GetConstFatalError();
							ss>>prePacketStream[(i + 2)];
							ss.clear();
						}
						entryCount++;
						entryCount++;

					}
					else
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
						entryCount++;
					}
					break;
				case 4:
					int tempNum1;
					ss<<prePacketStream[(i - 2)];
					ss>>tempNum1;
					ss.clear();
					
					if(tempNum1 == gameConstants->GetConstFatalError())
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					else
					{
						ss<<gameConstants->GetConstNullConstant();
						ss>>prePacketStream[i];
						ss.clear();
					}
					entryCount++;
					break;
				case 5:
					int tempNum2;
					ss<<prePacketStream[(i - 4)];
					ss>>tempNum2;
					ss.clear();

					if(tempNum2 == gameConstants->GetConstFatalError())
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					else if(winLocation == gameConstants->GetConstAcross())
					{
						if(rowLocation == gameConstants->GetConstRowOne() ||
						   rowLocation == gameConstants->GetConstRowTwo() ||
						   rowLocation == gameConstants->GetConstRowThree() ||
						   rowLocation == gameConstants->GetConstRowFour() ||
						   rowLocation == gameConstants->GetConstRowFive())
						{
							ss<<rowLocation;
							ss>>prePacketStream[i];
							ss.clear();
						}
						else
						{
							ss<<gameConstants->GetConstFatalError();
							ss>>prePacketStream[i];
							ss.clear();
						}
					}
					else if(winLocation == gameConstants->GetConstDown())
					{
						ss<<gameConstants->GetConstNullConstant();
						ss>>prePacketStream[i];
						ss.clear();
					}
					else
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					entryCount++;
					break;
				case 6:
					int temp3;
					ss<<prePacketStream[(i - 6)];
					ss>>temp3;
					ss.clear();

					if(temp3 == gameConstants->GetConstFatalError())
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					else if(winLocation == gameConstants->GetConstDown())
					{
						if(columnLocation == gameConstants->GetConstColumnOne() ||
						   columnLocation == gameConstants->GetConstColumnTwo() ||
						   columnLocation == gameConstants->GetConstColumnThree() ||
						   columnLocation == gameConstants->GetConstColumnFour() ||
						   columnLocation == gameConstants->GetConstColumnFive())
						{
							ss<<columnLocation;
							ss>>prePacketStream[i];
							ss.clear();
						}
						else
						{
							ss<<gameConstants->GetConstFatalError();
							ss>>prePacketStream[i];
							ss.clear();
						}
					}
					else if(winLocation == gameConstants->GetConstAcross())
					{
						ss<<gameConstants->GetConstNullConstant();
						ss>>prePacketStream[i];
						ss.clear();
					}
					else
					{
						ss<<gameConstants->GetConstFatalError();
						ss>>prePacketStream[i];
						ss.clear();
					}
					break;
				}
			}
		}
	}

	prePacket.clear();
	for(int i = 0; i < streamSize; i++)
	{
		prePacket += prePacketStream[i];
	}

	return prePacket;
}

WinDrawPacket& Board::FindWinDraw()
{
	//Put these constants here because they only have to do with this function
	//Basically these are the same constants foung in the WinDrawPacket class
	//Ensures that there aren't any mistakes with the different codes

	//----TEMPORARY VALUES FOR TESTING ONLY----
	int tempGameOutcome = gameConstants->GetConstWin();
	int tempPiece = X;
	int tempWinLocation = gameConstants->GetConstDiagonal();
	int tempDiagonalLocation = gameConstants->GetConstDiagonalRight();
	int tempRowLocation = gameConstants->GetConstNullConstant();
	int tempColumnLocation = gameConstants->GetConstNullConstant();
	//----ABOVE VALUES ARE TEMPORARY----
	//----FOR TESTING PURPOSES ONLY----

	WinDrawPacket *packet;
	string prePacket = CreatePrePacket(tempGameOutcome, tempPiece, tempWinLocation, tempDiagonalLocation, tempRowLocation, tempColumnLocation);
	packet = new WinDrawPacket();
	packet->CreatePacket(prePacket);
	return *packet;
}

void Board::ResetConsoleColor()
{
	int dark_white = 7 % 16;
	SetConsoleTextAttribute(hConsoleWindow, dark_white);
}