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

	 	SoundManager(int frequency = MIX_DEFAULT_FREQUENCY, uint format = MIX_DEFAULT_FORMAT, int channels = MIX_DEFAULT_CHANNELS, int chunkSize = 2048);
	 	~SoundManager();

	  void	initSFX(GLuint name, string path);
	  void	initBGM(GLuint name, string path);

	  void	playBGM(GLuint name);
	  void	playSFX(GLuint name);
	  void	print() const;
};
#endif // !SOUNDMANAGER_H
