#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleFBXLoader.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include "Glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")

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

	//InitCubeIndices();

	street = App->go->AddGameObject();
	App->fbx->LoadFBXRoot("Game/Street environment_V01.fbx", street);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	street = nullptr;

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	return UPDATE_CONTINUE;
}

//Draws everything on scene, to be called in ModuleRenderer
void ModuleSceneIntro::Render()
{
	Plane3D(0, 1, 0, 0).Render();
}


//OPENGL Cubes
//--------------------------------------------------
void ModuleSceneIntro::DirectModeCube()
{
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
}

void ModuleSceneIntro::InitCubeIndices()
{
	my_id = 0;

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	glGenBuffers(1, (GLuint*)&(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, g_vertex_buffer_data, GL_STATIC_DRAW);
}
//--------------------------------------------------