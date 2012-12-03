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
#pragma warning(disable : 4244)
#include <Windows.h>
#include <xaudio2.h>
#include <fstream>
#include <memory>
#include <string>
#include "ExceptionClass.h"
#include "ErrorTypes.h"

using namespace std;

typedef unique_ptr<BYTE> bytePtr;
typedef unique_ptr<XAUDIO2_BUFFER> xa2BufferPtr;
typedef unique_ptr<WAVEFORMATEX> wFormatPtr;

class SoundBuffer
{
public:
	SoundBuffer() throw();
	SoundBuffer(const SoundBuffer &sb) throw();
	~SoundBuffer();
	const xa2BufferPtr GetXA2Buffer() const;
	const wFormatPtr GetWFormat() const;
	bool LoadFile(const string soundFile);
	void InitializeSoundBuffer();

//Container Variables
private:
	ErrorTypes err;

//Regular Variables
private:
	WAVEFORMATEX format_;
	XAUDIO2_BUFFER buffer_;
	bytePtr soundData_;
	bool isSoundBufferInitialized_;
};