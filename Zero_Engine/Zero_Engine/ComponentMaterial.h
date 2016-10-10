#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"
#include "Texture.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* _go, Texture* _tex);
	~ComponentMaterial();

	void Update();

private:
	Texture* tex;
};

#endif // __COMPONENT_MATERIAL_H__

