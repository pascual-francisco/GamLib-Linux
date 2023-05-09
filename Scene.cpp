#include "stdafx.h"

Scene::Scene(GLuint id, bool act, GLfloat viewportX, GLfloat viewportY, GLfloat viewportW, GLfloat viewportH, GLuint program, GLuint type, GLfloat left, GLfloat right, GLfloat bottom,
GLfloat top, GLfloat znear, GLfloat zfar, GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
	sceneID = id;
	active = act;
	programID = program;
	viewPort.x = viewportX;
	viewPort.y = viewportY;
	viewPort.w = viewportW;
	viewPort.h = viewportH;

	ptrObjects = nullptr;
	ptrBackground = nullptr;
	ptrForeground = nullptr;

    //ptrCamera = new Camera(true, program, type, left, right, bottom, top, znear, zfar, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

//
//   mat4 projection = mat4(1.0f);
//	mat4 view = mat4(1.0f);
//
//	//Init Samplers
//	int samplers[32];
//	for (uint i = 0; i < 32; i++)
//		samplers[i] = i;
//
//	glUniform1iv(glGetUniformLocation(programID, "fSamplers"), 32, samplers);
//
//	//Init Matrices to 1
//	projection = mat4(1.0f);
//	view = mat4(1.0f);
//
//	//Init Projection
//	projection = glm::ortho(0.0f, float(viewPort.w), 0.0f, float(viewPort.h), 1000.0f, -1000.0f);
//
//	//Init Camera
//	view = glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f));
//
//	//Init Origin
//	view = glm::translate(view, vec3(0.0f, 0.0f, 0.0f));
//
//	glUniformMatrix4fv(glGetUniformLocation(programID, "vProjection"), 1, GL_FALSE, &projection[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(programID, "vView"), 1, GL_FALSE, &view[0][0]);
}

Scene::~Scene()
{
    delete ptrCamera;
	delete ptrObjects;
	delete ptrBackground;

	if(ptrForeground!=nullptr)
		delete ptrForeground;
}

void Scene::update()
{
	if (ptrBackground != nullptr)
	{
		updateBackground();
		ptrBackground->update();
		ptrBackground->batchDraw();
	}

	if (ptrObjects != nullptr)
	{
		updateObjects();
		ptrObjects->update();
		ptrObjects->batchDraw();
	}

	if (ptrForeground != nullptr)
	{
		updateForeground();
		ptrForeground->update();
		ptrForeground->batchDraw();
	}
}

void Scene::print() const
{
	if(ptrObjects != nullptr)
		ptrObjects->print();

	if(ptrBackground != nullptr)
		ptrBackground->print();

	if(ptrForeground != nullptr)
		ptrForeground->print();

	if(ptrCamera != nullptr)
		ptrCamera->print();

}
