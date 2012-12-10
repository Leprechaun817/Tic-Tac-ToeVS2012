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

#include "Player.h"

int Player::numOfPlayers_ = 0;
int Player::otherPlayerPiece_ = 0;

const std::string Player::noPlayerPiece = "noPlayerPiece";
const std::string Player::oPlayerPiece = "oPlayerPiece";
const std::string Player::xPlayerPiece = "xPlayerPiece";
const std::string Player::varError = "Player has not been initialized yet,\nplease run initialization function before use.";

const std::string Player::badMoveErrorSound = "badMoveErrorSound";
const std::string Player::fatalErrorSound = "fatalErrorSound";

Player::Player() throw()
	: textColor(), score_(0), madeMove_(false), playerInitialized_(false), win_(false), resetPlayerFunctionCalled_(false)
{
	if(numOfPlayers_ == 0)	//if numOfPlayers hasn't been used before
		numOfPlayers_ = 1;
	else	//if numOfPlayers has been used before
		numOfPlayers_++;

	id_ = numOfPlayers_;
	AssignPlayerPiece();	
}

void Player::InitializePlayer(int boundsLimit)
{
	(*this).boundsLimit_ = boundsLimit;

	//Clear the screen
	system("cls");
	//Ask player for name
	//Had to put it here because I need the ID for the prompt...
	std::string n;
	std::cout<<"Player "<<id_<<": What is your name?"<<std::endl;
	std::cin>>n;

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
		PieceGen();
	else
		if(otherPlayerPiece_ == 1)
			playerPiece_ = 2;
		else
			playerPiece_ = 1;

		resetPlayerFunctionCalled_ = false;
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
	if(!resetPlayerFunctionCalled_) {
		otherPlayerPiece_ = 0;
		resetPlayerFunctionCalled_ = true;
	}
	else
		throw Exception(err.Double_Function_Call);
}

void Player::PieceGen()
{
	int temp = (rand()%40)+1;

	if(temp >= 1 && temp <= 20)
		playerPiece_ = otherPlayerPiece_ = 1;

	if(temp >= 21 && temp <= 40)
		playerPiece_ = otherPlayerPiece_ = 2;
}

void Player::DisplayName()
{
	std::cout<<"Player "<<id_<<": "<<name_;
}

void Player::DisplayScore()
{
	std::cout<<"Player "<<id_<<"'s score is: "<<score_;
}

void Player::UpdateScore()
{
	score_++;
}

bool Player::MakeMove()
{
	DisplayName();
	std::string choice;
	std::cout<<std::endl;
	std::cout<<"Enter in your choice below...\n";
	std::cout<<"Ex. 1,1 or q to quit the game"<<std::endl;
	std::cin>>choice;

	bool checkMove = false;
	bool loop = false;
	while(!loop) {
		//Used unsigned int here because move.size is also an unsigned integer.
		//Keeps warning messages about type mismatches from showing up in the compiler window...
		for(unsigned int i = 0; i < choice.size(); i++)
			if(choice[i] == 'q' || choice[i] == 'Q') {
				move_ = -1;
				loop = true; //Just in case
				return false;
			}

		try {
			checkMove = CheckMoveFormat(choice);
			if(checkMove) {
				move_ = ReformatMove(choice);
				loop = true;
			}
		}
		catch(Exception &e) {
			SoundEngine::GetInstance()->PlaySoundFromQueue(badMoveErrorSound);
			std::cout<<e.what()<<"\n";
			std::cout<<"Please re-enter your choice\n";
			std::cin>>choice;
		}
	}

	madeMove_ = true;

	return true;
}

bool Player::CheckMoveFormat(std::string choice)
{
	const std::string toManyCharacters = "Your entry has to many characters, please try again...", toFewCharacters = "Your entry has to few characters, please try again...",
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

int Player::ReformatMove(std::string choice)
{
	const int hundred = 100, ten = 10;
	
	std::stringstream ss;
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
	//Resets madeMove_ value only when its value is true
	if(madeMove_) {
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
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const int Player::GetPiece() const
{
	if(playerInitialized_)
		return playerPiece_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const std::string Player::GetName() const
{
	if(playerInitialized_)
		return name_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const int Player::GetScore() const
{
	if(playerInitialized_)
		return score_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const int Player::GetMove() const
{
	if(playerInitialized_)
		return move_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const bool Player::DidPlayerWin() const
{
	if(playerInitialized_)
		return win_;
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

const int Player::GetPlayerTextColor() const
{
	if(playerInitialized_)
		return (textColor.GetTextColor());
	else {
		SoundEngine::GetInstance()->PlaySoundFromQueue(fatalErrorSound);
		throw Exception(err.Invalid_Variable_Access, varError);
	}
}

void Player::SetPlayerWon()
{
	win_ = true;
}