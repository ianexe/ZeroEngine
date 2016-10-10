#ifndef __MODULE_FBXLOADER_H__
#define __MODULE_FBXLOADER_H__

#include "Module.h"
#include "Mesh.h"
#include "Texture.h"

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

