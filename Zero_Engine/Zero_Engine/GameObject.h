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
	void Render();
	Component* FindComponent(ComponentType type);

	void AddChild(GameObject* _child);
	Component* AddComponent(ComponentType type);

	void SetName(char* _name);

	void Enable();
	void Disable();

	void ShowEditor();

public:
	GameObject*					parent = nullptr;
	std::string					name = "GameObject";
	std::vector<Component*>		components;
	std::vector<GameObject*>	children;
	bool						enabled = true;
};

#endif // __GAMEOBJECT_H__
