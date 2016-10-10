#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject* _go, Mesh* _mesh) : Component (_go)
{
	type = COMP_MESH;
	mesh = _mesh;
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Update()
{
}

