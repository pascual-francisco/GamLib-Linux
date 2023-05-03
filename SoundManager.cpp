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
    if(Mix_PlayMusic( bgmMap.at(name), -1) != 0)
    {
       cout << "Failed to play music: " << Mix_GetError() << endl;
    }
}

void SoundManager::playSFX(GLuint name)
{
    Mix_PlayChannel( -1, sfxMap.at(name), 0);


}

void SoundManager::print() const
{
	cout << "**************************************************" << endl;
	cout << "Sound Manager Info:" << endl;
	cout << "Frequency = " << frequency << endl;
	cout << "Format = " << format << endl;
	cout << "Channels = " << channels<< endl;
	cout << "Chunk Size = " << chunkSize << endl;
	cout << "BGM Map Info:" << endl;
	cout << "BGM count = " << bgmMap.size() << endl;
	cout << "SFX Map Info:" << endl;
	cout << "SFX count = " << sfxMap.size() << endl;
	cout << "**************************************************" << endl;
}



/*
vector<string> SoundMixer::soundList;

SoundMixer::SoundMixer()
{
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
	chunk = NULL;
}

SoundMixer::~SoundMixer()
{
	Mix_FreeChunk(chunk);
	Mix_CloseAudio();
	soundList.clear();
}

void SoundMixer::update()
{
	for(unsigned int i = 0; i<soundList.size(); i++)
	{
		chunk = Mix_LoadWAV(soundList[i].c_str());
		if(chunk!=NULL)
		{
			Mix_PlayChannel(0, chunk, 0 );
		}
	}

	soundList.clear();
}
*/

