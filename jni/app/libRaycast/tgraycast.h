#ifndef _TGRAYCAST_h_
#define _TGRAYCAST_h_

#include "Vector3.h"

namespace TGRaycast {

//定义包围球的结构体
struct boundingsphere {
	Vector3 c; //球心在世界坐标中的位置
	float r;  //半径
};

bool checkRaycasted(int x, int y, int screenW, int screenH, boundingsphere b);


}
#endif
