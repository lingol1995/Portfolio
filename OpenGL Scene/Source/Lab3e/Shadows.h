#ifndef SHADOWS_H
#define SHADOWS_H

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vec3.h"
#include "Inside.h"
#include "Objects.h"

class Shadows
{
	public:
	void generateShadowMatrix(float matrix[16], float light_pos[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);
	void drawShadowMatrixScene();

	float shadowMatrix[16]; 

	Inside indoors;
	Objects drawObject;
};


#endif