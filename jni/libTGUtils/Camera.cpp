#include "Camera.h"

#include <stdlib.h>
#include <algorithm>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

using namespace std;

float fpXAngle = 0.0;
float fpYAngle = 0.0;
float fpCameraXCoordinate = 0.0;
float fpCameraYCoordinate = 0.0;
float fpCameraZCoordinate = 0.0;

/*
* 	Function:  InitCamera
* 	--------------------
* 	Rotates and translates the world so the camera effect is enabled
*
*  returns: void
*/
void InitCamera()
{
	glRotatef(-fpYAngle, 1.0, 0.0, 0.0);
	glRotatef(-fpXAngle, 0.0, 1.0, 0.0);
	glTranslatef(-fpCameraXCoordinate, -fpCameraYCoordinate, -fpCameraZCoordinate);
}

/*
* 	Function:  MoveForward
* 	--------------------
* 	Moves the camera forward in it's current direction by one step
*
*  returns: void
*/
void MoveForward()
{

	float fpXRotationInRadians = (fpXAngle / 180 * PI);
	fpCameraXCoordinate += float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
	fpCameraZCoordinate += float(-cos(fpXRotationInRadians)) * CAMERA_SPEED;

/*	float fpXRotationInRadians = (fpXAngle / 180 * PI);
	float fpYRotationInRadians = (fpYAngle / 180 * PI);
	fpCameraXCoordinate += float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
	fpCameraYCoordinate += cos(fpYRotationInRadians) * sin(fpYRotationInRadians) * CAMERA_SPEED;
	fpCameraZCoordinate += float(-cos(fpXRotationInRadians)) * CAMERA_SPEED;*/
}

/*
* 	Function:  MoveBackward
* 	--------------------
* 	Moves the camera backward in it's current direction by one step
*
*  returns: void
*/
void MoveBackward()
{
	float fpXRotationInRadians = (fpXAngle / 180 * PI);
	fpCameraXCoordinate -= float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
	fpCameraZCoordinate -= float(-cos(fpXRotationInRadians)) * CAMERA_SPEED;
}

/*
* 	Function:  MoveRight
* 	--------------------
* 	Moves the camera to the right in it's current direction by one step
*
*  returns: void
*/
void MoveRight()
{
	float fpXRotationInRadians = (fpXAngle / 180 * PI);
	fpCameraXCoordinate += float(cos(fpXRotationInRadians)) * CAMERA_SPEED;
	fpCameraZCoordinate += float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
}

/*
* 	Function:  MoveLeft
* 	--------------------
* 	Moves the camera to the left in it's current direction by one step
*
*  returns: void
*/
void MoveLeft()
{
	float fpXRotationInRadians = (fpXAngle / 180 * PI);
	fpCameraXCoordinate -= float(cos(fpXRotationInRadians)) * CAMERA_SPEED;
	fpCameraZCoordinate -= float(-sin(fpXRotationInRadians)) * CAMERA_SPEED;
}

/*
* 	Function:  MoveUpward
* 	--------------------
* 	Moves the camera upward in it's current direction by one step
*
*  returns: void
*/
void MoveUpward()
{
	fpCameraYCoordinate++;
}

/*
* 	Function:  MoveDownward
* 	--------------------
* 	Moves the camera downward in it's current direction by one step
*
*  returns: void
*/
void MoveDownward()
{
	fpCameraYCoordinate--;
}

/*
* 	Function:  RotateRight
* 	--------------------
* 	Rotates the camera to the right in it's current direction by one degree
*
*  returns: void
*/
void RotateRight()
{
	fpXAngle -= 1.5;
}

/*
* 	Function:  RotateLeft
* 	--------------------
* 	Rotates the camera to the left in it's current direction by one degree
*
*  returns: void
*/
void RotateLeft()
{
	fpXAngle += 1.5;;
}

/*
* 	Function:  RotateUp
* 	--------------------
* 	Rotates the camera up in it's current direction by one degree
*
*  returns: void
*/
void RotateUp()
{
	fpYAngle += 1.5;
}

/*
* 	Function:  RotateDown
* 	--------------------
* 	Rotates the camera down in it's current direction by one degree
*
*  returns: void
*/
void RotateDown()
{
	fpYAngle -= 1.5;
}
