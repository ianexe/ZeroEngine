#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

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
	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		(*item)->Update();
	}
	for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
	{
		(*item)->Update();
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


