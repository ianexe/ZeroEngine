#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject* _go) : Component(_go)
{
	type = COMP_MESH;
	mesh = nullptr;
	multiple = true;
}

ComponentMesh::ComponentMesh(GameObject* _go, Mesh* _mesh) : Component (_go)
{
	type = COMP_MESH;
	mesh = _mesh;
	multiple = true;
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Update()
{
}

