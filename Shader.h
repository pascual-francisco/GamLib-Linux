#pragma once
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
		
	__declspec(dllexport) Shader();
	__declspec(dllexport) Shader(string file, const char* vname, const char* fname);
	__declspec(dllexport) ~Shader();
	__declspec(dllexport) void attach();
	__declspec(dllexport) void detach();

	private:
	__declspec(dllexport) void initShader(const char* vname, const char* fname);
	__declspec(dllexport) void loadFile(const char* fn, string& str);
	__declspec(dllexport) GLuint loadShader(string& source, GLuint mode);
};
#endif