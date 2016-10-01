#pragma once
#include "Module.h"
#include "Globals.h"
#include "PhysX\Include\PxPhysicsAPI.h"

using namespace physx;

class ModulePhysX : public Module
{
public:
	ModulePhysX(Application* app, bool start_enabled = true);
	~ModulePhysX();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PxMaterial* CreateMaterial(float a, float b, float c);

public:
	PxDefaultErrorCallback	gErrorCallback;
	PxDefaultAllocator		gAllocatorCallback;

	PxFoundation*			gFoundation = NULL;
	PxPhysics*				gPhysics = NULL;

	PxDefaultCpuDispatcher*	gDispatcher = NULL;
	PxScene*				gScene = NULL;

	PxMaterial*				gMaterial = NULL;

	bool					recordMemoryAllocations = true;

};

