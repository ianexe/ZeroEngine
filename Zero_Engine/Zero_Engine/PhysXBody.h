#pragma once

#include "PhysX\Include\PxPhysicsAPI.h"
#include <list>

using namespace std;
using namespace physx;

class Module;
class vec3;

struct PhysXBody
{
	friend class ModulePhysX;
public:
	PhysXBody(PxRigidDynamic* body);
	~PhysXBody();

	void Push(float x, float y, float z);
	PxMat44 GetTransform() const;
	void SetTransform(const PxMat44 matrix) const;
	void SetPos(float x, float y, float z);
	void Stop();
	void SetRotation(float x, float y, float z);
	vec3 GetPosition()const;

	PxTransform GetRealTransform()const;
	void ApplyCentralForce(PxVec3& force);

	void SetBounciness(const float restitution, const float friction);

private:
	PxRigidDynamic* body = nullptr;
	PxMaterial*		material = nullptr;

public:
	list<Module*> collision_listeners;
};

