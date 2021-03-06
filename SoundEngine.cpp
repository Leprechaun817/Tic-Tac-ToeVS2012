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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Aaron's Tic-Tac-Toe Clone. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************************
********************************************************************************************/

#include "SoundEngine.h"

const std::string SoundEngine::playerOneWinSound = "playerOneWinSound";
const std::string SoundEngine::playerTwoWinSound = "playerTwoWinSound";
const std::string SoundEngine::gameOverSound = "gameOverSound";
const std::string SoundEngine::pieceClickSound = "pieceClickSound";
const std::string SoundEngine::badMoveErrorSound = "badMoveErrorSound";
const std::string SoundEngine::fatalErrorSound = "fatalErrorSound";
const std::string SoundEngine::clickSound = "clickSound";
const std::string SoundEngine::endOfGameSound = "endOfGameSound";
const std::string SoundEngine::minorErrorSound = "minorErrorSound";
bool SoundEngine::isSoundEnginePtrInitialized_ = false;
SoundEngine::sePtr SoundEngine::engInstance_ = nullptr;

SoundEngine::SoundEngine() throw()
: isSoundEngineInitialized_(false)
{
	//This must be called first, the sound needs to have a COM object in order to work
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	soundBufferList.resize(numOfSounds);
	soundSourceList.resize(numOfSounds);

	std::array<const std::string, numOfSounds> soundNameArr = {playerOneWinSound, playerTwoWinSound, gameOverSound, pieceClickSound, badMoveErrorSound, fatalErrorSound, clickSound,
															   endOfGameSound, minorErrorSound};
	std::array<int, numOfSounds> soundNumArr = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	for(int i = 0; i < numOfSounds; i++)
		soundNameList.insert(std::pair<const std::string, int>(soundNameArr[i], soundNumArr[i]));

	//Initialize sound pointers
	soundEng_ = ixAudioPtr(new IXAudio2*());
	soundMaster_ = ixMasterVoicePtr(new IXAudio2MasteringVoice*());
	for(auto &i : soundSourceList)
		i = ixSourceVoicePtr(new IXAudio2SourceVoice*());
}

SoundEngine::~SoundEngine() throw()
{
	(*soundEng_)->Release();
	CoUninitialize();
}

void SoundEngine::InitPtr()
{
	if(!engInstance_)
		engInstance_ = sePtr(new SoundEngine());
	isSoundEnginePtrInitialized_ = true;
}

SoundEngine* SoundEngine::GetInstance()
{
	if(isSoundEnginePtrInitialized_)
		return engInstance_.get();
	else
		throw Exception(6, "Pointer for SoundEngine hasn't been initialized yet.\nInitPtr must be called first");
}

void SoundEngine::InitializeSoundEngine()
{
	//Declare filename constants
	const std::string fileType = ".wav";
	const std::string fileLocation = "Sounds\\";
	std::array<const std::string, numOfSounds> soundFileNames = { (fileLocation + playerOneWinSound + fileType), (fileLocation + playerTwoWinSound + fileType),
																  (fileLocation + gameOverSound + fileType), (fileLocation + pieceClickSound + fileType),
																  (fileLocation + badMoveErrorSound + fileType), (fileLocation + fatalErrorSound + fileType),
																  (fileLocation + clickSound + fileType), (fileLocation + endOfGameSound + fileType),
																  (fileLocation + minorErrorSound + fileType)
																};
	//Initialize sound engine
	if(FAILED(XAudio2Create(soundEng_.get()))) {
		CoUninitialize();
		throw Exception(err.SoundEngine_Fatal_Error, "Unable to create audio engine.");
	}

	//Initialize the mastering voice
	if(FAILED((*soundEng_)->CreateMasteringVoice(soundMaster_.get()))) {
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
		if(FAILED((*soundEng_)->CreateSourceVoice(i.get(), &(*soundBufferList[x++].GetWFormat())))) {
			(*soundEng_)->Release();
			CoUninitialize();
			throw Exception(err.SoundEngine_Fatal_Error, "Unable to create source voice.");
		}
		(*i)->Start();
	}

	isSoundEngineInitialized_ = true;
}

void SoundEngine::PlaySoundFromQueue(std::string sound) const
{
	int soundNum = GetConstantFromList(sound);
	if(isSoundEngineInitialized_)
		(*soundSourceList[soundNum])->SubmitSourceBuffer(&(*soundBufferList[soundNum].GetXA2Buffer()));
	else
		throw Exception(err.SoundEngine_Fatal_Error, "Sound engine uninitialized, can't play sounds.");
}

int SoundEngine::GetConstantFromList(std::string soundRequest) const
{
	int returnValue = -5;
	for(const auto &i : soundNameList)
		if((i.first) == soundRequest) {
			returnValue = (i.second);
			break;
		}

	if(returnValue == -5)
		throw Exception(err.Unknown_Constant_Error);
	
	return returnValue;
}