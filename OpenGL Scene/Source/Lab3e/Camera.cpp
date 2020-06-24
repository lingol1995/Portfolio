#include "Camera.h"

Camera::Camera()
{
	SetUp(0,1,0);
	SetYPR(0,0,0);

}

Camera::~Camera()
{

}


void Camera::CameraUpdate()
{
	float cosR, cosP, cosY;	//temp values for sin/cos from 
	float sinR, sinP, sinY;

	///////do stuff

	cosY = cosf(YPR.getX()*3.1415/180);
	cosP = cosf(YPR.getY()*3.1415/180);
	cosR = cosf(YPR.getZ()*3.1415/180);
	sinY = sinf(YPR.getX()*3.1415/180);
	sinP = sinf(YPR.getY()*3.1415/180);
	sinR = sinf(YPR.getZ()*3.1415/180);

	position.getX();
	position.getY();
	position.getZ();

	forward.setX(sinY * cosP);
	forward.setY(sinP);
	forward.setZ(cosP * -cosY);

	up.setX(-cosY * sinR - sinY * sinP * cosR);
	up.setY(cosP * cosR);
	up.setZ(-sinY * sinR - sinP * cosR * -cosY);

	right.setX(forward.getY()*up.getZ() - forward.getZ() *up.getY());
	right.setY(forward.getX()*up.getZ() - forward.getZ() *up.getX());
	right.setZ(forward.getX()*up.getY() - forward.getY() *up.getX());

	gluLookAt(GetPositionX(), GetPositionY(), GetPositionZ(), GetLookAtX(), GetLookAtY(), GetLookAtZ(), GetUpX(), GetUpY(), GetUpZ());
	//gluLookAt(position[0], position[1], position[2], forward[0], forward[1], forward[2], up[0], up[1], up[2]);
}

void Camera::SetPosition(float x, float y, float z)
{
	position.setX(x);
	position.setY(y);
	position.setZ(z);
}

void Camera::SetYPR(float x, float y, float z)
{
	YPR.setX(x);
	YPR.setY(y);
	YPR.setZ(z);
}

void Camera::SetLookAt(float x, float y, float z)
{
	lookat.setX(x);
	lookat.setY(y);
	lookat.setZ(z);
}

float Camera::GetPositionX()
{
	return position.getX();
}

float Camera::GetPositionY()
{
	return position.getY();
}

float Camera::GetPositionZ()
{
	return position.getZ();
}


float Camera::GetLookAtX()
{
 lookat.setX(position.getX() + forward.getX());
	return lookat.getX();
}

float Camera::GetLookAtY()
{	

	lookat.setY(position.getY() + forward.getY());
	return lookat.getY();
}

float Camera::GetLookAtZ()
{
	lookat.setZ(position.getZ() + forward.getZ());
	return lookat.getZ();
}

float Camera::GetUpX()
{
	return up.getX();
}

float Camera::GetUpY()
{
	return up.getY();
}

float Camera::GetUpZ()
{
	return up.getZ();

}

void Camera::SetUp(float x, float y, float z)
{
	up.setX(x);
	up.setY(y);
	up.setZ(z);
	
}

void Camera::positions(float x, float y, float z, float a, float b, float c, float d, float e, float f)
{
	SetPosition(x,y,z);
	SetLookAt(a,b,c);
	SetYPR(d,e,f);
}