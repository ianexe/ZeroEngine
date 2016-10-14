#include "ComponentTransform.h"
#include "GameObject.h"

ComponentTransform::ComponentTransform(GameObject* _go) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = float3::zero;
	scale = float3::one;
	rotation = Quat::identity;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
}


ComponentTransform::ComponentTransform(GameObject* _go, float3 _pos, float3 _scale, Quat _rot) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = _pos;
	scale = _scale;
	rotation = _rot;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
}


ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Update()
{
}

float3 ComponentTransform::SetPosition(float3 _pos)
{
	pos = _pos;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
	return pos;
}

float3 ComponentTransform::SetScale(float3 _scale)
{
	scale = _scale;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
	return scale;
}

Quat ComponentTransform::SetRotation(Quat _rot)
{
	rotation = _rot;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
	return rotation;
}

float4x4 ComponentTransform::GetDrawingMatrix()
{
	float4x4 ret = local_trans;

	if (go->parent != nullptr)
	{
		ComponentTransform* comp = (ComponentTransform*)go->parent->FindComponent(COMP_TRANSFORM);
		ret = comp->GetDrawingMatrix()*ret;
	}

	return ret;
}
