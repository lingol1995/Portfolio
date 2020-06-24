#ifndef SCENE3D_H
#define SCENE3D_H

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Input.h"
#include "Camera.h"
#include "SOIL.h"
#include "Scenery.h"
#include "Model.h"
#include "Vec3.h"
#include "TokenStream.h"
#include "Inside.h"
#include "Objects.h"
#include <iostream>
#include "Shadows.h"

#define COLOUR_DEPTH 16	//Colour depth

enum state { outside, inhouse };
enum camerastate {first, second};

class Scene3D
{
public:
	void Init(HWND*, Input*);	//initialse function
	void DrawScene(float);	// render scene
	void Resize();

protected:
	bool CreatePixelFormat(HDC);
	void ResizeGLWindow(int, int);	//width and height
	void InitializeOpenGL(int, int); // width and height
	void HandleInput(float dt);
	
	//vars
	HWND* hwnd;
	Input* input;
	RECT screenRect;
	HDC	hdc;
	HGLRC hrc;			//hardware RENDERING CONTEXT
	int s_wdith, s_height;
	float move;

	Camera cam;
	int differenceX, differenceZ;
	int current;
	Scenery scenery;
	float u, v;
	int d;
	Inside inside;
	void Painting();
	GLuint wallList;
	GLuint myTexture, goo, painting;
	GLuint secondTexture;
	Vec3 Conveyor1;
	Vec3 Conveyor2;
	void house();
	GLuint Dlist;
	
	Objects object;

	void secondCamera();

	camerastate cam_state;
	Shadows shadow;

};

#endif