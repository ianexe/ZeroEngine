#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Component.h"
#include "MathGeoLib\MathGeoLib.h"
#include "glmath.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* _go);
	ComponentTransform(GameObject* _go, float3 _pos, float3 _scale, Quat _rot);
	~ComponentTransform();

	void Update();

	float3 SetPosition(float3 _pos);
	float3 SetScale(float3 _scale);
	Quat SetRotation(Quat _rot);

	Quat SetRotationEuler(float3 euler);

	float4x4 GetDrawingMatrix();

	void ShowEditor();

private:
	float3	pos;
	float3	scale;
	Quat	rotation;
	float3	euler_rot;

	float4x4 local_trans;
};

#endif // __COMPONENT_TRANSFORM_H__


