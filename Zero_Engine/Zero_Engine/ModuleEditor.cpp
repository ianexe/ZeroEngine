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
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Quit", NULL))
		{
			return UPDATE_STOP;
		}

		ImGui::EndMainMenuBar();
	}
	ImGui::ShowTestWindow();

	return UPDATE_CONTINUE;
}