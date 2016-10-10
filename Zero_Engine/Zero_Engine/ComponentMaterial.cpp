#include "ComponentMaterial.h"

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
