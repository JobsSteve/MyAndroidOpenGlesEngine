#include "Vector3F.h"

#include <iostream>

Vector3F::Vector3F(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3F::Vector3F(){}

std::ostream& operator<<(std::ostream& cout, Vector3F& f){
	cout << "x: " << f.x << " y: " << f.y << " z: " << f.z << std::endl;
	return cout;
}