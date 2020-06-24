#ifndef CAMERA_H
#define CAMERA_H

//#include "Scene3D.h"
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include "Vec3.h"
#include <gl/gl.h>
#include <gl/glu.h>

class Camera
{
private: 
		float parts[9];
public:
		Camera();
		~Camera();
		void positions(float x, float y, float z, float a, float b, float c, float d, float e, float f);
		void CameraUpdate();
		
		float Yaw, Pitch, Roll;

		void SetPosition(float x, float y, float z);
		float GetPositionX();
		float GetPositionY();
		float GetPositionZ();

		void SetLookAt(float x, float y, float z);
		float GetLookAtX();
		float GetLookAtY();
		float GetLookAtZ();
		
		void SetUp(float x, float y, float z);
		float GetUpX();
		float GetUpY();
		float GetUpZ();

		void SetYPR(float x, float y, float z);

		Vec3 GetRight() { return right;}
		Vec3 GetUp() { return up;}
		Vec3 GetForward() { return forward;}
		
		Vec3 position;
		Vec3 forward;
		Vec3 up, right;
		Vec3 lookat;
		Vec3 YPR;

};


#endif