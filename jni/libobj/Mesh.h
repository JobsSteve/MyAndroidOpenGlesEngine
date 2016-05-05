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
#ifndef MESH_H
#define MESH_H

#include <GLES/gl.h>
#include <string>

using namespace std;

class Mesh
{

private:

    int numberOfvertices;
    float* vBuffer;
    float* tBuffer;
    float* nBuffer;


    GLuint texture;

public:
    string name;
    int ID;
    int boundRadius; // bounds radius

    Mesh(GLuint _texture, int n, float* vertexBuffer, float* textureCoordBuffer, float* normalBuffer);
    virtual ~Mesh();


    float mScale[3];
    float mRotate[3];
    float mCenter[3]; // world center position
    void move(float x, float y, float z);
    void rotate(float ax, float ay, float az);
    void scale(float sx, float sy, float sz);

    void render(void) const;

    bool isTouched(float x, float y);
};

#endif // MESH_H
