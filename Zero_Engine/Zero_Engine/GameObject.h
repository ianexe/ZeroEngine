#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* _parent);
	~GameObject();

	void Update();
	Component* FindComponent(ComponentType type);

	void AddChild(GameObject* _child);
	Component* AddComponent(ComponentType type);

	void SetName(char* _name);

public:
	GameObject*					parent = nullptr;
	char*						name = "GameObject";
	std::vector<Component*>		components;
	std::vector<GameObject*>	children;
};

#endif // __GAMEOBJECT_H__
