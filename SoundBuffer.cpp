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

#include "SoundBuffer.h"

SoundBuffer::SoundBuffer() throw()
	: isSoundBufferInitialized_(false)
{}

SoundBuffer::SoundBuffer(const SoundBuffer &sb) throw()
{
	soundData_.reset();
	format_ = sb.format_;
	buffer_ = sb.buffer_;

	if(sb.soundData_) {
		soundData_ = bytePtr(new BYTE[buffer_.AudioBytes]);
		CopyMemory(soundData_.get(), sb.soundData_.get(), buffer_.AudioBytes);
		buffer_.pAudioData = soundData_.get();
	}
}

SoundBuffer::~SoundBuffer()
{
	if(soundData_)
		soundData_.reset();
}

SoundBuffer& SoundBuffer::operator=(const SoundBuffer &sb) throw()
{
	soundData_.reset();
	format_ = sb.format_;
	buffer_ = sb.buffer_;

	if(sb.soundData_) {
		soundData_ = bytePtr(new BYTE[buffer_.AudioBytes]);
		CopyMemory(soundData_.get(), sb.soundData_.get(), buffer_.AudioBytes);
		buffer_.pAudioData = soundData_.get();
	}

	return *this;
}

void SoundBuffer::InitializeSoundBuffer()
{
	soundData_.reset();
	SecureZeroMemory(&format_, sizeof(format_));
	SecureZeroMemory(&buffer_, sizeof(buffer_));
	isSoundBufferInitialized_ = true;
}

bool SoundBuffer::LoadFile(const char *soundFile)
{
	if(soundFile == NULL)
		throw Exception(err.SoundBuffer_Fatal_Error, "Cannot find sound file, name is NULL.");

	std::ifstream inputSoundFile(soundFile, std::ios::binary | std::ios::in);
	if(inputSoundFile.bad())
		throw Exception(err.SoundBuffer_Fatal_Error, "Sound file is bad or corrupted.");
		
	DWORD dwChunkId = 0, dwFileSize = 0, dwChunkSize = 0, dwExtra = 0;

	//look for 'RIFF' chunk identifier
	inputSoundFile.seekg(0, std::ios::beg);
	inputSoundFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
	if(dwChunkId != 'FFIR') {
		inputSoundFile.close();
		throw Exception(err.SoundBuffer_Fatal_Error, "Couldn't find the RIFF chunk identifier.\nFile may be corrupted.");
	}
	//----------DEBUG ONLY START------------
	cout<<"\nfile did finally load\n";
	_getche();
	//----------DEBUG ONLY END------------
	inputSoundFile.seekg(4, std::ios::beg); //get file size
	inputSoundFile.read(reinterpret_cast<char*>(&dwFileSize), sizeof(dwFileSize));
	if(dwFileSize <= 16) {
		inputSoundFile.close();
		throw Exception(err.SoundBuffer_Fatal_Error, "Could not determine file size.\nFile may be corrupted.");
	}
	//----------DEBUG ONLY START------------
	cout<<"got file size...\n";
	_getche();
	//----------DEBUG ONLY END------------
	inputSoundFile.seekg(8, std::ios::beg); //get file format
	inputSoundFile.read(reinterpret_cast<char*>(&dwExtra), sizeof(dwExtra));
	if(dwExtra != 'EVAW') {
		inputSoundFile.close();
		throw Exception(err.SoundBuffer_Fatal_Error, "Could not determine file format.\nFile may be corrupted.");
	}
	//----------DEBUG ONLY START------------
	cout<<"got the file format succesfully...\n";
	_getche();
	//----------DEBUG ONLY END------------
	//look for 'fmt ' chunk id
	bool isFormatOK = false;
	for(unsigned int i = 12; i < dwFileSize; ) {
		inputSoundFile.seekg(i, std::ios::beg);
		inputSoundFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
		inputSoundFile.seekg(i + 4, std::ios::beg);
		inputSoundFile.read(reinterpret_cast<char*>(&dwChunkSize), sizeof(dwChunkSize));
		if(dwChunkId == ' tmf') {
			inputSoundFile.seekg(i + 8, std::ios::beg);
			inputSoundFile.read(reinterpret_cast<char*>(&format_), sizeof(format_));
			isFormatOK = true;
			break;
		}
		dwChunkSize += 8; //add offsets of the chunk id, and chunk size data entries
		dwChunkSize += 1;
		dwChunkSize &= 0xfffffffe; //guarantees WORD padding alignment
		i += dwChunkSize;
	}
	
	if(!isFormatOK) {
		inputSoundFile.close();
		throw Exception(err.SoundBuffer_Fatal_Error, "Couldn't find \'fmt\' in chunk id, sound file may be corrupted");
	}
	//----------DEBUG ONLY START------------
	cout<<"Found fmt in chunk id\n";
	_getche();
	//----------DEBUG ONLY END------------

	//look for 'data' chunk id
	bool isDataOK = false;
	for(unsigned int i = 12; i < dwFileSize; ) {
		inputSoundFile.seekg(i, std::ios::beg);
		inputSoundFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
		inputSoundFile.seekg(i + 4, std::ios::beg);
		inputSoundFile.read(reinterpret_cast<char*>(&dwChunkSize), sizeof(dwChunkSize));
		if(dwChunkId == 'atad') {
			soundData_ = bytePtr(new BYTE[dwChunkSize]);
			inputSoundFile.seekg((i + 8), ios::beg);
			inputSoundFile.read(reinterpret_cast<char*>(soundData_.get()), dwChunkSize);
			buffer_.AudioBytes = dwChunkSize;
			buffer_.pAudioData = soundData_.get();
			buffer_.PlayBegin = 0;
			buffer_.PlayLength = 0;
			isDataOK = true;
			break;
		}
		dwChunkSize += 8; //add offsets of the chunk id, and chunk size data entries
		dwChunkSize += 1;
		dwChunkSize &= 0xfffffffe; //guarantees WORD padding alignment
		i += dwChunkSize;
	}
	
	if(!isDataOK) {
		inputSoundFile.close();
		throw Exception(err.SoundBuffer_Fatal_Error, "Couldn't find \'data\' in chunk id, sound file may be corrupted");
	}

	//----------DEBUG ONLY START------------
	cout<<"Found data in chunk id\n";
	_getche();
	//----------DEBUG ONLY END------------

	inputSoundFile.close();
	return true;
}

const xa2BufferPtr SoundBuffer::GetXA2Buffer() const
{
	xa2BufferPtr temp(new XAUDIO2_BUFFER());
	if(isSoundBufferInitialized_) {
		*temp = buffer_;
		return temp;
	}
	else
		throw Exception(err.Invalid_Variable_Access);
}

const wFormatPtr SoundBuffer::GetWFormat() const
{
	wFormatPtr temp(new WAVEFORMATEX());
	if(isSoundBufferInitialized_) {
		*temp = format_;
		return temp;
	}
	else
		throw Exception(err.Invalid_Variable_Access);
}