#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"
#include "Mesh.h"
#include <vector>

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* _go);
	ComponentMesh(GameObject* _go, Mesh* _mesh);
	~ComponentMesh();

	void Update();

	void SetMesh(Mesh _mesh);
	void SetMesh2(std::vector<Mesh> _mesh);
	Mesh GetMesh();
	std::vector<Mesh> GetMesh2();

private:
	Mesh mesh;
	std::vector<Mesh> mesh2;
};

#endif // __COMPONENT_MESH_H__
