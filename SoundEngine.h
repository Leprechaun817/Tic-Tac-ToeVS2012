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

#pragma once
#pragma warning( disable : 4101 )
#include <Windows.h>
#include <xaudio2.h>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include "SoundBuffer.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef unique_ptr<IXAudio2*> ixAudioPtr;
typedef unique_ptr<IXAudio2SourceVoice*> ixSourceVoicePtr;
typedef unique_ptr<IXAudio2MasteringVoice*> ixMasterVoicePtr;
typedef vector<SoundBuffer> wBufferVectors;
typedef vector<ixSourceVoicePtr> svVector;

typedef map<const string, int> ConstList;

class SoundEngine
{
public:
	static void InitPtr();
	static SoundEngine* GetInstance();
	~SoundEngine() throw();
	void InitializeSoundEngine();
	void PlaySoundFromQueue(string sound) const;

//Copy constructor and assignement operator made private and not given definitions
//so that only one copy of a SoundEngine object can exist at one time
private:
	SoundEngine() throw();
	SoundEngine(const SoundEngine&);
	SoundEngine& operator=(const SoundEngine&);

//Constant Variables
private:
	static const string playerOneWinSound, playerTwoWinSound, gameOverSound, pieceClickSound, badMoveErrorSound, fatalErrorSound;
	static const int numOfSounds = 6;

//Container Variables
private:
	ConstList soundNameList;
	wBufferVectors soundBufferList;
	svVector soundSourceList;
	ErrorTypes err;

//Regular Variables
private:
	ixAudioPtr soundEng_;
	ixMasterVoicePtr soundMaster_;
	bool isSoundEngineInitialized_;

//Static variables/objects
private:
	static SoundEngine *engInstance_;
	static bool isSoundEnginePtrInitialized_;
//Private Functions
private:
	void LoadSound(const string filename);
	int GetConstantFromList(string soundRequest) const;
};