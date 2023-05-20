#include "stdafx.h"

Camera::Camera(bool active,GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
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
    mProjection = mat4(1.0f);
    mView = mat4(1.0f);
    initCamera(active, type, left, right, bottom, top, znear, zfar, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

Camera::~Camera()
{

}

void Camera::initCamera(bool active,  GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
   this->active = active;

   initProjection(type, left, right, bottom, top, zNear, zFar);

   initView(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

   initOrigin(eyeX, eyeY, eyeZ);
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

   if(type == 0)
   {
      mProjection = glm::ortho(left, right, bottom, top, znear, zfar);
   }
   else
   {
      mProjection = glm::perspective(45.0f, (abs(right-left)/abs(top-bottom)), znear, zfar);
   }

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
    mView = glm::lookAt(vec3(eyeX, eyeY, eyeZ), vec3(centerX, centerY, centerZ), vec3(upX, upY, upZ));

}

void Camera::initOrigin(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ)
{
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    mView = glm::translate(mView, vec3(eyeX, eyeY, eyeZ));

}


void Camera::print()const
{
    cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Camera Info:" << endl;
   cout << "Active ="<< active << endl;
    cout << "Projection Type = ";
    if(projectionType == 0)  { cout<<"Ortho"<<endl; }
    else { cout<<"Perspective"<<endl;}
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
