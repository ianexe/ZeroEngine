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

	vector<Mesh> LoadMesh(const char* path);
	void LoadMesh(const char* path, GameObject* go = nullptr);
	Texture* LoadTexture(const char* path);
	bool LoadFBXRoot(const char* path, GameObject* go = nullptr);
	void LoadNode(aiNode* node, const aiScene* scene, GameObject* go);

public:

};

#endif // __MODULE_FBXLOADER_H__

