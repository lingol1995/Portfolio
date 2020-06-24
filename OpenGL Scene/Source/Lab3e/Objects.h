#ifndef OBJECTS_H
#define OBJECTS_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include <math.h>
#include "Scenery.h"
#include "Model.h"

class Objects
{
	public:
	Objects();

	void InitObjects();
	void Chair();
	void drawChairs();
	void sphere(int segments, int radius);
	void DrawFlies(float dt);

	float rotation;
	float rotation2; 
	float rotation3; 
	float speed; 
	float anglerot;

	Model chair;
	Scenery textures;
	GLuint chairtex, goo, wood;




};


#endif