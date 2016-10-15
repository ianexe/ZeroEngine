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

	void Render();
	void RenderChild(GameObject* go);

	GameObject* AddGameObject(GameObject* parent = nullptr);
	void RemoveGameObject(GameObject* go = nullptr);

	void ShowEditor();

private:
	GameObject* root;
};

#endif // __MODULE_GOMANAGER_H__
