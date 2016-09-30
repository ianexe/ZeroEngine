#include "Globals.h"
#include "Application.h"
#include "ModulePhysX.h"

#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3DEBUG_x86.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3CommonDEBUG_x86.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3ExtensionsDEBUG.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysXProfileSDKDEBUG.lib")


ModulePhysX::ModulePhysX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModulePhysX::~ModulePhysX()
{
}

bool ModulePhysX::Init()
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocatorCallback, gErrorCallback);

	PxProfileZoneManager* gProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	if (!gProfileZoneManager)
		LOG("PxProfileZoneManager::createProfileZoneManager failed!");

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), recordMemoryAllocations, gProfileZoneManager);
	if (!gPhysics)
		LOG("PxCreatePhysics failed!");



	return true;
}

bool ModulePhysX::Start()
{
	return true;
}

update_status ModulePhysX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModulePhysX::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModulePhysX::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModulePhysX::CleanUp()
{
	gPhysics->release();
	gFoundation->release();
	return true;
}