#include "Globals.h"
#include "Application.h"
#include "ModuleGOManager.h"

ModuleGOManager::ModuleGOManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGOManager::~ModuleGOManager()
{
}

bool ModuleGOManager::Start()
{
	bool ret = true;

	root = new GameObject();
	root->SetName("root");
	root->AddComponent(COMP_TRANSFORM);

	return ret;
}

update_status ModuleGOManager::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleGOManager::Update(float dt)
{
	root->Update();
	return UPDATE_CONTINUE;
}

update_status ModuleGOManager::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleGOManager::CleanUp()
{
	bool ret = true;


	return ret;
}

GameObject* ModuleGOManager::AddGameObject(GameObject* parent)
{
	GameObject* ret;

	if (parent != nullptr)
		ret = new GameObject(parent);
		
	else
		ret = new GameObject(root);

	return ret;
}

