#pragma once
#include "stdafx.h"

Texture::Texture(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type)
{
	init(name, path, width, height, depth, target, unit, internalFormat, format, type);
}

Texture::Texture(Texture &t)
{
	if (&t != this)
	{
		textureName = t.textureName;
		texturePath = t.texturePath;
		textureID = t.textureID;
		textureWidth = t.textureWidth;
		textureHeight = t.textureHeight;
		textureDepth = t.textureDepth;
		textureUnit = t.textureUnit;
		textureTarget = t.textureTarget;
		textureDataFormat = t.textureDataFormat;
		textureInternalDataFormat = t.textureInternalDataFormat;
		textureDataType = t.textureDataType;
	}
}

Texture::~Texture()
{
}

const Texture &Texture::operator=(const Texture &t)
{
	if (&t != this)
	{
		textureName = t.textureName;
		texturePath = t.texturePath;
		textureID = t.textureID;
		textureWidth = t.textureWidth;
		textureHeight = t.textureHeight;
		textureDepth = t.textureDepth;
		textureUnit = t.textureUnit;
		textureTarget = t.textureTarget;
		textureDataFormat = t.textureDataFormat;
		textureInternalDataFormat = t.textureInternalDataFormat;
		textureDataType = t.textureDataType;
	}
	return *this;
}

bool Texture::operator==(const Texture &t) const
{
	if (
		textureName == t.textureName &&
		texturePath == t.texturePath &&
		textureID == t.textureID &&
		textureWidth == t.textureWidth &&
		textureHeight == t.textureHeight &&
		textureDepth == t.textureDepth &&
		textureUnit == t.textureUnit &&
		textureTarget == t.textureTarget &&
		textureDataFormat == t.textureDataFormat &&
		textureInternalDataFormat == t.textureInternalDataFormat &&
		textureDataType == t.textureDataType
		)
	{
		return true;
	}

	else
	{
		return false;
	}

}

bool Texture::operator<(const Texture &t) const
{
	if (textureWidth < t.textureWidth && textureHeight < t.textureHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Texture::operator>(const Texture &t) const
{
	if (textureWidth > t.textureWidth && textureHeight > t.textureHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Texture::init(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type)
{
	textureName = name;
	texturePath = path;
	textureWidth = width;
	textureHeight = height;
	textureDepth = depth;
	textureTarget = target;
	textureUnit = unit;
	textureInternalDataFormat = internalFormat;
	textureDataFormat = format;
	textureDataType = type;

	glActiveTexture(textureUnit);
	glGenTextures(1, &textureID);
	glBindTexture(textureTarget, textureID);

	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (textureTarget)
	{
		case GL_TEXTURE_2D_ARRAY:
		{
			//Reserve memory
			if (path == "reserve")
			{
				reserveImage3D();
			}
			else
			{
				loadImage3D();
			}
		}
		break;

		case GL_TEXTURE_2D:
		{
			//Reserve memory
			if (path == "reserve")
			{
				reserveImage2D();
			}
			else
			{
				loadImage2D();
			}
		}
		break;

		default:
		break;
	}
	glBindTexture(textureTarget, 0);
}

void Texture::reserveImage3D()
{
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, textureInternalDataFormat, textureWidth, textureHeight, textureDepth, 0, textureDataFormat, textureDataType, nullptr);
}

void Texture::loadImage3D()
{
	char index[4] = { 0 };
	string file;
	SDL_Surface *ptrImage = nullptr;

	if (textureDepth < 10)
	{
		file = texturePath + "1.png";
		ptrImage = IMG_Load(file.c_str());

		if (ptrImage != NULL)
		{
			textureWidth = ptrImage->w;
			textureHeight = ptrImage->h;

			//Reserve memory for textures
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, textureInternalDataFormat, textureWidth, textureHeight, textureDepth, 0, textureDataFormat, textureDataType, nullptr);

			//Load images
			for (GLint i = 1; i < textureDepth + 1; i++)
			{
				file = texturePath + to_string(i) + ".png";
				ptrImage = IMG_Load(file.c_str());

				if (ptrImage != NULL)
				{
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i - 1, textureWidth, textureHeight, 1, textureDataFormat, textureDataType, ptrImage->pixels);
				}
			}
		}
	}

	if (textureDepth >= 10)
	{
		file = texturePath + "01.png";
		ptrImage = IMG_Load(file.c_str());

		if (ptrImage != NULL)
		{
			textureWidth = ptrImage->w;
			textureHeight = ptrImage->h;

			//Reserve memory for textures
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, textureInternalDataFormat, textureWidth, textureHeight, textureDepth, 0, textureDataFormat, textureDataType, nullptr);

			for (GLint i = 1; i < textureDepth + 1; i++)
			{
				if (i < 10)
				{
					file = texturePath + "0" + to_string(i) + ".png";
				}
				else
				{
					file = texturePath + to_string(i) + ".png";
				}

				ptrImage = IMG_Load(file.c_str());

				if (ptrImage != NULL)
				{
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i - 1, textureWidth, textureHeight, 1, textureDataFormat, textureDataType, ptrImage->pixels);
				}
			}
		}
	}
	SDL_FreeSurface(ptrImage);
}

void Texture::reserveImage2D()
{
	glTexImage2D(GL_TEXTURE_2D, 0, textureInternalDataFormat, textureWidth, textureHeight, 0, textureDataFormat, textureDataType, nullptr);
}

void Texture::loadImage2D()
{
	char index[4] = { 0 };
	string file;
	SDL_Surface *ptrImage = nullptr;
	void *data = nullptr;

	file = texturePath + ".png";
	ptrImage = IMG_Load(file.c_str());

	if (ptrImage != nullptr)
	{
		textureWidth = ptrImage->w;
		textureHeight = ptrImage->h;

		glTexImage2D(GL_TEXTURE_2D, 0, textureInternalDataFormat, textureWidth, textureHeight, 0, textureDataFormat, textureDataType, ptrImage->pixels);
	}
	free(data);
	SDL_FreeSurface(ptrImage);
}

void Texture::attach(GLuint unit)
{
	textureUnit = unit;
	glActiveTexture(textureUnit);
	glBindTexture(textureTarget, textureID);
}

void Texture::detach() const
{
	glActiveTexture(textureUnit);
	glBindTexture(textureTarget, 0);
}

void Texture::print() const
{
	cout << "Texture Object Info: " << endl;
	cout << "Texture ID = " << textureID << endl;
	cout << "Texture Unit = " << textureUnit << endl;
	cout << "Texture Size = ["<<textureWidth<<", "<< textureHeight<<","<<textureDepth<<"]"<< endl;
	cout << "Texture Data Format = " << textureDataFormat << endl;
	cout << "Texture Data Type = " << textureDataType << endl;
	cout << "Texture Name = " << textureName << endl;
	cout << "Texture Path = " << texturePath << endl;
}
