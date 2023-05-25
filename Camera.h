#include "stdafx.h"

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
    mat4    mProjection;
    mat4	   mView;

      Camera(bool active = true, GLuint type = 0, GLfloat left = 0.0f, GLfloat right = 256.0f, GLfloat bottom = 0.0f, GLfloat top = 224.0f, GLfloat zNear = 1000.0f ,
      GLfloat zFar = -1000.0f, GLfloat eyeX = 0.0f, GLfloat eyeY = 0.0f, GLfloat eyeZ = 0.0f, GLfloat centerX = 0.0f , GLfloat centerY = 0.0f , GLfloat centerZ = -1.0f, GLfloat upX = 0.0f,
      GLfloat upY = 1.0f, GLfloat upZ = 0.0f);
      ~Camera();

      void initCamera(bool active, GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar, GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
      		GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);

      void initProjection(GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
      void initView(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat up, GLfloat uy, GLfloat uz);
      void initOrigin(GLfloat x, GLfloat y, GLfloat z);
      void print() const;
    private:

};
#endif

