#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glmath.h"
#include "Color.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:

	Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;
	vec3			GetPos()const;
public:

	Color color;
	mat4x4 transform;
	bool axis, wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class Cube3D : public Primitive
{
public:
	Cube3D();
	Cube3D(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	vec3 size;
};

// ============================================
class Sphere3D : public Primitive
{
public:
	Sphere3D();
	Sphere3D(float radius);
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class Cylinder3D : public Primitive
{
public:
	Cylinder3D();
	Cylinder3D(float radius, float height);
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class Line3D : public Primitive
{
public:
	Line3D();
	Line3D(float x, float y, float z);
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class Plane3D : public Primitive
{
public:
	Plane3D();
	Plane3D(float x, float y, float z, float d);
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};

#endif //__PRIMITIVE_H__