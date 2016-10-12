#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "Application.h"

using namespace std;

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* _parent)
{
	parent = _parent;
	_parent->AddChild(this);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (enabled)
	{
		for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
		{
			(*item)->Update();
		}
		for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
		{
			(*item)->Update();
		}
	}
}

void GameObject::Render()
{
	if (enabled)
	{
		ComponentTransform* _trans = (ComponentTransform*)FindComponent(COMP_TRANSFORM);
		ComponentMesh* _mesh = (ComponentMesh*)FindComponent(COMP_MESH);
		ComponentMaterial* _material = (ComponentMaterial*)FindComponent(COMP_MATERIAL);
	}
}

Component* GameObject::FindComponent(ComponentType type)
{
	Component* ret = nullptr;

	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		if ((*item)->type == type)
		{
			ret = (*item);
		}
	}

	return ret;
}

void GameObject::AddChild(GameObject* _child)
{
	children.push_back(_child);
}

Component* GameObject::AddComponent(ComponentType type)
{
	Component* ret = nullptr;

	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		if ((*item)->type == type)
		{
			//Cannot add this type of component twice (LOG doesn't work)
			return NULL;
		}
	}

	switch (type)
	{
	case COMP_TRANSFORM:
		ret = new ComponentTransform(this);
		break;
	case COMP_MESH:
		ret = new ComponentMesh(this);
		break;
	case COMP_MATERIAL:
		ret = new ComponentMaterial(this);
		break;
	default:
		break;
	}

	components.push_back(ret);

	return ret;
}


void GameObject::SetName(char* _name)
{
	name = _name;
}

void GameObject::Enable()
{
	enabled = true;
}

void GameObject::Disable()
{
	enabled = false;
}


