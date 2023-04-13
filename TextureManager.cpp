#pragma once
#include "stdafx.h"



TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::initTexture(GLuint name, string path, GLuint quantity, GLuint target)
{
	GLuint textureID = 0;
	string file;
	SDL_Surface *ptrImage = NULL;

	glGenTextures(1, &textureID);
	glBindTexture(target, textureID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (target == GL_TEXTURE_2D_ARRAY)
	{
		if (quantity == 1)
		{
			file = path + ".png";

			ptrImage = IMG_Load(file.c_str());

			if (ptrImage != NULL)
			{
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, ptrImage->w, ptrImage->h, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, ptrImage->w, ptrImage->h, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage->pixels);
			}
		}

		if (quantity > 1 && quantity < 10 )
		{
			//Attack_BattonBone_1.png//
			//Attack_BattonBone_
			file = path + "1.png";

			ptrImage = IMG_Load(file.c_str());

			if (ptrImage != NULL)
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, ptrImage->w, ptrImage->h, quantity, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


			for (GLuint i = 1; i < quantity + 1; i++)
			{
				file = path + to_string(i) + ".png";

				ptrImage = IMG_Load(file.c_str());

				if (ptrImage != NULL)
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i - 1, ptrImage->w, ptrImage->h, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage->pixels);
			}
		}

		if (quantity >= 10)
		{
			//Idle_RT-55J_01.png//
			//Idle_RT-55J_
			file = path + "01.png";
			ptrImage = IMG_Load(file.c_str());

			if (ptrImage != NULL)
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, ptrImage->w, ptrImage->h, quantity, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


			for (GLuint i = 1; i < quantity + 1; i++)
			{
				if (i < 10)
				{
					file = path + "0" + to_string(i) + ".png";
				}
				else
				{
					file = path + to_string(i) + ".png";
				}

				ptrImage = IMG_Load(file.c_str());

				if (ptrImage != NULL)
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i - 1, ptrImage->w, ptrImage->h, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage->pixels);

			}
		}
		SDL_FreeSurface(ptrImage);
	}

}

void TextureManager::initTileSet(GLuint name, string path, GLuint tileWidth, GLuint tileHeight, GLuint columns, GLuint rows, GLuint columnOffset, GLuint rowOffset, GLuint target)
{
	GLuint quantity = columns * rows;
	GLuint textureID = 0;
	string file;
	SDL_Surface *ptrImage1 = nullptr;
	SDL_Surface *ptrImage2 = nullptr;
	SDL_Rect source;
	SDL_Rect destination;
	GLuint counter = 0;
	source.x = 0;
	source.y = 0;
	source.w = 0;
	source.h = 0;

	destination.x = 0;
	destination.y = 0;
	destination.w = 0;
	destination.h = 0;

	glGenTextures(1, &textureID);
	glBindTexture(target, textureID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (target == GL_TEXTURE_2D_ARRAY)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, tileWidth, tileHeight, quantity, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		file = path + ".png";
		ptrImage1 = IMG_Load(file.c_str());
		ptrImage2 = SDL_CreateRGBSurface(0, tileWidth, tileHeight, 8, 0, 0, 0, 0);

		if (ptrImage1 != nullptr && ptrImage2 != nullptr)
		{
			for (GLuint i = 0; i < rows; i++)
			{
				for (GLuint j = 0; j < columns; j++)
				{
					source.x = (j * tileWidth) + columnOffset;
					source.y = (i * tileHeight) + rowOffset;
					source.w = tileWidth;
					source.h = tileHeight;

					SDL_BlitSurface(ptrImage1, &source, ptrImage2, 0);
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, counter, tileWidth, tileHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage2->pixels);
					counter++;
				}
			}
		}
		SDL_FreeSurface(ptrImage1);
		SDL_FreeSurface(ptrImage2);
	}
}

void TextureManager:: print() const
{

}


