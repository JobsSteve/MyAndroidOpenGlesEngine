#ifndef NORMALCALCULATORS_H
#define NORMALCALCULATORS_H

#include "Vector3F.h"

extern void CalculateVectorNormal(float fVert1[], float fVert2[],
								  float fVert3[], float *fNormalX,
								  float *fNormalY, float *fNormalZ);

extern void CalculateVectorNormal2(Vector3F vertex[4], Vector3F *normal);

#endif