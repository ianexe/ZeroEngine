#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform();
	~ComponentTransform();

	void Enable();
	void Update();
	void Disable();

public:

};

#endif // __COMPONENT_TRANSFORM_H__


