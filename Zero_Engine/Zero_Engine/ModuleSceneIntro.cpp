#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

	//Draw Line
	/*
	//------------------------------
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f);
	glEnd();

	glLineWidth(1.0f);
	//------------------------------
	*/

	//Cube
	//Face1
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glVertex3f(-1.f, 1.f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 1.f, 0.f);
	glVertex3f(-1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();

	//Face2
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, -1.f);
	glVertex3f(0.f, 1.f, -1.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 1.f, -1.f);
	glVertex3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();

	//Face3
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, 0.f);
	glEnd();

	//Face4
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 1.f, 0.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glVertex3f(-1.f, 0.f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 1.f, 0.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();

	//Face5
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(0.f, 1.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 0.f, -1.f);
	glVertex3f(0.f, 1.f, -1.f);
	glVertex3f(0.f, 0.f, -1.f);
	glEnd();

	//Face6
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(-1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, -1.f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.f, 0.f, 0.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glVertex3f(0.f, 0.f, -1.f);
	glEnd();

	glLineWidth(1.0f);

	return UPDATE_CONTINUE;
}


