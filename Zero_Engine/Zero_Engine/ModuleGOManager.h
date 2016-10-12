#ifndef __MODULE_GOMANAGER_H__
#define __MODULE_GOMANAGER_H__

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

class ModuleGOManager : public Module
{
public:
	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	GameObject* AddGameObject(GameObject* parent = nullptr);

public:
	GameObject* root;
};

#endif // __MODULE_GOMANAGER_H__
