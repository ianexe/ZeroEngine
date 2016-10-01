#include "Globals.h"
#include "Application.h"
#include "ModulePhysX.h"
#include "PhysXBody.h"
#include "Primitive.h"

#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3DEBUG_x86.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3CommonDEBUG_x86.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysX3ExtensionsDEBUG.lib")
#pragma comment (lib, "PhysX/Lib/vc14win32/PhysXProfileSDKDEBUG.lib")

//Number of working threads
#define THREADS 2

ModulePhysX::ModulePhysX(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}


ModulePhysX::~ModulePhysX()
{
}

bool ModulePhysX::Init()
{
	//Initializing PhysX
	//-------------------------
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocatorCallback, gErrorCallback);

	PxProfileZoneManager* gProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	if (!gProfileZoneManager)
		LOG("PxProfileZoneManager::createProfileZoneManager failed!");

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), recordMemoryAllocations, gProfileZoneManager);
	if (!gPhysics)
		LOG("PxCreatePhysics failed!");
	//-------------------------

	//Threading
	//-------------------------
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());

	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	//[...]

	// create CPU dispatcher which mNbThreads worker threads
	gDispatcher = PxDefaultCpuDispatcherCreate(THREADS);
	if (!gDispatcher)
		LOG("PxDefaultCpuDispatcherCreate failed!");
	sceneDesc.cpuDispatcher = gDispatcher;

	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	//[...]

	gScene = gPhysics->createScene(sceneDesc);
	//-------------------------

	//Geometry
	//-------------------------
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);
	//-------------------------
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
	gScene->simulate(1.0f / 60.0f);
	gScene->fetchResults(true);
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

PhysXBody* ModulePhysX::AddBody(const Cube& cube, float mass, bool isSensor)
{
	PhysXBody* pbody = nullptr;
	PxRigidDynamic* body = gPhysics->createRigidDynamic(PxTransform(0,0,0));
	//PxQuat q;
	//q.createIdentity();
	//PxTransform pose(q);
	PxShape* aBoxShape = body->createShape(PxBoxGeometry(1 / 2, 1 / 2, 1 / 2), *gMaterial);
	//aBoxShape->setLocalPose(pose);
	PxRigidBodyExt::updateMassAndInertia(*body, mass);
	gScene->addActor(*body);
	pbody = new PhysXBody(body);

	/*
	btCollisionShape* colShape = new btSphereShape(sphere.radius);
	shapes.push_back(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&sphere.transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.push_back(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	if (isSensor)
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.push_back(pbody);

	return pbody;
	*/
	return pbody;
}