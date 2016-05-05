#include "GameObject.h"
#include "ObjectLoader.h"
#include <vector>
using namespace TGMesh;

GameObject::GameObject(float fpXCoordinate, float fpYCoordinate, float fpZCoordinate, std::string objectPath)
{
	this->m_fpXCoordinate = fpXCoordinate;
	this->m_fpYCoordinate = fpYCoordinate;
	this->m_fpZCoordinate = fpZCoordinate;

	if (objectPath != "")
		this->m_mesh = GetModelFromOBJ(objectPath);
}

void GameObject::Draw()
{
	glPushMatrix();
	m_mesh->Draw();
	glPopMatrix();
}
