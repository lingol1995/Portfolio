#include "Scene3D.h"

extern float verts[] = {-1.0, 1.0, 1.0,//Vertex #1
				-1.0, -1.0, 1.0,// Vertex #1
				1.0,  -1.0, 1.0,// Vertex #2
				1.0,  1.0, 1.0,// Vertex #3
				};

extern float norms[] = { 0.0, 0.0, 1.0,//0
				   0.0, 0.0, 1.0,//1
				   0.0, 0.0, 1.0,//2
				   0.0, 0.0, 1.0,//3
				  };

extern float texcoords[]= {0.0, 0.0, //0
						   0.0, 1.0, //1
						   1.0, 1.0, //2	
						   1.0, 0.0, //3
						   };


bool Scene3D::CreatePixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR pfd = {0}; 
    int pixelformat; 
 
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Set the size of the structure
    pfd.nVersion = 1;							// Always set this to 1
	// Pass in the appropriate OpenGL flags
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;			// standard mask (this is ignored anyway)
    pfd.iPixelType = PFD_TYPE_RGBA;				// RGB and Alpha pixel type
    pfd.cColorBits = COLOUR_DEPTH;				// Here we use our #define for the color bits
    pfd.cDepthBits = COLOUR_DEPTH;				// Ignored for RBA
    pfd.cAccumBits = 0;							// nothing for accumulation
    //pfd.cStencilBits = 0;						// nothing for stencil
	pfd.cStencilBits = COLOUR_DEPTH;

	//Gets a best match on the pixel format as passed in from device
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == false ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
	//sets the pixel format if its ok. 
    if (SetPixelFormat(hdc, pixelformat, &pfd) == false) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
    return true;
}

void Scene3D::ResizeGLWindow(int width, int height)// Initialize The GL Window
{
	if (height==0)// Prevent A Divide By Zero error
	{
		height=1;// Make the Height Equal One
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//calculate aspect ratio
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 1 ,150.0f);

	glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
	glLoadIdentity();// Reset The Modelview Matrix
}

void Scene3D::InitializeOpenGL(int width, int height) 
{  
    hdc = GetDC(*hwnd);//  sets  global HDC

    if (!CreatePixelFormat(hdc))//  sets  pixel format
        PostQuitMessage (0);


    hrc = wglCreateContext(hdc);	//  creates  rendering context from  hdc
    wglMakeCurrent(hdc, hrc);		//	Use this HRC.

	ResizeGLWindow(width, height);	// Setup the Screen
}



void Scene3D::Init(HWND* wnd, Input* in)
{
	hwnd = wnd;
	input = in;

	GetClientRect(*hwnd, &screenRect);	//get rect into our handy global rect
	InitializeOpenGL(screenRect.right, screenRect.bottom); // initialise openGL

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_LIGHTING);
	cam_state = second;
	move = 0;
//	speed = 50;
	
	//u = (cos(angle)/2) +0.5;
	//v = (sin(angle)/2) +0.5;
	Conveyor1.set(0,0,0);
	Conveyor2.set(0.01,0.02,0);
	Dlist = glGenLists(1);
	glClearStencil(0);

	cam.positions(0 ,0 ,6, 0 ,0 , 0, 0, 1, 0);
	//Also, do any other setting variables here for your app if you wish.

	glEnable(GL_LIGHTING);
	scenery.initScenery();
	scenery.Textures();
	inside.InitInside();
	object.InitObjects();

	current = outside;
	////////////POINT LIGHT(WHITE LIGHT)/////////////////////
	GLfloat Light_Ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light_Diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light_Position[]= {0.0f, 1.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glEnable(GL_LIGHT0);
	///////////DIRECTIONAL LIGHT (RED LIGHT)////////////////
	GLfloat Light_Diff[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat Light_Pos[]= {0.0f, -1.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  Light_Diff);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient);
	glEnable(GL_LIGHT1);
	
	//////////DIRECTIONAL LIGHT (WHITE LIGHT)/////////////////////////
	GLfloat Light_Diff2[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light_Pos2[]= {1.0f, -1.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  Light_Diff2);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Pos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);
	glEnable(GL_LIGHT2);
	
	GLfloat spot_Direction[]= {0.0f, -1.0f, 0.0f};

	glLightfv(GL_LIGHT3, GL_AMBIENT,  Light_Ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  Light_Diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 50.0);
	glEnable(GL_LIGHT3);

	myTexture = SOIL_load_OGL_texture
	(
		"water.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	secondTexture = SOIL_load_OGL_texture
	(
		"house.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	goo = SOIL_load_OGL_texture
	(
		"Blackgoo.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	painting = SOIL_load_OGL_texture
	(
		"painting.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

void Scene3D::DrawScene(float dt) 
{
	HandleInput(dt);
	int i=0;

	if(cam_state == second)
	secondCamera();			//fixed camera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

	cam.CameraUpdate();

	scenery.SkyBox(cam);
	
	switch (current)
	{
	case outside :  
				scenery.DrawGround();
				house();
				object.sphere(25,4);
				
				
				break;
	case inhouse : 
					cam_state = first;
					switch(inside.time)
					{
						case present: glBindTexture(GL_TEXTURE_2D, inside.wallpaper);
									  glDisable(GL_LIGHT2);
									  glEnable(GL_LIGHT1);	break;
						case past:    glBindTexture(GL_TEXTURE_2D, inside.newwall); 
								      glEnable(GL_LIGHT2);
								      glDisable(GL_LIGHT1);break;
					}

					inside.DrawBox();
					Painting();
					scenery.window();
					glPushMatrix();
	
					switch(inside.time)
					{
						case present:	glTranslatef(-1.8,-1.5, 0);
										glRotatef(180, 0, 1, 0);
										glRotatef(270, 0, 0, 1);
										break;

						case past:		glTranslatef(-0.8,0.0, 0.0);
										glRotatef(180, 0, 1, 0);
							break;
					};

				object.Chair();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -1.0f);
				inside.DrawPlate();
			glPopMatrix();
			glPushMatrix();
				inside.DrawPlate();
				shadow.drawShadowMatrixScene();
				
				glTranslatef(-0.2f, -0.9f, 0.0f);
				glScalef(0.01, 0.01, 0.01);
				inside.teapot.Render();
			
			glPopMatrix();
			
			glPushMatrix();
				if(inside.time == present) object.DrawFlies(dt);
			glPopMatrix();
			
				object.drawChairs();
			
			glTranslatef(0.0f, 0.0f, -6.0f);
		glPushMatrix();
				inside.Mirror(dt);
				glPushMatrix();
				switch(inside.time)
				{
					case present: glBindTexture(GL_TEXTURE_2D, inside.wallpaper);
									glDisable(GL_LIGHT2);
									glDisable(GL_LIGHT0);
									glEnable(GL_LIGHT1);	break;
					case past: glBindTexture(GL_TEXTURE_2D, inside.newwall); 
								glEnable(GL_LIGHT2);
								glDisable(GL_LIGHT1);
								object.DrawFlies(dt);break;
				}
		glPopMatrix();
			inside.EndMirror();
		glPopMatrix();
	glPopMatrix();
	}
	

	SwapBuffers(hdc);// Swap the frame buffers.
}		

void Scene3D::Resize()
{
	if(hwnd == NULL)
		return;

	GetClientRect(*hwnd, &screenRect);	
	ResizeGLWindow(screenRect.right, screenRect.bottom);	
}
//////////////////////////////INPUT/////////////////////////////
void Scene3D::HandleInput(float dt)
{
	int currMouseX = input->getMouseX();
		int distanceX = currMouseX - differenceX;
	
		if(input->isKeyDown(0x58))  // if x is pressed
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//wireframe mode
			input->SetKeyUp(0x58);  //force un-pressing of x
			
		}
		
		if(input->isKeyDown(0x59))  // if y is pressed
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//return objects to normal
			glDisable(GL_LIGHT2);
		}


	if(input->isKeyDown(0x56))  // if v is pressed
		{
			current = inhouse;
			glEnable(GL_LIGHT0);
		}

	if(cam_state == first)
	{
		if(input->isKeyDown(VK_RIGHT))  // if right arrow key is pressed
		{
			move = 0.1;

			Vec3 right_vec = cam.GetRight();


			cam.SetPosition(cam.GetPositionX() + (move*right_vec.getX()), cam.GetPositionY() + (move*right_vec.getY()), cam.GetPositionZ() + (move*right_vec.getZ()));
			
			input->SetKeyUp(VK_RIGHT);  //force un-pressing of right arrow key
		}
	
	else if(input->isKeyDown(VK_LEFT))  // if w is pressed
		{
			move = -0.1;

			Vec3 right_vec = cam.GetRight();


			cam.SetPosition(cam.GetPositionX() + (move*right_vec.getX()), cam.GetPositionY() + (move*right_vec.getY()), cam.GetPositionZ() + (move*right_vec.getZ()));
			
			input->SetKeyUp(VK_LEFT);  //force un-pressing of right arrow key
		}

	else if(input->isKeyDown(VK_DOWN))  // if down arrow key is pressed
		{
			move =- 0.1;

			Vec3 up_vec = cam.GetForward();


			cam.SetPosition(cam.GetPositionX() + (move*up_vec.getX()), cam.GetPositionY() + (move*up_vec.getY()), cam.GetPositionZ() + (move*up_vec.getZ()));
			
			input->SetKeyUp(VK_RIGHT);  //force un-pressing of right arrow key
		}
	
	else if(input->isKeyDown(VK_UP))  // if up is pressed
		{
			move = 0.1;

			Vec3 up_vec = cam.GetForward();


			cam.SetPosition(cam.GetPositionX() + (move*up_vec.getX()), cam.GetPositionY() + (move*up_vec.getY()), cam.GetPositionZ() + (move*up_vec.getZ()));
			
			input->SetKeyUp(VK_RIGHT);  //force un-pressing of right arrow key
		}

	else if(input->isKeyDown(0x53))  // if s is pressed
		{
			move = 0;
			move ++;
			cam.SetYPR(cam.YPR.getX(), cam.YPR.getY() + move, cam.YPR.getZ());
			
			input->SetKeyUp(0x53);  //force un-pressing of s
		}
	
	else if(input->isKeyDown(0x57))  // if w is pressed
		{
			switch(inside.time){
			case present: inside.time = past; break;
			case past: inside.time = present; break;
			}

			cam_state = second;
			input->SetKeyUp(0x57);  //force un-pressing of w
		}

		if( input->isKeyDown(VK_SPACE))		//PRESS SPACE TO MOVE CAMERA BY MOUSE
		{
			int currMouseX = input->getMouseX();
			int distanceX = currMouseX - differenceX;
			if(distanceX > 0)
			{
				cam.SetYPR(cam.YPR.getX() + distanceX, cam.YPR.getY(), cam.YPR.getZ());
			}

		else if (distanceX < 0)
		{
			cam.SetYPR(cam.YPR.getX() + distanceX, cam.YPR.getY(), cam.YPR.getZ());
		}
	
		differenceX = currMouseX;
	}
	
	
	
	if( input->isKeyDown(VK_BACK))
	{	
			int currMouseZ = input->getMouseY();
			int distanceZ = currMouseZ - differenceZ;
			if(distanceZ > 0)
			{
				cam.SetYPR(cam.YPR.getX() , cam.YPR.getY()- distanceZ, cam.YPR.getZ());
			}
			
			else if (distanceZ < 0)
			{
				cam.SetYPR(cam.YPR.getX() , cam.YPR.getY()- distanceZ, cam.YPR.getZ());
			}
			differenceZ = currMouseZ;

		}
	}
}

/////////////////////////////FRAME WITH TRANSPARENCY AND MOVING TEXTURE////////////////////////
void Scene3D::Painting()
{
	glPushMatrix();
	glTranslatef(2.01f, 0.0f, -6.0f);
	glRotatef(90,0, 1,0);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	if(inside.time == past)
	{
		glBindTexture(GL_TEXTURE_2D, painting);
	}
	

	else if(inside.time==present)
	{
		glBindTexture(GL_TEXTURE_2D, goo);	//tells opengl which texture to use
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
			Conveyor2 = Conveyor2.add(Vec3(0,-0.01,0));
			glTranslatef(Conveyor2.getX(), Conveyor2.getY(), Conveyor2.getZ());
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glBegin(GL_QUADS);
	glColor4f(0.0, 0.3, 0.4,0.3);
		glNormal3f(  0.0f,  0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f,  1.0f, 0.0f);		
		glNormal3f( 0.0f,  0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( -3.0f, -1.0f, 0.0f);
		glNormal3f( 0.0f,  0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( -1.0f, -1.0f, 0.0f);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( -1.0f, 1.0f, 0.0f);
		glEnd();
	if(inside.time == past) glPopMatrix();
		glMatrixMode(GL_TEXTURE);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}
/////////////////////////////DRAW HOUSE//////////////////////////////////
void Scene3D::house()
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2,GL_FLOAT, 0, texcoords);

	glTranslatef(0.0f, 2.0f, -6.0f);
	glScalef(3.0f, 3.0f, 3.0f);

	glBindTexture(GL_TEXTURE_2D, secondTexture);
	
	glBegin(GL_QUADS);
	
	
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);

	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}

///////////////////////////FIXED VIEW CAMERA, ONLY MOUSE MOVES IT LEFT AND RIGHT//////////////////////
void Scene3D::secondCamera()
{
	int camX = input->getMouseX();
		int distanceX = camX - differenceX;
		
		if(distanceX > 0)
		{
			cam.SetYPR(cam.YPR.getX() + distanceX, cam.YPR.getY(), cam.YPR.getZ());
		}

		else if (distanceX < 0)
		{
			cam.SetYPR(cam.YPR.getX() + distanceX, cam.YPR.getY(), cam.YPR.getZ());
		}
	

		differenceX = camX;
}


