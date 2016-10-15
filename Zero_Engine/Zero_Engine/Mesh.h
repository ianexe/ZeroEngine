#ifndef __MESH_H__
#define __MESH_H__

#include "Globals.h"

class Mesh
{
public:
	Mesh()
	{}

	~Mesh()
	{
		delete(vertices);
		vertices = nullptr;

		delete(indices);
		indices = nullptr;

		delete(normals);
		normals = nullptr;

		delete(uvs);
		uvs = nullptr;
	}
public:
	//Vertices
	uint id_vertices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;

	//Indices
	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	//Normals
	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = nullptr;

	//UVs
	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = nullptr;
};

#endif // __MESH_H__