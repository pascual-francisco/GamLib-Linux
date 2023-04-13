#pragma once
#include "Stdafx.h"

#ifndef CAMERA_H
#define	CAMERA_H

class Camera
{
    public:
    bool    active;
	GLuint  programID;
	GLuint  projectionType;
    GLfloat left;
    GLfloat right;
    GLfloat top;
    GLfloat bottom;
    GLfloat zNear;
    GLfloat zFar;
    GLfloat eyeX;
    GLfloat eyeY;
    GLfloat eyeZ;
    GLfloat centerX;
    GLfloat centerY;
    GLfloat centerZ;
    GLfloat upX;
    GLfloat upY;
    GLfloat upZ;
    mat4    projection;
	mat4	view;

    __declspec(dllexport) Camera(bool active = true,  GLuint programID = 0,  GLuint type = 0, GLfloat left = 0.0f, GLfloat right = 256.0f, GLfloat bottom = 0.0f, GLfloat top = 240.0f, GLfloat zNear = 1000.0f , GLfloat zFar = -1000.0f,
           GLfloat eyeX = 0.0f, GLfloat eyeY = 0.0f, GLfloat eyeZ = 0.0f, GLfloat centerX = 0.0f , GLfloat centerY = 0.0f , GLfloat centerZ = -1.0f, GLfloat upX = 0.0f, GLfloat upY = 1.0f, GLfloat upZ = 1.0f);
    __declspec(dllexport) ~Camera();

    __declspec(dllexport) void initCamera(bool active, GLuint programID,  GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);

    __declspec(dllexport) void initProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
    __declspec(dllexport) void initView(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);
    __declspec(dllexport) void initOrigin(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ);
    __declspec(dllexport) void print() const;
    private:

};
#endif

