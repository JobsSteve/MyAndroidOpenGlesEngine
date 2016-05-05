#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.14159265358979323846
#define CAMERA_SPEED 0.5

extern void InitCamera();
extern void MoveRight();
extern void MoveLeft();
extern void MoveForward();
extern void MoveBackward();
extern void MoveUpward();
extern void MoveDownward();
extern void RotateRight();
extern void RotateLeft();
extern void RotateUp();
extern void RotateDown();

extern float fpXAngle;
extern float fpYAngle;
extern float fpCameraXCoordinate;
extern float fpCameraYCoordinate;
extern float fpCameraZCoordinate;

#endif