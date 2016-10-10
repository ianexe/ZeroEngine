#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();
	Component* FindComponent(ComponentType type);

public:
	GameObject*					parent;
	char*						string;
	std::vector<Component*>		components;
	std::vector<GameObject*>	children;
};

#endif // __GAMEOBJECT_H__
