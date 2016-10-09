#ifndef __MODULE_FBXLOADER_H__
#define __MODULE_FBXLOADER_H__

#include "Module.h"

struct Mesh
{
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

struct Texture
{
	uint id = 0;
	int width = 0;
	int height = 0;
};

class ModuleFBXLoader : public Module
{
public:
	ModuleFBXLoader(Application* app, bool start_enabled = true);
	~ModuleFBXLoader();

	bool Init();
	bool CleanUp();

	vector<Mesh> LoadMesh(const char* path);
	Texture LoadTexture(const char* path);

public:

};

#endif // __MODULE_FBXLOADER_H__

