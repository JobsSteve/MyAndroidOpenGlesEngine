#ifndef MESH_H
#define MESH_H

#include "vector"
#include "Vector3F.h"

#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <GLES/gl.h>

namespace TGMesh {
class Mesh
{
public:
	Mesh();
	GLuint m_textureID;

	Mesh(Vector3F *pVertices, Vector3F *pNormals, Vector3F *pTextures, Vector3F *pFaces, int iVerticeSize, int iNormalSize, int iTextureSize, int iFaceSize, int iMaxAmountOfVerticesPerFace);
	~Mesh();
	Vector3F *m_pVertices;
	Vector3F *m_pNormals;
	Vector3F *m_pTextures;
	Vector3F *m_pFaces;
	int m_iVerticeSize;
	int m_iNormalSize;
	int m_iTextureSize;
	int m_iFaceSize;
	int m_iMaxAmountOfVerticesPerFace;

	void Draw();
	void InitTexturing(const char *texturePath);
};

}

#endif

