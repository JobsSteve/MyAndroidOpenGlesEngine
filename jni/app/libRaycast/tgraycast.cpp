#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "tgraycast.h"


#define LOG_TAG "TGRaycast.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


using namespace TGRaycast;

//boundingsphere b={Vector3(4), 1.5}; //定义一个包围球,半径为1.4

//定义射线结构体
struct Ray
{
	Vector3 pos; //射线起始位置
	Vector3 dir; //射线方向
} PickingRay; // 定义一个射线


//屏幕坐标到投影后坐标的转换
Vector3 screen2viewport(int x, int y, int w, int h)
{
	float _x = 2.0*x/w -1;
	float _y = 1-2.0*y/h;
    return Vector3(_x,_y, 1.0);
}


//投影坐标到相机坐标的转换
Vector3 viewport2viewspace(Vector3 vp)
{
	GLfloat m[16];
	glGetFloatv(GL_PROJECTION_MATRIX, m);

	float _x = vp[0]/m[0];
	float _y = vp[1]/m[5];

	return Vector3(_x,_y, -1.0);
}

//生成拾取射线
Ray computeRay(Vector3 s, Vector3 e)
{
	Ray ray;
	ray.dir = Vector3(e[0]-s[0],e[1]-s[1], e[2]-s[2]).normalized();
	ray.pos = Vector3(s[0],s[1],s[2]);
	return ray;
}

//将拾取射线从相机坐标转换到世界坐标
void ray2world(Ray *ray)
{
	// 这里最后一列为(0,0,5,1)是因为相机的位置在世界坐标的(0,0,5)这个地方
//	float m[16] =
//	{
//		1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 1, 5,
//		0, 0, 0, 1
//	};

//	GMatrix M(4,4,m);
//
//	ray->pos = M * ray->pos; //矩阵乘以点 转换射线起始坐标到世界坐标
//	ray->dir = M * ray->dir; //矩阵乘以向量  转换射线方向到世界坐标

}


//判断是否相交
bool intersect(Ray r, boundingsphere b)
{
	float A = Vector3::dotProduct(r.dir, r.dir);
	float B = 2*Vector3::dotProduct(r.dir, (r.pos - b.c));
	float C = Vector3::dotProduct((r.pos - b.c), (r.pos-b.c)) - Vector3::dotProduct(b.r, b.r);

	//根号内部分为0,那么肯定无实数解,说明射线和球不相交
	if(B*B-4*C <0)
		return false;

	float x1 = (-B + sqrt(B*B-4*C) )/ (2.0);
	float x2 = (-B - sqrt(B*B-4*C) )/ (2.0);

	//如果有解,且有一个大于0,说明射线和球相交,小于0的话说明射线的反方向和球相交
  	if(x1 >= 0 || x2 >=0)
		return true;

	return false;
}


void render()
{
//	GLfloat diff[]={1.0,.0,.0,0.7};
//	GLfloat amb[]={1.0,.0,.0,0.6};
//	GLfloat sp[]={1.0,1.0,1.0,0.5};
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
//	glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, sp);
//	glMateriali(GL_FRONT, GL_SHININESS, 64);
//
//	static float a = 0.0;
//	static float r = 0.0;
//
//	//将物体和包围球一起移动
//	glTranslatef(r*cosf(a), r*sinf(a), -8.0);
//	b.c.Set(r*cosf(a), r*sinf(a), -8.0,1.0);
//   	glutSolidTeapot(1.0);
//
//	GLfloat d[]={1.0,1.0,0.0,0.3};
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
//
//
//	//渲染包围球
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glutSolidSphere(b.r,20,20);
//	glDisable(GL_BLEND);

}

bool checkRaycasted(int x, int y, int screenW, int screenH, boundingsphere b)
{
		//屏幕坐标转换为投影后坐标,保存在v1中
		Vector3 v1 = screen2viewport(x,y, screenW, screenH);

		//将投影坐标v1转换为相机坐标,保存在v2中
		Vector3 v2 =viewport2viewspace(v1);

		//利用相机坐标生成拾取射线
		PickingRay = computeRay(Vector3(.0,.0,.0), v2);

		//将射线转换到世界坐标
		ray2world(&PickingRay);

		//判断是否和包围球相交
		bool is =intersect(PickingRay, b);

		LOGI("Ray pos(%f,%f,%f), dir(%f, %f, %f), isCasted=%d", PickingRay.pos.x, PickingRay.pos.y, PickingRay.pos.z, PickingRay.dir.x, PickingRay.dir.y, PickingRay.dir.z, is);

		return is;
}

