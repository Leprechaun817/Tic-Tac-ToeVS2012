#include "Player.h"

int Player::numOfPlayers_ = 0;
int Player::otherPlayerPiece_ = 0;
const int Player::answerSize = 3;

const string Player::noPlayerPiece = "noPlayerPiece";
const string Player::oPlayerPiece = "oPlayerPiece";
const string Player::xPlayerPiece = "xPlayerPiece";

Player::Player()
	: textColor()
{
	//if...else... here is used becuase of the fact that numOfPlayers is a static variable so if this class has been
	//instantiated once this variable will already have a value. So the constructor has to check for that and account for it.
	if(numOfPlayers_ == 0)	//if numOfPlayers hasn't been used before
		numOfPlayers_ = 1;
	else	//if numOfPlayers has been used before
		numOfPlayers_++;

	//ID will equal the current number of players, which normally won't be more than 2 anyways.
	//Might as well code for expansion anyways though
	id_ = numOfPlayers_;
	score_ = 0;
	AssignPlayerPiece();	

	madeMove_ = false;
	playerInitialized_ = false;
	win_ = false;

	resetPlayerFunctionCalled_ = false;
}

Player::~Player()
{}

void Player::InitializePlayer(int boundsLimit, const ConstList &cList)
{
	(*this).boundsLimit_ = boundsLimit;
	(*this).constantsList = cList;

	//Ask player for name
	//Had to put it here because I need the ID for the prompt...
	string n;
	cout<<"Player "<<id_<<": What is your name?"<<endl;
	cin>>n;

	//Assigning string value n to name
	name_ = n;

	textColor.DecidePlayerScreenColor();

	//Player has now been initialized
	playerInitialized_ = true;
}

void Player::AssignPlayerPiece()
{
	//Decide on piece for player
	//1 = O
	//2 = X
	if(otherPlayerPiece_ == 0) //if otherPlayerPiece hasn't been filled yet, which means that player 1 hasn't been assigned a piece
	{
		int piece = PieceGen();
		playerPiece_ = piece;
		otherPlayerPiece_ = piece;
	}
	else
	{
		if(otherPlayerPiece_ == 1)
			playerPiece_ = 2;
		else
			playerPiece_ = 1;

		resetPlayerFunctionCalled_ = false;
	}
}

//Make sure to call this after AssignPlayerPiece is called. This is very important!!!
void Player::ResetPlayer(int boundsLimit)
{
	madeMove_ = false;
	playerPiece_ = 0;
	move_ = 0;
	//Set boundsLimit
	(*this).boundsLimit_ = boundsLimit;
	AssignPlayerPiece();
}

//This must be called before ResetPlayer has been called in order for this to work correctly
void Player::ResetPlayerPiece()
{
	if(resetPlayerFunctionCalled_ == false)
	{
		otherPlayerPiece_ = 0;
		resetPlayerFunctionCalled_ = true;
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
		num = 1;

	if(temp >= 21 && temp <= 40)
		num = 2;

	return num;
}

void Player::DisplayName()
{
	cout<<"Player "<<id_<<": "<<name_;
}

void Player::DisplayScore()
{
	cout<<"Player "<<id_<<"'s score is: "<<score_;
}

void Player::UpdateScore()
{
	//This function only incrememnts the score by 1.
	//This way there's no way to change the score by adding more than one at the same time
	score_++;
	//Quite simple really...
}

int Player::MakeMove()
{
	int answer;
	const int quit = 0;
	
	DisplayName();
	string choice;
	cout<<endl;
	cout<<"Enter in your choice below...\n";
	cout<<"Ex. 1,1 or q to quit the game"<<endl;
	cin>>choice;

	bool checkMove = true;
	bool loop = false;
	while(loop == false)
	{
		//Used unsigned int here because move.size is also an unsigned integer.
		//Keeps warning messages about type mismatches from showing up in the compiler window...
		for(unsigned int i = 0; i < choice.size(); i++)	//Don't know size of string at this time.
		{
			if(choice[i] == 'q' || choice[i] == 'Q')	//Searching the whole string looking for an instance of q or Q
			{
				answer = quit;
				loop = true; //Just in case
				return answer;
			}
		}

		checkMove = CheckMoveFormat(choice);
		if(checkMove == false)
		{
			cout<<"Please re-enter your choice\n";
			cin>>choice;
		}
		else
		{
			answer = ReformatMove(choice);
			loop = true;
		}
	}

	madeMove_ = true;

	return answer;
}

bool Player::CheckMoveFormat(string choice)
{
	const unsigned int sizeOfMove = 3;
	const char middleCharacter = ',';

	if(choice.size() > sizeOfMove)
	{
		cout<<"Your entry has to many characters, please try again...\n";
		return false;
	}
	else if(choice.size() < sizeOfMove)
	{
		cout<<"Your entry has to few characters, please try again...\n";
		return false;
	}
	else if(choice[1] != middleCharacter)
	{
		cout<<"Your entry must have a comma in it, please try again...\n";
		return false;
	}
	else
		//Move format is good, return true
		return true;
}

int Player::ReformatMove(string choice)
{
	const int hundred = 100;
	const int ten = 10;
	
	stringstream ss;
	ss.clear();

	int firstNumber;
	int secondNumber;
	int returnNumber;

	ss<<choice[0];
	ss>>firstNumber;
	ss.clear();

	ss<<choice[2];
	ss>>secondNumber;
	ss.clear();

	firstNumber *= hundred;
	secondNumber *= ten;
	returnNumber = firstNumber + secondNumber;

	return returnNumber;
}

const void Player::SetPlayerTextColor() const
{
	textColor.SetTextToPlayerColor();
}

bool Player::HasPlayerMadeMove()
{
	bool returnValue;
	if(madeMove_ == true)
	{
		returnValue = true;
		madeMove_ = false;
	}
	else
	{
		returnValue = false;
		madeMove_ = true;
	}

	return returnValue;
}

const int Player::GetID() const
{
	if(playerInitialized_ == true)
		return id_;
	else
	{
		cout<<"This Player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const int Player::GetPiece() const
{
	if(playerInitialized_ == true)
		return playerPiece_;
	else
	{
		cout<<"This Player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return 666;
	}
}

const string Player::GetName() const
{
	if(playerInitialized_ == true)
		return name_;
	else
	{
		cout<<"This player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue..."<<endl;
		_getche();
		return "666";
	}
}

const int Player::GetScore() const
{
	if(playerInitialized_ == true)
		return score_;
	else
	{
		cout<<"This player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue...\n";
		_getche();
		return 666;
	}
}

const int Player::GetMove() const
{
	if(playerInitialized_ == true)
		return move_;
	else
	{
		cout<<"This player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue...\n";
		_getche();
		return 666;
	}
}

const bool Player::DidPlayerWin() const
{
	if(playerInitialized_ == true)
		return win_;
	else
	{
		cout<<"This player has not been initialized yet,\n";
		cout<<"Please run the initialization function...\n";
		cout<<"Press any key to continue...\n";
		_getche();
		return 666;
	}
}

void Player::SetPlayerWon()
{
	win_ = true;
}