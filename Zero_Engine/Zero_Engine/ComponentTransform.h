#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Component.h"
//#include "MathGeoLib\MathGeoLib.h"
#include "glmath.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* _go);
	///ComponentTransform(GameObject* _go, float3 _pos, float3 _scale, Quat _rot);
	~ComponentTransform();

	void Update();

	//float3 SetPosition(float3 _pos);
	//float3 SetScale(float3 _scale);
	//Quat SetRotiation(Quat _rot);

	//float4x4 GetDrawingMatrix();

private:
	//float3	pos;
	//float3	scale;
	//Quat	rotation;
};

#endif // __COMPONENT_TRANSFORM_H__


