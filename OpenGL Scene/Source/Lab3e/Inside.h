#ifndef INSIDE_H
#define INSIDE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include <math.h>
#include "Scenery.h"
#include "Objects.h"
#include "Model.h"


enum TIME {past, present};

class Inside{
public:
	Inside();
	~Inside();

float dt;
	void InitInside();
	void Table();
	void InsideTextures();
	void Mirror(float dt);
	void EndMirror();
	void DrawBox();

	GLint wallpaper, floor, shadow, wood, metal, newwall, sofa, goo;
	void DrawPlate();
	float angle, x, y;
	GLfloat u, v, d;
	float interval;
	int segments;
	int time; 
	Scenery tex;
	Objects items;
	Model teapot;
	Objects flies;

};



#endif 