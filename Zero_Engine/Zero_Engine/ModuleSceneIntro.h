#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

struct Mesh;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();



public:
	uint my_id;

	vector<Mesh> warrior;
};
