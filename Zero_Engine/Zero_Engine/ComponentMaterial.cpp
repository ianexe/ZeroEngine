#include "ComponentMaterial.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

ComponentMaterial::ComponentMaterial(GameObject* _go) : Component(_go)
{
	type = COMP_MATERIAL;
	tex = nullptr;
}

ComponentMaterial::ComponentMaterial(GameObject* _go, Texture* _tex) : Component(_go)
{
	type = COMP_MATERIAL;
	tex = _tex;
}

ComponentMaterial::~ComponentMaterial()
{
	RELEASE(tex);
}

void ComponentMaterial::Update()
{
}

void ComponentMaterial::SetTexture(Texture* _tex)
{
	tex = _tex;
}

Texture* ComponentMaterial::GetTexture()
{
	return tex;
}

void ComponentMaterial::ShowEditor()
{
	ImGui::Text("Material");
	ImGui::Separator();
}