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


#define _USE_MATH_DEFINES

#include <math.h>
#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>
#include <app.h>
#include <libpng/png.h>
#include <libzip/zip.h>
#include <libobj/MeshUtil.h>

#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

#define LOG_TAG "app.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

// All rendering meshes
const char* gAPKPATH;
bool gJavaReady = false;
bool gTouchEnabled = false;
float gTouchDownPoint[] = {0, 0};
float gTouchUpPoint[] = {0, 0};
float gTouchMoveX = 0, gTouchMoveY = 0;
std::vector<Mesh*> gDrawObjects;
Mesh* gCurrTouchMesh = nullptr;

// Global view settings
int VIEW_WIDHT = 0;
int VIEW_HEIGHT = 0;

// Lights
float lightSpec[]= {1.0f, 1.0f, 1.0f, 1.0f };
float lightAmb[]= { 0.6f, 0.6f, 0.6f, 1.0f };
float lightDif[]= {10.0f, 10.0f, 10.0f, 1.0f };
float lightPos[]= { 0.0f, 10.0f, 0.0f, 0.0f };

void initGlobalThings() {
	gTouchEnabled = false;
	gCurrTouchMesh = nullptr;

	for(size_t i=0; i<gDrawObjects.size(); ++i)
		delete gDrawObjects[i];
	gDrawObjects.clear();
}

// For checking OpenGL errors and print it out.
void CheckErrors(std::string desc) {
  GLenum e = glGetError();
  if (e != GL_NO_ERROR) {
    LOGI("OpenGL error in \"%s\": %d (%d)\n", desc.c_str(), e, e);
    //exit(20);
  }
}

Mesh* loadAssetObjMesh(const char* objChars, const char* txtChars) {
	if (gJavaReady) {
		zip* APKArchive = zip_open(gAPKPATH, 0, NULL);
		Mesh* mesh = MeshUtil::loadMesh(APKArchive, objChars, txtChars);
		zip_close(APKArchive);
		return mesh;
	}
	return NULL;
}

// Make Frustumx
void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
    GLfloat xmin, xmax, ymin, ymax;

    ymax = zNear * (GLfloat)tan(fovy * M_PI / 360.0f);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustumx((GLfixed)(xmin * 65536), (GLfixed)(xmax * 65536),
               (GLfixed)(ymin * 65536), (GLfixed)(ymax * 65536),
               (GLfixed)(zNear * 65536), (GLfixed)(zFar * 65536));

}


void onResize(int w, int h)
{
	VIEW_WIDHT = w;
	VIEW_HEIGHT = h;

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();

    gluPerspective(45.0f, (float)w / h, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onSurfaceCreated(const char* pathStr)
{
	LOGI("onSurfaceCreated: %s", pathStr);
	initGlobalThings();

	gAPKPATH = pathStr;
    gJavaReady = true;


    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    Mesh* m1 = loadAssetObjMesh("assets/table.obj", "assets/table.png");
    m1->ID = 111;
    m1->boundRadius = 3;
    m1->move(3, 4, -10);

    Mesh* m2 = loadAssetObjMesh("assets/cube0.obj", "assets/cube0.png");
    m2->ID = 999;
    m2->boundRadius = 3;
    m2->move(0, 5, 0);


    Mesh* m3 = loadAssetObjMesh("assets/skydoom.obj", "assets/skydoom.png");
    m3->scale(30,30,30);

    gDrawObjects.push_back(m1);
    gDrawObjects.push_back(m2);
    gDrawObjects.push_back(m3);
}

void renderFrame()
{
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glTranslatef(gTouchMoveX, gTouchMoveY, -30.0f);
    glTranslatef(0, 0, -30.0f);
//    glRotatef(gTouchMoveY, 1.0, 0.0, 0.0);
    glRotatef(gTouchMoveX, 0.0, 1.0, 0.0);

	for(std::vector<Mesh*>::size_type i=0; i<gDrawObjects.size(); ++i) {
		gDrawObjects[i]->render();
		if (gTouchEnabled && gDrawObjects[i]->isTouched(gTouchUpPoint[0], gTouchUpPoint[1])) {
			gCurrTouchMesh = gDrawObjects[i];
		}
	}//end for

	gTouchEnabled = false;

	if (gCurrTouchMesh != nullptr) {
		gCurrTouchMesh->mRotate[0]++;
	}
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_loadAssetsObj(JNIEnv * env, jobject thiz, jstring obj, jstring txt)
{
	const char *objChars = env->GetStringUTFChars(obj, JNI_FALSE);
	const char *txtChars = env->GetStringUTFChars(txt, JNI_FALSE);

	// use your string

	loadAssetObjMesh(objChars, txtChars);

	env->ReleaseStringUTFChars(obj, objChars);
	env->ReleaseStringUTFChars(txt, txtChars);
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_resize(JNIEnv * env, jobject obj, jint width, jint height)
{
    onResize(width,height);
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_renderFrame(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_onSurfaceCreated(JNIEnv * env, jclass cls, jstring appPath)
{
    const char* pathStr;
    jboolean copyFlag;

    pathStr = env->GetStringUTFChars(appPath,&copyFlag);

    onSurfaceCreated(pathStr);
}
JNIEXPORT void JNICALL Java_com_objLoader_AppLib_touchDown(JNIEnv * env, jobject thiz, jfloat x, jfloat y)
{
	gTouchDownPoint[0] = x;
	gTouchDownPoint[1] = y;
}
JNIEXPORT void JNICALL Java_com_objLoader_AppLib_touchMove(JNIEnv * env, jobject thiz, jfloat x, jfloat y)
{
	gTouchMoveX = x - gTouchDownPoint[0];
	gTouchMoveY = y - gTouchDownPoint[1];
}
JNIEXPORT void JNICALL Java_com_objLoader_AppLib_touchUp(JNIEnv * env, jobject thiz, jfloat x, jfloat y)
{
	gTouchUpPoint[0] = x;
	gTouchUpPoint[1] = y;
	gTouchEnabled = true;
	gCurrTouchMesh = nullptr;
}

