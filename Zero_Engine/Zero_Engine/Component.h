#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Globals.h"

class GameObject;

enum ComponentType
{
	COMP_TRANSFORM,
	COMP_MESH,
	COMP_MATERIAL,
	COMP_NULL
};

class Component
{
public:
	Component(GameObject* _go)
	{
		go = _go;
	}
	~Component() {}

	virtual void Enable() 
	{
		enabled = true;
	}

	virtual void Update() 
	{
	}

	virtual void Disable() 
	{
		enabled = false;
	}

	virtual void ShowEditor()
	{
	}

public:
	ComponentType type = COMP_NULL;
	bool enabled = true;

	GameObject* go = NULL;

};

#endif // __COMPONENT_H__

