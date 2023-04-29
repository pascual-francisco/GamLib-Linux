#include "stdafx.h"

Camera::Camera(bool active, GLuint programID,  GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
    this->active = active;
	this->programID = programID;
	this->projectionType = type;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->zNear = znear;
    this->zFar = zfar;
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    this->centerX = centerX;
    this->centerY = centerY;
    this->centerZ = centerZ;
    this->upX = upX;
    this->upY = upY;
    this->upZ = upZ;


    initCamera(active, programID, type, left, right, bottom, top, znear, zfar, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

Camera::~Camera()
{

}

void Camera::initCamera(bool active, GLuint programID,  GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
    this->active = active;
	this->programID = programID;

    initProjection(type, left, right, bottom, top, zNear, zFar);

    initView(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    initOrigin(eyeX, eyeY, eyeZ);

    projection = mat4(1.0f);
	view = mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(programID, "vProjection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "vView"), 1, GL_FALSE, &view[0][0]);
}

void Camera::initProjection(GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar)
{
    this->projectionType = type;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->zNear = znear;
    this->zFar = zfar;
	projection = glm::ortho(left, right, bottom, top, znear, zfar);
}

void Camera::initView(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    this->centerX = centerX;
    this->centerY = centerY;
    this->centerZ = centerZ;
    this->upX = upX;
    this->upY = upY;
    this->upZ = upZ;
    view = glm::lookAt(vec3(eyeX, eyeY, eyeZ), vec3(centerX, centerY, centerZ), vec3(upX, upY, upZ));
}

void Camera::initOrigin(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ)
{
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
	view = glm::translate(view, vec3(eyeX, eyeY, eyeZ));
}


void Camera::print()const
{
    cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Camera Info:" << endl;
	cout << "Program ID = " << programID << endl;
	cout << "Active ="<< active << endl;
    cout << "Projection Type ="<<projectionType << endl;
    cout << "Left = "<< left << endl;
    cout << "Right = "<< right << endl;
    cout << "Top = "<< top << endl;
    cout << "Bottom = "<< bottom << endl;
    cout << "ZNear = "<< zNear << endl;
    cout << "ZFar = "  << zFar << endl;
    cout << "Eye X = "<< eyeX << endl;
    cout << "Eye Y = "<< eyeY << endl;
    cout << "Eye Z = "<< eyeZ << endl;
    cout << "Center X = "<< centerX << endl;
    cout << "Center Y = "<< centerY << endl;
    cout << "Center Z = "<< centerZ << endl;
    cout << "Up X = "<< upX << endl;
    cout << "Up Y = " << upY << endl;
    cout << "Up Z = " << upZ << endl;
    cout << "Camera Info:" << endl;
    cout << "******************************************************************************************************************************************************************************" << endl;
}
