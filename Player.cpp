#include "Player.h"

int Player::numOfPlayers_ = 0;
int Player::otherPlayerPiece_ = 0;
const int Player::answerSize = 3;

const string Player::noPlayerPiece = "noPlayerPiece";
const string Player::oPlayerPiece = "oPlayerPiece";
const string Player::xPlayerPiece = "xPlayerPiece";
const string Player::varError = "Player has not been initialized yet,\nplease run initialization function before use.";

Player::Player()
	: textColor(), score_(0), madeMove_(false), playerInitialized_(false), win_(false), resetPlayerFunctionCalled_(false)
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
	AssignPlayerPiece();	
}

void Player::InitializePlayer(int boundsLimit, const ConstList &cList)
{
	(*this).boundsLimit_ = boundsLimit;
	(*this).constantsList = cList;

	//Clear the screen
	system("cls");
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
		playerPiece_ = otherPlayerPiece_ = PieceGen();
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
	if(!resetPlayerFunctionCalled_)
	{
		otherPlayerPiece_ = 0;
		resetPlayerFunctionCalled_ = true;
	}
	else
		throw Exception(err.Double_Function_Call);
}

int Player::PieceGen()
{
	int temp = (rand()%40)+1;	//Simple random number generator, nothing special

	if(temp >= 1 && temp <= 20)
		return 1;

	if(temp >= 21 && temp <= 40)
		return 2;
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
	score_++;
}

bool Player::MakeMove()
{
	DisplayName();
	string choice;
	cout<<endl;
	cout<<"Enter in your choice below...\n";
	cout<<"Ex. 1,1 or q to quit the game"<<endl;
	cin>>choice;

	bool checkMove = true;
	bool loop = false;
	while(!loop)
	{
		//Used unsigned int here because move.size is also an unsigned integer.
		//Keeps warning messages about type mismatches from showing up in the compiler window...
		for(unsigned int i = 0; i < choice.size(); i++)	//Don't know size of string at this time.
		{
			if(choice[i] == 'q' || choice[i] == 'Q')	//Searching the whole string looking for an instance of q or Q
			{
				move_ = -1;
				loop = true; //Just in case
				return false;
			}
		}

		checkMove = CheckMoveFormat(choice);
		if(!checkMove)
		{
			cout<<"Please re-enter your choice\n";
			cin>>choice;
		}
		else
		{
			move_ = ReformatMove(choice);
			loop = true;
		}
	}

	madeMove_ = true;

	return true;
}

bool Player::CheckMoveFormat(string choice)
{
	const string toManyCharacters = "Your entry has to many characters, please try again...", toFewCharacters = "Your entry has to few characters, please try again...",
				 noComma = "Your entry must have a comma in it, please try again...";
	
	const unsigned int sizeOfMove = 3;
	const char middleCharacter = ',';

	if(choice.size() > sizeOfMove)
		throw Exception(err.Move_Format_Invalid, toManyCharacters);
	else if(choice.size() < sizeOfMove)
		throw Exception(err.Move_Format_Invalid, toFewCharacters);
	else if(choice[1] != middleCharacter)
		throw Exception(err.Move_Format_Invalid, noComma);
	else
		//Move format is good, return true
		return true;
}

int Player::ReformatMove(string choice)
{
	const int hundred = 100, ten = 10;
	
	stringstream ss;
	ss.clear();

	int firstNumber, secondNumber;

	ss<<choice[0];
	ss>>firstNumber;
	ss.clear();

	ss<<choice[2];
	ss>>secondNumber;
	ss.clear();

	firstNumber *= hundred;
	secondNumber *= ten;
	
	return (firstNumber + secondNumber);
}

const void Player::SetPlayerTextColor() const
{
	textColor.SetTextToPlayerColor();
}

bool Player::HasPlayerMadeMove()
{
	//Only reset the madeMove_ value if it has already been made true
	if(madeMove_)
	{
		madeMove_ = false;
		return true;
	}
	else
		return false;
}

const int Player::GetID() const
{
	if(playerInitialized_)
		return id_;
	else
		throw Exception(err.Invalid_Variable_Access, varError); 
}

const int Player::GetPiece() const
{
	if(playerInitialized_)
		return playerPiece_;
	else
		throw Exception(err.Invalid_Variable_Access, varError);
}

const string Player::GetName() const
{
	if(playerInitialized_)
		return name_;
	else
		throw Exception(err.Invalid_Variable_Access, varError);
}

const int Player::GetScore() const
{
	if(playerInitialized_)
		return score_;
	else
		throw Exception(err.Invalid_Variable_Access, varError);
}

const int Player::GetMove() const
{
	if(playerInitialized_)
		return move_;
	else
		throw Exception(err.Invalid_Variable_Access, varError);
}

const bool Player::DidPlayerWin() const
{
	if(playerInitialized_)
		return win_;
	else
		throw Exception(err.Invalid_Variable_Access, varError);
}

void Player::SetPlayerWon()
{
	win_ = true;
}