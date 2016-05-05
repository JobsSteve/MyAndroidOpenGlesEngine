/*
 *
 *      Copyright TomkidGames
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "Mesh.h"

#include <GLES/gl.h>
#include <cmath>
#include <jni.h>
#include <android/log.h>

#define LOG_TAG "Mesh.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


Mesh::Mesh(GLuint _texture ,int n,float* vertexBuffer, float* textureCoordBuffer, float* normalBuffer)
{
	this->ID = 0;
	this->name = ""+this->ID;
	this->boundRadius = 0;
	this->mCenter[0] = 0;
	this->mCenter[1] = 0;
	this->mCenter[2] = 0;
	this->mScale[0] = 1;
	this->mScale[1] = 1;
	this->mScale[2] = 1;
	this->mRotate[0] = 0;
	this->mRotate[1] = 0;
	this->mRotate[2] = 0;

    this->vBuffer = vertexBuffer;
    this->tBuffer = textureCoordBuffer;
    this->nBuffer = normalBuffer;
    this->numberOfvertices = n;

    this->texture = _texture;
}

Mesh::~Mesh()
{
    LOGI("~Mesh() called for %d", ID);

    delete[] vBuffer;
    delete[] tBuffer;
    delete[] nBuffer;

    glDeleteTextures(1,&texture);

}

void Mesh::move(float x, float y, float z) {
	mCenter[0] = x;
	mCenter[1] = y;
	mCenter[2] = z;
}
void Mesh::rotate(float ax, float ay, float az) {
	mRotate[0] = ax;
	mRotate[1] = ay;
	mRotate[2] = az;
}
void Mesh::scale(float sx, float sy, float sz) {
	mScale[0] = sx;
	mScale[1] = sy;
	mScale[2] = sz;
}

void Mesh::render(void) const
{
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPushMatrix();
    	glTranslatef(mCenter[0], mCenter[1], mCenter[2]);
    	glRotatef(mRotate[0],1.0f,0.0f,0.0f);
    	glRotatef(mRotate[1],0.0f,1.0f,0.0f);
    	glRotatef(mRotate[2],0.0f,0.0f,1.0f);
    	glScalef(mScale[0],mScale[1],mScale[2]);

        glVertexPointer(3, GL_FLOAT, 0, this->vBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, this->tBuffer);
        glNormalPointer(GL_FLOAT, 0, this->nBuffer);

        glDrawArrays(GL_TRIANGLES, 0, this->numberOfvertices);

    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}

bool Mesh::isTouched(float x, float y)
{
	if (this->boundRadius > 0) {
		int dx = mCenter[0] -x;
		int dy = mCenter[1] - y;
		int r2 = boundRadius * boundRadius;
		if ((dx*dx + dy*dy) < r2) {
    		LOGI("Touched object [%d]", this->ID);
			return true;
		}
	}
	return false;
}
