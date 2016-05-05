#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include "Mesh.h"

using namespace TGMesh;

extern Mesh* GetModelFromOBJ(std::string filePath);

#endif
