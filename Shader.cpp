#pragma once
#include "stdafx.h"

Shader::Shader()
{
	filePath = "Assets/Shaders/";
	programID = 0;
	vertexID = 0;
	fragmentID = 0;	
}

Shader::Shader(string file, const char *vname, const char *fname)
{
	filePath = file;
	programID = 0;
	vertexID = 0;
	fragmentID = 0;
	initShader(vname, fname);
}

Shader::~Shader()
{
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
}

void Shader::initShader(const char* vname, const char* fname)
{
	char buffer[1000] = { 0 };
	char log[300] = { 0 };
	string source;
	ofstream out;

	time_t now = time(0);
	ctime_s(buffer, 1000, &now);

	if (!out.is_open())
	{		
		out.open(filePath + "shaderlog.txt", ios::trunc);
		out << "Shader Logs " << buffer;	
	}

	loadFile(vname, source);
	vertexID = loadShader(source, GL_VERTEX_SHADER);
	glGetShaderInfoLog(vertexID, 1000, NULL, buffer);

	out << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;

	out << "Shaders Status:" << endl;
	cout << "Shaders Status:" << endl;

	out << "Vertex Shader Info Log: " << endl;
	cout << "Vertex Shader Info Log: " << endl;
	
	out << "Vertex Shader name = " << vname << endl;		
	cout << "Vertex Shader name = " << vname << endl;
	
	out << "Vertex Shader id = " << vertexID << endl;
	cout << "Vertex Shader id = " << vertexID << endl;
	
	if (strcmp(buffer, "") == 0)
	{
		out << "Vertex Shader status OK!" << endl;
		cout << "Vertex Shader status OK!" << endl;
	}
	else
	{
		out << "Vertex Shader ERROR!" << endl<<buffer<<endl;
		cout << "Vertex Shader ERROR!" << endl << buffer << endl;
	}

	source = "";
	loadFile(fname, source);
	fragmentID = loadShader(source, GL_FRAGMENT_SHADER);
	glGetShaderInfoLog(fragmentID, 1000, NULL, buffer);

	out << "Fragment Shader Info Log: " << endl;
	cout << "Fragment Shader Info Log: " << endl;

	out << "Fragment Shader name = " << fname << endl;
	cout << "Fragment Shader name = " << fname << endl;
	
	out << "Fragment Shader id = " << fragmentID << endl;
	cout << "Fragment Shader id = " << fragmentID << endl;	

	if (strcmp(buffer, "") == 0)
	{
		out << "Fragment Shader status OK!" << endl;
		cout << "Fragment Shader status OK!" << endl;
	}
	else
	{
		out << "Fragment Shader ERROR!" << endl << buffer << endl;
		cout << "Fragment Shader ERROR!" << endl << buffer << endl;
	}
		
	programID = glCreateProgram();	
	glGetProgramInfoLog(programID, 1000, NULL, buffer);	

	out << "Program Info Log: " << endl;
	cout << "Program Info Log: " << endl;
	
	out << "Program id = " << programID << endl;
	cout << "Program id = " << programID << endl;

	if (strcmp(buffer, "") == 0)
	{
		out << "Program Shader status OK!" << endl;
		cout << "Program Shader status OK!" << endl;
	}
	else
	{
		out << "Program Shader ERROR!" << endl << buffer << endl;
		cout << "Program Shader ERROR!" << endl << buffer << endl;
	}

	out << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;

	out.close();
}

void Shader::loadFile(const char* fn, string& str)
{
	ifstream in(fn);

	if (!in.is_open())
	{		
		cout << "The file " << fn << " cannot be opened"<< endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	char tmp[300];
	while (!in.eof())
	{	
		in.getline(tmp, 300);
		str += tmp;
		str += '\n';
	}
}

GLuint Shader::loadShader(string& source, GLuint mode)
{	
	//char buffer[1000] = { 0 };
	const char* csource = source.c_str();	
	GLuint id = 0;
	
	id = glCreateShader(mode);
	glShaderSource(id, 1, &csource, NULL);
	glCompileShader(id);
	//glGetShaderInfoLog(id, 1000, NULL, buffer);	
	return id;
}

void Shader::attach()
{
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glUseProgram(programID);
}

void Shader::detach()
{
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);
}