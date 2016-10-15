#include "ComponentTransform.h"
#include "GameObject.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

ComponentTransform::ComponentTransform(GameObject* _go) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = float3::zero;
	scale = float3::one;
	rotation = Quat::identity;
	euler_rot = rotation.ToEulerXYZ();
	local_trans = float4x4::FromTRS(pos, rotation, scale);
}


ComponentTransform::ComponentTransform(GameObject* _go, float3 _pos, float3 _scale, Quat _rot) : Component(_go)
{
	type = COMP_TRANSFORM;
	pos = _pos;
	scale = _scale;
	rotation = _rot;
	euler_rot = rotation.ToEulerXYZ();
	euler_rot *= 360;
	euler_rot /= 2 * pi;
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
	euler_rot = rotation.ToEulerXYZ();
	euler_rot *= 360;
	euler_rot /= 2 * pi;
	local_trans = float4x4::FromTRS(pos, rotation, scale);
	return rotation;
}

Quat ComponentTransform::SetRotationEuler(float3 euler)
{
	float3 _euler = euler;
	_euler *= 2 * pi;
	_euler /= 360;
	rotation = rotation.FromEulerXYZ(_euler.x, _euler.y, _euler.z);
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

void ComponentTransform::ShowEditor()
{
	ImGui::Text("Transformation");
	ImGui::PushItemWidth(200);
	if (ImGui::DragFloat3("Position", pos.ptr(), 0.2f))
	{
		SetPosition(pos);
	}

	if (ImGui::DragFloat3("Scale", scale.ptr(), 0.05f))
	{
		SetScale(scale);
	}

	if (ImGui::DragFloat3("Rotation", euler_rot.ptr(), 0.5f, -180.0f, 180.0f))
	{
		SetRotationEuler(euler_rot);
	}
	ImGui::PopItemWidth();
	ImGui::Separator();
}
