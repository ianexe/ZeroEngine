#include "PhysXBody.h"
#include "glmath.h"

PhysXBody::PhysXBody(PxRigidDynamic* _body) : body(_body)
{
	body->userData = this;
}


PhysXBody::~PhysXBody()
{
	//delete body;
}

void PhysXBody::Push(float x, float y, float z)
{
	//Not sure of this
	body->addForce(PxVec3(x, y, z), PxForceMode::eIMPULSE);
}

PxMat44 PhysXBody::GetTransform() const
{
	PxMat44 m;

	if (body != NULL)
	{
		// retrieve world space transform of rigid body
		PxTransform t = body->getGlobalPose();

		// convert to matrix form
		m = PxMat44(t);
	}

	else
	{
		m.createIdentity();
	}

	return m;
}

void PhysXBody::SetTransform(const PxMat44 matrix) const
{
	if (body != NULL)
	{
		PxTransform t;
		t = PxTransform(matrix);
		body->setGlobalPose(t);
	}
}

void PhysXBody::SetPos(float x, float y, float z)
{
	PxTransform t = body->getGlobalPose();
	PxMat44 m = PxMat44(t);
	m.setPosition(PxVec3(x, y, z));
	body->setGlobalPose(PxTransform(m));
}

void PhysXBody::SetRotation(float x, float y, float z)
{
	PxTransform t = body->getGlobalPose();
	//PxQuat q;
	//q.rotate(PxVec3(x, y, z));
	t.rotate(PxVec3(x, y, z));
	body->setGlobalPose(t);
}

void PhysXBody::Stop()
{
	body->setLinearVelocity(PxVec3(0, 0, 0));
	body->setAngularVelocity(PxVec3(0, 0, 0));
	body->clearForce();
}

PxTransform PhysXBody::GetRealTransform()const
{
	return body->getGlobalPose();
}

void PhysXBody::ApplyCentralForce(PxVec3& force)
{
	body->addForce(force, PxForceMode::eFORCE);
}

void PhysXBody::SetBounciness(float restitution, float friction)
{
	//body->setFriction(friction);
	//body->setRestitution(restitution);
}

vec3 PhysXBody::GetPosition()const
{
	vec3 ret;
	ret.x = PxMat44(body->getGlobalPose()).getPosition().x;
	ret.y = PxMat44(body->getGlobalPose()).getPosition().y;
	ret.z = PxMat44(body->getGlobalPose()).getPosition().z;
	return ret;
}
