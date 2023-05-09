#include "stdafx.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	private:
    void init(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type);
	void reserveImage3D();
	void loadImage3D();
	void reserveImage2D();
	void loadImage2D();


	public:
	string	textureName;
	GLuint	textureID;
	string	texturePath;
	GLsizei textureWidth;
	GLsizei textureHeight;
	GLsizei textureDepth;
	GLuint	textureUnit;
	GLenum	textureTarget;
	GLenum	textureDataFormat;
	GLenum	textureInternalDataFormat;
	GLenum	textureDataType;

    Texture(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type);
    Texture(Texture&);
    ~Texture();

    const Texture &operator=(const Texture &);
    bool operator==(const Texture &) const;
    bool operator<(const Texture &) const;
    bool operator>(const Texture &) const;

    void attach(GLuint unit);
    void detach() const;
    void print() const;
};
#endif
