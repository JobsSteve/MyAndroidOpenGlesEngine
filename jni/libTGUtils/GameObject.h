#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameObject.h"
#include "Mesh.h"

using namespace TGMesh;

class GameObject
{
public:
	GameObject(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, std::string objectPath);
	virtual void Draw();

	float m_fpXCoordinate, m_fpYCoordinate, m_fpZCoordinate;
	Mesh* m_mesh;

};

#endif
