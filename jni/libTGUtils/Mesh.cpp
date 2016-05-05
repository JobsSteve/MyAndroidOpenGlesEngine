#include "Mesh.h"

#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <jni.h>
#include <android/log.h>
#include <iostream>
#include "Vector3F.h"
#include "stb_image.h"

#define LOG_TAG "TGMesh.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

using namespace TGMesh;

Mesh::Mesh() {
	this->m_pFaces = nullptr;
	this->m_pNormals = nullptr;
	this->m_pVertices = nullptr;
	this->m_pTextures = nullptr;
}

Mesh::~Mesh()
{
	LOGI("~~~~~~~~~~TGMesh()");
	if (m_pVertices != nullptr)
		free(m_pVertices);

	if (m_pNormals != nullptr)
		free(m_pNormals);

	if (m_pTextures != nullptr)
		free(m_pTextures);

	if (m_pFaces != nullptr)
		free(m_pFaces);

    glDeleteTextures(1,&m_textureID);
}

Mesh::Mesh(Vector3F *pVertices, Vector3F *pNormals, Vector3F *pTextures,
		Vector3F *pFaces, int iVerticeSize, int iNormalSize, int iTextureSize,
		int iFaceSize, int iMaxAmountOfVerticesPerFace) {
	this->m_textureID = 0;
	this->m_pVertices = pVertices;
	this->m_pNormals = pNormals;
	this->m_pTextures = pTextures;
	this->m_pFaces = pFaces;
	this->m_iVerticeSize = iVerticeSize;
	this->m_iNormalSize = iNormalSize;
	this->m_iTextureSize = iTextureSize;
	this->m_iFaceSize = iFaceSize;
	this->m_iMaxAmountOfVerticesPerFace = iMaxAmountOfVerticesPerFace;
}

void Mesh::Draw() {
	//glColor4f(1.0, 1.0, 1.0, 1.0);
#if defined(HAVE_GLES)
	if (m_iMaxAmountOfVerticesPerFace == 3)
		glBegin (GL_TRIANGLES);
	else if (m_iMaxAmountOfVerticesPerFace == 4)
		glBegin (GL_QUADS);
	else
		glBegin (GL_POLYGON);

	std::vector<GL_FLOAT>vv;

	for (int i = 0; i < m_iFaceSize; i++) {
		for (int j = 0; j < m_iMaxAmountOfVerticesPerFace; j++) {
			Vector3F face = m_pFaces[i * m_iMaxAmountOfVerticesPerFace + j];

			if (m_iNormalSize > 0) {
				Vector3F normal = m_pNormals[(int) (face.z) - 1];
				glNormal3f(normal.x, normal.y, normal.z);
			} else
				glNormal3f(0, 0, 0);

			if (m_iTextureSize > 0) {
				Vector3F texture = m_pTextures[(int) (face.y) - 1];
				glTexCoord2f(texture.x, texture.y);
			}

			Vector3F vertice = m_pVertices[(int) (face.x) - 1];
			glVertex3f(vertice.x, vertice.y, vertice.z);
			vv.push_back(vertice.x);
			vv.push_back(vertice.y);
			vv.push_back(vertice.z);
		}
	}
	glEnd();
#else
	LOGI("~~~~~~~~~~DrawwwwwwTGMesssssss()==%d",m_iMaxAmountOfVerticesPerFace);
	std::vector<float>vv, vn, vt;

		for (int i = 0; i < m_iFaceSize; i++) {
			for (int j = 0; j < m_iMaxAmountOfVerticesPerFace; j++) {
				Vector3F face = m_pFaces[i * m_iMaxAmountOfVerticesPerFace + j];

				if (m_iNormalSize > 0) {
					Vector3F normal = m_pNormals[(int) (face.z) - 1];
					vn.push_back(normal.x);
					vn.push_back(normal.y);
					vn.push_back(normal.z);
				}else{
					vn.push_back(0);
					vn.push_back(0);
					vn.push_back(0);
				}

				if (m_iTextureSize > 0) {
					Vector3F texture = m_pTextures[(int) (face.y) - 1];
					vt.push_back(texture.x);
					vt.push_back(texture.y);
				}

				Vector3F vertice = m_pVertices[(int) (face.x) - 1];
				vv.push_back(vertice.x);
				vv.push_back(vertice.y);
				vv.push_back(vertice.z);
			}
		}

	glEnableClientState(GL_VERTEX_ARRAY);

	if (m_iNormalSize > 0)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, &vn[0]);
	}
	if (m_iTextureSize > 0)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, &vt[0]);
	}
	glVertexPointer(3, GL_FLOAT, 0, &vv[0]);
	glDrawArrays(GL_TRIANGLES, 0, vv.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

#endif

}

void Mesh::InitTexturing(const char *texturePath) {
	if (m_textureID == 0) {
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		int width = 64, height = 64, bpp = 32;
		unsigned char* imgData = stbi_load(texturePath, &width, &height,
				&bpp, 4);
		glTexImage2D(GL_TEXTURE_2D, 0,					//level
				GL_RGBA,			//internal format
				width,				//width
				height,				//height
				0,					//border
				GL_RGBA,			//data format
				GL_UNSIGNED_BYTE,	//data type
				imgData);			//data

		stbi_image_free(imgData);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}
