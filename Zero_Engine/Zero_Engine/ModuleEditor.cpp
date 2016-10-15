#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Start()
{
	//Initializing ImGui on window
	ImGui_ImplSdlGL3_Init(App->window->window);

	selected = nullptr;

	return true;
}

bool ModuleEditor::CleanUp()
{
	//Shutting down ImGui
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

update_status ModuleEditor::Update(float dt)
{
	//Create the menu bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				return UPDATE_STOP;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Hierarchy"))
				hierarchy = !hierarchy;

			if (ImGui::MenuItem("Properties"))
				properties = !properties;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo"))
				demo = !demo;

			if (ImGui::MenuItem("Download latest"))
				ShellExecute(0, 0, "https://github.com/ianexe/ZeroEngine/releases", 0, 0, SW_SHOW);

			if (ImGui::MenuItem("About"))
				about = !about;

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	//Show Demo Window
	if (demo)
		ImGui::ShowTestWindow();

	//Show About Window
	if (about)
		ShowAbout();

	//Show Hierarchy Window
	if (hierarchy)
		ShowHierarchy();

	if (properties)
		ShowProperties();

	return UPDATE_CONTINUE;
}

void ModuleEditor::Render()
{
	//Rendering ImGui
	ImGui::Render();
}

void ModuleEditor::ShowAbout()
{
	ImGui::Begin("About Zero Engine", &about, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("This is an engine created for learning purposes.");
	ImGui::Text("By Ian Trueba Lopez.");
	ImGui::Separator();
	ImGui::Text("Libraries used in this project:");
	ImGui::BulletText("SDL");
	ImGui::BulletText("Bullet");
	ImGui::BulletText("MatGeoLib");
	ImGui::BulletText("ImGui");
	ImGui::BulletText("PhysFS");
	ImGui::BulletText("Assimp");
	ImGui::BulletText("DevIL");
	ImGui::End();
}

void ModuleEditor::ShowHierarchy()
{
	ImGui::SetNextWindowPos({ 5,25 });
	ImGui::Begin("GameObjects", &hierarchy, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader(App->go->root->name.data()))
	{
		if (ImGui::IsItemClicked(0))
		{
			selected = App->go->root;
		}
		CreateHierarchyChild(App->go->root);
	}

	ImGui::End();
}

void ModuleEditor::CreateHierarchyChild(GameObject* go)
{
	for (vector<GameObject*>::iterator item = go->children.begin(); item != go->children.end(); ++item)
	{
		int flags = 0;
		if ((*item)->children.size() > 0)
		{
			if (selected == (*item))
				flags = ImGuiTreeNodeFlags_Selected;

			if (ImGui::TreeNodeEx((*item)->name.data(), flags))
			{
				if (ImGui::IsItemClicked(0))
				{
					selected = (*item);
				}
				CreateHierarchyChild(*item);
				ImGui::TreePop();
			}
		}

		else
		{
			if (selected == (*item))
				flags = ImGuiTreeNodeFlags_Selected;

			if (ImGui::TreeNodeEx((*item)->name.data(), ImGuiTreeNodeFlags_Leaf | flags))
			{
				if (ImGui::IsItemClicked(0))
				{
					selected = (*item);
				}
				ImGui::TreePop();
			}
		}
	}
}

void ModuleEditor::ShowProperties()
{
	ImGui::SetNextWindowPos({ SCREEN_WIDTH - 275, 25 });
	ImGui::SetNextWindowSize({ 275, 500 });
	ImGui::Begin("Properties", &properties);
	ImGui::Text("Selected GameObject:");
	if (selected != nullptr)
	{
		ImGui::SameLine();
		ImGui::Text(selected->name.data());
		ImGui::Separator();
		selected->ShowEditor();
	}

	ImGui::End();
}