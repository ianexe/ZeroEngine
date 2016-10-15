#include "ComponentMesh.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

ComponentMesh::ComponentMesh(GameObject* _go) : Component(_go)
{
	type = COMP_MESH;
	mesh = nullptr;
}

ComponentMesh::ComponentMesh(GameObject* _go, Mesh* _mesh) : Component (_go)
{
	type = COMP_MESH;
	mesh = _mesh;
}

ComponentMesh::~ComponentMesh()
{
	RELEASE(mesh);
}

void ComponentMesh::Update()
{
}

void ComponentMesh::SetMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

Mesh* ComponentMesh::GetMesh()
{
	return mesh;
}

void ComponentMesh::ShowEditor()
{
	ImGui::Text("Mesh");
	ImGui::Checkbox("MeshActive", &enabled);
	ImGui::BulletText("Indices Num: %i", mesh->num_indices);
	ImGui::BulletText("Vertices Num: %i", mesh->num_vertices);
	ImGui::BulletText("Normals Num: %i", mesh->num_normals);
	ImGui::BulletText("UVs Num: %i", mesh->num_uvs);
	ImGui::Separator();
}

