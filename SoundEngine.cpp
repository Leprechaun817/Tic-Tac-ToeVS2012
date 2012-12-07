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

const string SoundEngine::playerOneWinSound = "playeronewinsound";
const string SoundEngine::playerTwoWinSound = "playerywowinsound";
const string SoundEngine::gameOverSound = "gameoversound";
const string SoundEngine::pieceClickSound = "piececlicksound";
const string SoundEngine::badMoveErrorSound = "badmoveerrorsound";
const string SoundEngine::fatalErrorSound = "fatalerrorsound";

SoundEngine::SoundEngine() throw()
	: isSoundEngineInitialized_(false)
{
	//This must be called first, the sound needs to have a COM object in order to work
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	soundBufferList.resize(numOfSounds);
	soundSourceList.resize(numOfSounds);

	array<const string, numOfSounds> soundNameArr = {playerOneWinSound, playerTwoWinSound, gameOverSound, pieceClickSound, badMoveErrorSound, fatalErrorSound};
	array<int, numOfSounds> soundNumArr = {0, 1, 2, 3, 4, 5};

	for(int i = 0; i < numOfSounds; i++)
		soundNameList.insert(pair<const string, int>(soundNameArr[i], soundNumArr[i]));

	//Initialize sound pointers
	soundEng_ = ixAudioPtr(new IXAudio2*());
	soundMaster_ = ixMasterVoicePtr(new IXAudio2MasteringVoice*());
	for(auto &i : soundSourceList)
		i = ixSourceVoicePtr(new IXAudio2SourceVoice*());
}

SoundEngine::~SoundEngine()
{
	(*soundEng_)->Release();
	CoUninitialize();
}

void SoundEngine::InitializeSoundEngine()
{
	//Declare filename constants
	const string fileType = ".wav";
	const string fileLocation = "sounds\\";
	//------TESTING ONLY--------
	array<const string, numOfSounds> soundFileNames = {(fileLocation + playerOneWinSound + fileType), playerTwoWinSound, gameOverSound, pieceClickSound, badMoveErrorSound, fatalErrorSound};
	/*array<const string, numOfSounds> soundFileNames = {(fileLocation + playerOneWinSound + fileType), (fileLocation + playerTwoWinSound + fileType), (fileLocation + gameOverSound + fileType), 
													   (fileLocation + pieceClickSound + fileType), (fileLocation + badMoveErrorSound + fileType), (fileLocation + fatalErrorSound + fileType)};*/
	//----------DEBUG ONLY START------------
	cout<<soundFileNames[0];
	_getche();
	//----------DEBUG ONLY END------------
	//Initialize sound engine
	if(FAILED(XAudio2Create(&(*soundEng_)))) {
		CoUninitialize();
		throw Exception(err.SoundEngine_Fatal_Error, "Unable to create audio engine.");
	}

	//Initialize the mastering voice
	if(FAILED((*soundEng_)->CreateMasteringVoice(&(*soundMaster_)))) {
		(*soundEng_)->Release();
		CoUninitialize();
		throw Exception(err.SoundEngine_Fatal_Error, "Unable to create mastering voice.");
	}

	//TODO:
	//Change the load function used here so that it's not loading sounds straight into memory, but instead streams them straight from the hard drive
	//-------------------------------------------------------------------------------------
	//Initializing all of the source voices, basically there is one source voice per sound
	//At least that's how I have it set up right now...
	int x = 0;
	for(auto &i : soundBufferList) {
		i.InitializeSoundBuffer();
		try {
			i.LoadFile(soundFileNames[x++].c_str());
		}
		catch(Exception &e) {
			(*soundEng_)->Release();
			CoUninitialize();
			throw;
		}
	}

	x = 0;
	for(auto &i : soundSourceList) {
		if(FAILED((*soundEng_)->CreateSourceVoice(&(*i), &(*soundBufferList[0].GetWFormat())))) {
			(*soundEng_)->Release();
			CoUninitialize();
			throw Exception(err.SoundEngine_Fatal_Error, "Unable to create source voice.");
		}
	}

	isSoundEngineInitialized_ = true;
}

void SoundEngine::PlaySoundFromQueue(string sound)
{
	if(isSoundEngineInitialized_) {
		int soundNum = GetConstantFromList(sound);
		(*soundSourceList[soundNum])->Start();

		(*soundSourceList[soundNum])->SubmitSourceBuffer(&(*soundBufferList[soundNum].GetXA2Buffer()));

		(*soundSourceList[soundNum])->Stop();
	}
	else
		throw Exception(err.SoundEngine_Fatal_Error, "Sound engine uninitialized, can't play sounds.");
}

int SoundEngine::GetConstantFromList(string soundRequest)
{
	int returnValue = -5;
	for(auto &i : soundNameList)
		if((i.first) == soundRequest) {
			returnValue = (i.second);
			break;
		}

	if(returnValue == -5)
		throw Exception(err.Unknown_Constant_Error);
	return returnValue;
}