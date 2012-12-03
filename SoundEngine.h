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
#include <Windows.h>
#include <xaudio2.h>
#include <memory>
#include <vector>
#include "SoundBuffer.h"
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef unique_ptr<IXAudio2*> ixAudioPtr;
typedef unique_ptr<IXAudio2SourceVoice*> ixSourceVoicePtr;
typedef unique_ptr<IXAudio2MasteringVoice*> ixMasterVoicePtr;
typedef vector<SoundBuffer> wBufferVectors;
typedef vector<ixSourceVoicePtr> svVector;

class SoundEngine
{
public:
	SoundEngine() throw();
	~SoundEngine();
	void InitializeSoundEngine();
	void PlaySoundQueue(int sound);

//Container Variables
private:
	wBufferVectors soundBufferList;
	svVector soundSourceList;
	ErrorTypes err;

//Regular Variables
private:
	ixAudioPtr soundEng;
	ixSourceVoicePtr soundSource;
	ixMasterVoicePtr soundMaster;
	bool isSoundEngineInitialized;

//Private Functions
private:
	void LoadSound(const string filename);
};