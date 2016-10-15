#ifndef __MODULE_RENDERER3D_H__
#define __MODULE_RENDERER3D_H__

#include "Module.h"
#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct Mesh;
struct Texture;

typedef void* SDL_GLContext;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height, float fovy);

	void RenderMesh(Mesh* mesh, float4x4 trans, Texture* tex);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};

#endif // __MODULE_RENDERER3D_H__