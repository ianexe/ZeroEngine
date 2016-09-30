#pragma once
#include "Module.h"
#include "Globals.h"
#include "PhysX\Include\PxPhysicsAPI.h"

using namespace physx;

class ModulePhysX : public Module
{
public:
	ModulePhysX(Application* app, bool start_enabled);
	~ModulePhysX();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	PxDefaultErrorCallback	gErrorCallback;
	PxDefaultAllocator		gAllocatorCallback;

	PxFoundation*			gFoundation = NULL;
	PxPhysics*				gPhysics = NULL;

	bool					recordMemoryAllocations = true;

};

