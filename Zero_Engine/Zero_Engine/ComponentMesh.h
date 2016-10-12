#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"
#include "Mesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* _go);
	ComponentMesh(GameObject* _go, Mesh* _mesh);
	~ComponentMesh();

	void Update();

private:
	Mesh* mesh;
};

#endif // __COMPONENT_MESH_H__
