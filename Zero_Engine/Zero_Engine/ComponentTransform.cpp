#include "ComponentTransform.h"
#include "GameObject.h"

ComponentTransform::ComponentTransform(GameObject* _go) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = float3::zero;
	scale = float3::one;
	rotation = Quat::identity;
}


ComponentTransform::ComponentTransform(GameObject* _go, float3 _pos, float3 _scale, Quat _rot) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = _pos;
	scale = _scale;
	rotation = _rot;
}


ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Update()
{
}

float3 ComponentTransform::SetPosition(float3 _pos)
{
	return pos = _pos;
}

float3 ComponentTransform::SetScale(float3 _scale)
{
	return scale = _scale;
}

Quat ComponentTransform::SetRotation(Quat _rot)
{
	return rotation = _rot;
}

float4x4 ComponentTransform::GetDrawingMatrix()
{
	float4x4 ret = float4x4::FromTRS(pos, rotation, scale);

	if (go->parent != NULL)
	{
		ComponentTransform* parent_trans = (ComponentTransform*)go->parent->FindComponent(COMP_TRANSFORM);
		ret = parent_trans->GetDrawingMatrix()*ret;
	}

	return ret;
}
