#ifndef SCENERY_H
#define SCENERY_H

#include "camera.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include <math.h>

#define PI 3.14159265

class Scenery 
{
public:
	Scenery(void);
	~Scenery(void);

	void initScenery();
	void SkyBox(Camera cam);
	void Textures();
	void DrawGround();
	void window();
	GLint skyboxBack, skyboxRight, skyboxLeft, skyboxFront, ground, windows;
	GLfloat theta, delta;
	GLfloat x, y, z;
	GLfloat lat;
	GLfloat longitude, segments;

	GLuint LoadTexture(const char* filename);
};

#endif

