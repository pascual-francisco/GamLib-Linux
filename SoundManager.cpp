#pragma once
#include "stdafx.h"

SoundManager::SoundManager(int frequency, uint format, int channels, int chunkSize)
{
	this->frequency = frequency;
	this->format = format;
	this->channels = channels;
	this->chunkSize = chunkSize;

	if (Mix_OpenAudio(frequency, format, channels, chunkSize) < 0)
	{
		cout << "SDL_Mixer Error: Initialization Error" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "SDL_Mixer initialized no error" << endl;
	}
}

SoundManager::~SoundManager()
{
	sfxMap.clear();
	bgmMap.clear();
}

void SoundManager::initSFX(GLuint name, string path)
{
	Mix_Chunk *chunk = nullptr;

	chunk = Mix_LoadWAV(path.c_str());
	
	if (chunk != nullptr)
		sfxMap.insert(SFXMap::value_type(name, chunk));

	Mix_FreeChunk(chunk);
}

void SoundManager::initBGM(GLuint name, string path)
{
	Mix_Music *music = nullptr;
	music = Mix_LoadMUS(path.c_str());

	if (music != nullptr)
		bgmMap.insert(BGMMap::value_type(name, music));

	Mix_FreeMusic(music);
}

void SoundManager::playBGM(GLuint name)
{
}

void SoundManager::playSFX(GLuint name)
{
}

void SoundManager::print() const
{
	cout << "**************************************************" << endl;
	cout << "Sound Manager Info:" << endl;
	cout << "Frequecy = " << frequency << endl;
	cout << "Format = " << format << endl;
	cout << "Channels = " << channels<< endl;
	cout << "Chunk Size = " << chunkSize << endl;
	cout << "BGM Map Info:" << endl;
	cout << "BGM count = " << bgmMap.size() << endl;	
	cout << "SFX Map Info:" << endl;
	cout << "SFX count = " << sfxMap.size() << endl;	
	cout << "**************************************************" << endl;
}

