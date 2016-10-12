#include "ComponentMaterial.h"

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
