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

#include "SoundEngine.h"

SoundEngine::SoundEngine() throw()
	: isSoundEngineInitialized(false)
{
	//This must be called first, the sound needs to have a COM obejct in order to work
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	soundBufferList.resize(4);
	soundSourceList.resize(4);
}

SoundEngine::~SoundEngine()
{
	(*soundEng)->Release();
	CoUninitialize();
}

void SoundEngine::InitializeSoundEngine()
{
	//Initialize sound engine
	if(FAILED(XAudio2Create(&(*soundEng)))) {
		CoUninitialize();
		throw Exception(err.SoundEngine_Fatal_Error, "Unable to create audio engine.");
	}

	//Initialize the mastering voice
	if(FAILED((*soundEng)->CreateMasteringVoice(&(*soundMaster)))) {
		(*soundEng)->Release();
		CoUninitialize();
		throw Exception(err.SoundEngine_Fatal_Error, "Unable to create mastering voice.");
	}

	for(auto &i : soundBufferList) {
		i.InitializeSoundBuffer();
		try {
			i.LoadFile("file1");
		}
		catch(Exception &e) {
			(*soundEng)->Release();
			CoUninitialize();
			throw;
		}
	}

	int x = 0;
	for(auto &i : soundSourceList) {
		if(FAILED((*soundEng)->CreateSourceVoice(&(*i), &(*soundBufferList[0].GetWFormat())))) {
			(*soundEng)->Release();
			CoUninitialize();
			throw Exception(err.SoundEngine_Fatal_Error, "Unable to create source voice.");
		}
	}

	isSoundEngineInitialized = true;
}