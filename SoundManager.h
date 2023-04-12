#pragma once
#include "stdafx.h"

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundManager
{
	public:
	int		frequency;
	uint	format;
	int		channels;
	int		chunkSize;	
	
	typedef	map< GLuint, Mix_Music *, less< GLuint > > BGMMap;
	BGMMap	bgmMap;
	typedef	map< GLuint, Mix_Chunk*, less< GLuint > > SFXMap;
	SFXMap	sfxMap;

	__declspec(dllexport)	SoundManager(int frequency = MIX_DEFAULT_FREQUENCY, uint format = MIX_DEFAULT_FORMAT, int channels = MIX_DEFAULT_CHANNELS, int chunkSize = 2048);
	__declspec(dllexport)	~SoundManager();

	__declspec(dllexport) void	initSFX(GLuint name, string path);	
	__declspec(dllexport) void	initBGM(GLuint name, string path);

	__declspec(dllexport) void	playBGM(GLuint name);
	__declspec(dllexport) void	playSFX(GLuint name);
	__declspec(dllexport) void	print() const;
};
#endif // !SOUNDMANAGER_H
