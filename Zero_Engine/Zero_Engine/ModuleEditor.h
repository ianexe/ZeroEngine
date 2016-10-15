#ifndef __MODULE_EDITOR_H__
#define __MODULE_EDITOR_H__

#include "Module.h"
#include "Globals.h"

class GameObject;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Render();
	void ShowAbout();

	void ShowHierarchy();
	void CreateHierarchyChild(GameObject* go);

	void ShowProperties();

public:
	bool demo = false;
	bool about = false;
	bool hierarchy = true;
	bool properties = true;

	GameObject* selected = nullptr;
};

#endif // __MODULE_EDITOR_H__
