#ifndef __MODULE_SCENEINTRO_H__
#define __MODULE_SCENEINTRO_H__

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class Mesh;
class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Render();

	void DirectModeCube();
	void InitCubeIndices();

public:
	GameObject* street;
	uint my_id;
};

#endif // __MODULE_SCENEINTRO_H__