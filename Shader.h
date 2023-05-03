#include "stdafx.h"

#ifndef SHADER_H
#define SHADER_H

class Shader

{
public:
	GLuint	programID;;
	GLuint	vertexID;
	GLuint	fragmentID;
	string	filePath;

	  Shader();
	  Shader(string file, const char* vname, const char* fname);
	  ~Shader();
	  void attach();
	  void detach();

	private:
	  void initShader(const char* vname, const char* fname);
	  void loadFile(const char* fn, string& str);
	  GLuint loadShader(string& source, GLuint mode);
};
#endif
