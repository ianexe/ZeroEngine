#include "Globals.h"
#include "Application.h"
#include "ModuleGOManager.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

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

void ModuleGOManager::Render()
{
	RenderChild(root);
}

void ModuleGOManager::RenderChild(GameObject* go)
{
	for (vector<GameObject*>::iterator item = go->children.begin(); item != go->children.end(); ++item)
	{
		RenderChild(*item);
		if ((*item)->enabled)
		{
			ComponentTransform* _trans = (ComponentTransform*)(*item)->FindComponent(COMP_TRANSFORM);
			ComponentMesh* _mesh = (ComponentMesh*)(*item)->FindComponent(COMP_MESH);
			ComponentMaterial* _material = (ComponentMaterial*)(*item)->FindComponent(COMP_MATERIAL);

			if (_mesh != nullptr && _mesh->enabled)
			{
				Mesh* item_mesh = _mesh->GetMesh();
				if (_material != nullptr && _material->enabled)
					App->renderer3D->RenderMesh(item_mesh, _trans->GetDrawingMatrix(),_material->GetTexture());

				else
					App->renderer3D->RenderMesh(item_mesh, _trans->GetDrawingMatrix(), nullptr);
			}
		}
	}
}

bool ModuleGOManager::CleanUp()
{
	bool ret = true;

	RemoveGameObject(root);

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

void ModuleGOManager::RemoveGameObject(GameObject* go)
{
	if (go->children.size() > 0)
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			RemoveGameObject(go->children[i]);
		}
	}
	if (go->parent != nullptr)
	{
		go->parent->RemoveChild(go);
	}
	RELEASE(go);
}

void ModuleGOManager::ShowEditor()
{
	ImGui::SetNextWindowPos({ 5,25 });
	ImGui::Begin("GameObjects", &App->editor->hierarchy, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader(root->name.data()))
	{
		App->editor->CreateHierarchyChild(root);
	}

	ImGui::End();
}