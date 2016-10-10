#ifndef __COMPONENT_H__
#define __COMPONENT_H__

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
	Component() {}
	~Component() {}

	virtual void Enable() {}
	virtual void Update() {}
	virtual void Disable() {}

public:
	ComponentType type = COMP_NULL;
	bool enabled = true;
};

#endif // __COMPONENT_H__

