#include "Globals.h"
#include "Application.h"
#include "ModuleGOManager.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

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
	//Render
	//------------
	for (vector<GameObject*>::iterator item = root->children.begin(); item != root->children.end(); ++item)
	{
		if ((*item)->enabled)
		{
			ComponentTransform* _trans = (ComponentTransform*)(*item)->FindComponent(COMP_TRANSFORM);
			ComponentMesh* _mesh = (ComponentMesh*)(*item)->FindComponent(COMP_MESH);
			ComponentMaterial* _material = (ComponentMaterial*)(*item)->FindComponent(COMP_MATERIAL);

			Mesh item_mesh = _mesh->GetMesh();

			if (_material != nullptr)
				App->renderer3D->RenderMesh(item_mesh, _material->GetTexture());

			else
				App->renderer3D->RenderMesh(item_mesh, nullptr);
		}
	}
	//------------

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

