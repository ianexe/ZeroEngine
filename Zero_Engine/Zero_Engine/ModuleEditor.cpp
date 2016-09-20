#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "Imgui\imgui.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Start()
{
	return true;
}

bool ModuleEditor::CleanUp()
{
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
	if (demo)
		ImGui::ShowTestWindow();

	if (about)
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
		ImGui::End();
	}


	return UPDATE_CONTINUE;
}