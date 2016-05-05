#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>
#include <math.h>

#undef PI
#define PI 3.1415926535897932f

//void appInit();
static void prepareFrame(int width, int height);
void appRender(int width, int height);
static void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear,
			   GLfloat zFar);

static int sWindowWidth = 320;
static int sWindowHeight = 480;
int currentFlip = 1;
GLfloat change = 0.0f;

void drawCube()
{

    GLfloat box[] = {
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, box);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

}

extern "C" {
    JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeInit(JNIEnv * env);
    JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeResize(JNIEnv * env, jobject thiz, jint w, jint h);
    JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeRender(JNIEnv * env);
    JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoGLSurfaceView_nativeTogglePauseResume(JNIEnv * env, jobject thiz, jint flip);
};


JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeInit(JNIEnv * env)
{
    //appInit();
}

JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeResize(JNIEnv * env, jobject thiz, jint w, jint h)
{
    sWindowWidth = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "SanAngeles", "resize w=%d h=%d",
			w, h);
}

JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoRenderer_nativeRender(JNIEnv * env)
{
    appRender(sWindowWidth, sWindowHeight);
}


JNIEXPORT void JNICALL Java_com_unwrappedapps_android_demo_DemoGLSurfaceView_nativeTogglePauseResume(JNIEnv * env, jobject thiz, jint flip)
{
    currentFlip = flip;
}


static void drawModels()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -4.0f);
    if (currentFlip > 0) {
        change += 1.2f;
    }
    glRotatef(change, 0, 1, 0);
    glRotatef(change * 0.25f, 1, 0, 0);
    drawCube();
    glPopMatrix();

}


void appRender(int width, int height)
{
    prepareFrame(width, height);
    drawModels();
}


static void prepareFrame(int width, int height)
{
    glViewport(0, 0, width, height);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 0.5f, 150);
    glMatrixMode(GL_MODELVIEW);

    // Setup lighting model.
	GLfloat light_model_ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_direction[] = {0.0f, 0.0f, 10.0f, 0.0f};
	GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_model_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLoadIdentity();
}

static void gluPerspective(GLfloat fovy, GLfloat aspect,
			   GLfloat zNear, GLfloat zFar)
{
    GLfloat xmin, xmax, ymin, ymax;

    ymax = zNear * (GLfloat) tan(fovy * PI / 360);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustumx((GLfixed) (xmin * 65536), (GLfixed) (xmax * 65536),
	       (GLfixed) (ymin * 65536), (GLfixed) (ymax * 65536),
	       (GLfixed) (zNear * 65536), (GLfixed) (zFar * 65536));
}
