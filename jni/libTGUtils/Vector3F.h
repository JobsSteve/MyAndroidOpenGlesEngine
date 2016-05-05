#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>

class Vector3F
{
public:
	Vector3F(float x, float y, float z); 
	Vector3F();
	float x, y, z;

	friend std::ostream& operator<<(std::ostream&, Vector3F&);

};

#endif