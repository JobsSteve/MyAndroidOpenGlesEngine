#include "NormalCalculators.h"

#include <stdlib.h>

#ifdef _WIN32
#include <glut.h>
#include <Windows.h>
#else
#include <GLES/gl.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#endif

#include "Vector3F.h"

void CalculateVectorNormal(float fVert1[], float fVert2[],
								  float fVert3[], float *fNormalX,
								  float *fNormalY, float *fNormalZ)
{
	float Qx, Qy, Qz, Px, Py, Pz;

	Qx = fVert2[0] - fVert1[0];
	Qy = fVert2[1] - fVert1[1];
	Qz = fVert2[2] - fVert1[2];
	Px = fVert3[0] - fVert1[0];
	Py = fVert3[1] - fVert1[1];
	Pz = fVert3[2] - fVert1[2];

	*fNormalX = Py*Qz - Pz*Qy;
	*fNormalY = Pz*Qx - Px*Qz;
	*fNormalZ = Px*Qy - Py*Qx;
}

void CalculateVectorNormal2(Vector3F vertices[4], Vector3F *normal)
{
	for (int i = 0; i < 4; i++)
	{
		int j = (i + 1) % 4;
		normal->x += (vertices[i].y - vertices[j].y)
			*(vertices[i].z + vertices[j].z);
		normal->y += (vertices[i].z - vertices[j].z)
			*(vertices[i].x + vertices[j].x);
		normal->z += (vertices[i].x - vertices[j].x)
			*(vertices[i].y + vertices[j].y);
	}
}
