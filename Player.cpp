#include "Player.h"

int Player::numOfPlayers = 0;
int Player::otherPlayerPiece = 0;
const int Player::answerSize = 3;

const string Player::noPlayerPiece = "noPlayerPiece";
const string Player::oPlayerPiece = "oPlayerPiece";
const string Player::xPlayerPiece = "xPlayerPiece";

Player::Player(const ConstList &cList)
	: textColor()
{
	//if...else... here is used becuase of the fact that numOfPlayers is a static variable so if this class has been
	//instantiated once this variable will already have a value. So the constructor has to check for that and account for it.
	if(numOfPlayers == 0)	//if numOfPlayers hasn't been used before
	{
		numOfPlayers = 1;
	}
	else	//if numOfPlayers has been used before
	{
		numOfPlayers++;
	}

	//ID will equal the current number of players, which normally won't be more than 2 anyways.
	//Might as well code for expansion anyways though
	id = numOfPlayers;
	score = 0;
	AssignPlayerPiece();	

	madeMove = false;
	playerInitialized = false;

	(*this).constantsList = cList;

	resetPlayerFunctionCalled = false;
}

Player::~Player()
{}

void Player::InitializePlayer(int boundsLimit)
{
	(*this).boundsLimit = boundsLimit;

	//Ask player for name
	//Had to put it here because I need the ID for the prompt...
	string n;
	cout<<"Player "<<id<<": What is your name?"<<endl;
	cin>>n;

	//Assigning string value n to name
	name = n;

	textColor.DecidePlayerScreenColor();

	//Player has now been initialized
	playerInitialized = true;
	
	//Decide player turn order (Who goes first and second)
}

void Player::AssignPlayerPiece()
{
	//Decide on piece for player
	//1 = O
	//2 = X
	if(otherPlayerPiece == 0) //if otherPlayerPiece hasn't been filled yet, which means that player 1 hasn't been assigned a piece
	{
		int piece = PieceGen();
		playerPiece = piece;
		otherPlayerPiece = piece;
	}
	else
	{
		if(otherPlayerPiece == 1)
		{
			playerPiece = 2;
		}
		else
		{
			playerPiece = 1;
		}

		resetPlayerFunctionCalled = false;
	}
}

void Player::DecidePlayerTurnOrder()
{
	//Order of play decided by who has which pieces
	//X's go first
	//O's go second
	if(playerPiece == 1)
		;
}

//Make sure to call this after AssignPlayerPiece is called. This is very important!!!
void Player::ResetPlayer(int boundsLimit)
{
	madeMove = false;
	playerPiece = 0;
	//Set boundsLimit
	(*this).boundsLimit = boundsLimit;
	AssignPlayerPiece();
}

//This must be called before ResetPlayer has been called in order for this to work correctly
void Player::ResetPlayerPiece()
{
	if(resetPlayerFunctionCalled == false)
	{
		otherPlayerPiece = 0;
		resetPlayerFunctionCalled = true;
	}
	else
	{
		cout<<"This function has already been called,\n";
		cout<<"You can't call this again...\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();
	}
}

int Player::PieceGen()
{
	int temp = (rand()%40)+1;	//Simple random number generator, nothing special
	int num;

	if(temp >= 1 && temp <= 20)
	{
		num = 1;
	}

	if(temp >= 21 && temp <= 40)
	{
		num = 2;
	}

	return num;
}

void Player::DisplayName()
{
	cout<<"Player "<<id<<": "<<name;
}

void Player::DisplayScore()
{
	cout<<"Player "<<id<<"'s score is: "<<score;
}

void Player::UpdateScore()
{
	//This function only incrememnts the score by 1.
	//This way there's no way to change the score by adding more than one at the same time
	score++;
	//Quite simple really...
}

bool Player::MakeMove()
{
	bool answer = false;
	bool continuePlay = true;
	DisplayName();
	string choice;
	cout<<endl;
	cout<<"Enter in your choice below..."<<endl;
	cout<<"Ex. 1,1 or q to quit the game"<<endl;
	cin>>choice;
	while(answer == false)
	{
		//Used unsigned int here because move.size is also an unsigned integer.
		//Keeps warning messages about type mismatches from showing up in the compiler window...
		for(unsigned int i = 0; i < move.size(); i++)	//Don't know size of string at this time.
		{
			if(move[i] == 'q' || move[i] == 'Q')	//Searching the whole string looking for an instance of q or Q
			{
				//Player wishes to quit the current game
				continuePlay = false;
				//Break out of loop as there's no need to continue
				break;
			}
		}

		//If continuePlay is false, skip the move check and exit out of loop and function right away
		//The call for quiting will propogate from this function
		if(continuePlay == false)
		{
			//break out of loop
			break;
		}
		else
		{
			answer = CheckPlayerMove();
			//This if...then... is only evaluated when continuePlay is true
			//This way it won't ask you to re-enter your move after typing a q or Q into the prompt
			if(answer == false)
			{
				cout<<"Please enter your move again..."<<endl;
				cin>>move;
			}
		}
	}

	return continuePlay;
}

bool Player::CheckPlayerMove(string choice)
{
	//stringstream for converstion
	stringstream s;

	//temporary strings to store numbers in while waiting for converstion into integers
	string temp1 = move.substr(0,1);
	string temp3 = move.substr(2,1);

	int part1 = 0;
	char part2 = move[1];
	int part3 = 0;

	s.clear();
	//Converting temp1
	s<<temp1;
	s>>part1;
	s.clear();
	//Converting temp2
	s<<temp3;
	s>>part3;
	 
	if(move.size() > answerSize)
	{
		cout<<"Your move was to long, please re-enter your\n";
		cout<<"move in the proper format..."<<endl;
		return false;
	}
	else if(move.size() < answerSize)
	{
		cout<<"Your move was to short, please re-enter your\n";
		cout<<"move in the proper format..."<<endl;
		return false;
	}
	else if(part1 < 1 || part1 > boundsLimit)
	{
		cout<<"First number is to high, please enter in a lower value"<<endl;
		return false;
	}
	else if(part3 < 1 || part3 > boundsLimit)
	{
		cout<<"Third number is to high, please enter in a lower value"<<endl;
		return false;
	}
	else if(part2 != ',')
	{
		cout<<"Your move must have a comma in between the 2 numbers"<<endl;
		return false;
	}

	return true;
}

int Player::GetTextColor() const
{
	return textColor.GetColorAttribute();
}