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
	//Render
	//------------
	Render(root);
	//------------

	//ShowEditor
	//------------
	ImGui::Begin("GameObjects");

		if (ImGui::CollapsingHeader(root->name.data()))
		{
			CreateUI(root);
			if (ImGui::IsItemClicked(0))
			{
				selected = root;
			}
		}
	
	ImGui::End();
	//------------

	if (selected != nullptr)
	{
		selected->ShowEditor();
	}

	return UPDATE_CONTINUE;
}

void ModuleGOManager::Render(GameObject* go)
{
	for (vector<GameObject*>::iterator item = go->children.begin(); item != go->children.end(); ++item)
	{
		Render(*item);
		if ((*item)->enabled)
		{
			ComponentTransform* _trans = (ComponentTransform*)(*item)->FindComponent(COMP_TRANSFORM);
			ComponentMesh* _mesh = (ComponentMesh*)(*item)->FindComponent(COMP_MESH);
			ComponentMaterial* _material = (ComponentMaterial*)(*item)->FindComponent(COMP_MATERIAL);

			if (_mesh != nullptr)
			{
				Mesh item_mesh = _mesh->GetMesh();
				if (_material != nullptr)
					App->renderer3D->RenderMesh(item_mesh, _trans->GetDrawingMatrix(),_material->GetTexture());

				else
					App->renderer3D->RenderMesh(item_mesh, _trans->GetDrawingMatrix(), nullptr);
			}
		}
	}
}

void ModuleGOManager::CreateUI(GameObject* go)
{
	bool selected_flag = false;
	for (vector<GameObject*>::iterator item = go->children.begin(); item != go->children.end(); ++item)
	{
		if (ImGui::TreeNodeEx((*item)->name.data()))
		{
			if (ImGui::IsItemClicked(0) && selected_flag == false)
			{
				selected = (*item);
				selected_flag = true;
			}
			CreateUI(*item);
			ImGui::TreePop();
		}
	}
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

