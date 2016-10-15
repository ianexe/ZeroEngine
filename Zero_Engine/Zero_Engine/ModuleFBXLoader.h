#ifndef __MODULE_FBXLOADER_H__
#define __MODULE_FBXLOADER_H__

#include "Module.h"
#include "Mesh.h"
#include "Texture.h"
#include "MathGeoLib\MathGeoLib.h"

class GameObject;

struct aiNode;
struct aiScene;

class ModuleFBXLoader : public Module
{
public:
	ModuleFBXLoader(Application* app, bool start_enabled = true);
	~ModuleFBXLoader();

	bool Init();
	bool CleanUp();

	bool LoadFBXRoot(const char* path, GameObject* go = nullptr);
	void LoadNode(aiNode* node, const aiScene* scene, GameObject* go);

	Texture* LoadTexture(const char* path);

public:

};

#endif // __MODULE_FBXLOADER_H__

