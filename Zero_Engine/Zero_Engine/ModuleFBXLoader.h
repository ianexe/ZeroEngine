#ifndef __MODULE_FBXLOADER_H__
#define __MODULE_FBXLOADER_H__

#include "Module.h"

struct Mesh
{
	uint id_vertices = 0; // id in VRAM 
	uint num_vertices = 0;
	float* vertices = nullptr;

	uint id_indices = 0; // id in VRAM 
	uint num_indices = 0;
	uint* indices = nullptr;
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

