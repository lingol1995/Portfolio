#include "Inside.h"


extern float vert[] = { 0.0, 0.0, 0.0,//0
						0.0, 0.0, 1.0,//1
						1.0, 0.0, 1.0,//2
						1.0, 0.0, 0.0 //3
						};

//////////////////NORMAL ARRAYS//////////////////
extern float nor[] = { 
					0.0, 0.0, -1.0,//0
				   0.0, 0.0, -1.0,//1
				   0.0, 0.0, -1.0,//2
				   0.0, 0.0, -1.0,//3
				   
				   1.0, 0.0, 0.0,//4
				   1.0, 0.0, 0.0,//5
				   1.0, 0.0, 0.0,//6
				   1.0, 0.0, 0.0,//7
				   -1.0, 0.0, 0.0,//8
				   -1.0, 0.0, 0.0,//9
				   -1.0, 0.0, 0.0,//10
				   -1.0, 0.0, 0.0,//11
				   0.0, 1.0, 0.0,//12
				   0.0, 1.0, 0.0,//13
				   0.0, 1.0, 0.0,//14
				   0.0, 1.0, 0.0,//15
				   0.0, -1.0, 0.0,//16
				   0.0, -1.0, 0.0,//17
				   0.0, -1.0, 0.0,//18
				   0.0, -1.0, 0.0,//19
				  };

////////////////////TEXTURE ARRAYS //////////////////////
extern float texco[]= {
							0.0, 0.0, //0
						   0.0, 1.0, //1
						   1.0, 1.0, //2	
						   1.0, 0.0, //3
						   0.0, 0.0, //4
						   0.0, 1.0, //5
						   1.0, 1.0, //6	
						   1.0, 0.0, //7
						  0.0, 0.0, //8
						   0.0, 1.0, //9
						   1.0, 1.0, //10	
						   1.0, 0.0, //11
						   0.0, 0.0, //12
						   0.0, 1.0, //13
						   1.0, 1.0, //14	
						   1.0, 0.0, //15
						   0.0, 0.0, //16
						   0.0, 1.0, //17
						   1.0, 1.0, //18	
						   1.0, 0.0, //19
						};

Inside::Inside()
{

}

Inside::~Inside()
{

}
////////////////INITIALISE VALUES///////////////////////
void Inside::InitInside()
{
	time = present;
	angle = 1;
	segments = 12;
	interval = (2*3.141592)/segments;
	x, y = 0;
	u = (cos(angle)/0.5) +0.5;
	v = (sin(angle)/0.5) +0.5;
	InsideTextures();
}
/////////////////DRAW TABLE USING QUADS///////////////////////
void Inside::Table()
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glNormalPointer(GL_FLOAT, 0, nor);
	glTexCoordPointer(2,GL_FLOAT, 0, texco);

	glTranslatef(-0.5f, -1.5f, 5.0f);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wood);
	glBegin(GL_QUADS);
	glArrayElement(16);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glArrayElement(17);
	glVertex3f(0.5f, 0.5f, -1.5f);
	glArrayElement(18);
	glVertex3f(0.0f, 0.5f, -1.5f);
	glArrayElement(19);
	glVertex3f(0.0f, 0.5f, 0.5f);

//legs
	glArrayElement(0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glArrayElement(1);
	glVertex3f(0.4f, 0.5f, 0.5f);
	glArrayElement(2);
	glVertex3f(0.4f, 0.0f, 0.5f);
	glArrayElement(3);
	glVertex3f(0.5f, 0.0f, 0.5f);

	glArrayElement(0);
	glVertex3f(0.1f, 0.5f, 0.5f);
	glArrayElement(1);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glArrayElement(2);
	glVertex3f(0.0f, 0.0f, 0.5f);
	glArrayElement(3);
	glVertex3f(0.1f, 0.0f, 0.5f);

	glArrayElement(0);
	glVertex3f(0.5f, 0.5f, -1.5f);
	glArrayElement(1);
	glVertex3f(0.4f, 0.5f, -1.5f);
	glArrayElement(2);
	glVertex3f(0.4f, 0.0f, -1.5f);
	glArrayElement(3);
	glVertex3f(0.5f, 0.0f, -1.5f);

	glArrayElement(0);
	glVertex3f(0.1f, 0.5f, -1.5f);
	glArrayElement(1);
	glVertex3f(0.0f, 0.5f, -1.5f);
	glArrayElement(2);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glArrayElement(3);
	glVertex3f(0.1f, 0.0f, -1.5f);
	glEnd();
	glPopMatrix();
	//shadow

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, shadow);
	glBegin(GL_QUADS);
		glArrayElement(16);
		glVertex3f(0.5f, 0.0f, 0.5f);
		glArrayElement(17);
		glVertex3f(0.5f, 0.0f, -1.5f);
		glArrayElement(18);
		glVertex3f(0.0f, 0.0f, -1.5f);
		glArrayElement(19);
		glVertex3f(0.0f, 0.0f, 0.5f);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
glPopMatrix();

glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

/////////////////LOAD IN TEXTURES AND MODEL///////////////////////
void Inside::InsideTextures()
{
	wallpaper = tex.LoadTexture("wallpaper.jpg");
	floor =  tex.LoadTexture("floor.jpg");
	shadow = tex.LoadTexture("imposter.png");
	wood = tex.LoadTexture("wood.jpg");
	metal = tex.LoadTexture("Metal.png");
	newwall = tex.LoadTexture("newwall.jpg");
	goo = tex.LoadTexture("Blackgoo.jpg");

	teapot.Load("Models/teapot.obj", "metal.png");
}
//////////////DRAWING MIRROR///////////////////////////////////
void Inside::Mirror(float dt)
{
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);//Disable writing to the frame buffer

	glEnable(GL_STENCIL_TEST);		//create our stencil before rendering the scene
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
			glVertex3f(0.8f, 1.0f, 0.5f);
			glVertex3f(-0.8f, 1.0f, 0.5f);
			glVertex3f(-0.8f, -1.5f, 0.5f);
			glVertex3f(0.8f, -1.5f, 0.5f);
			
	glEnd();


	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //Turn on rendering to frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);	//Only pass stencil test if value is equal to 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	
glPushMatrix();
	glScalef(1.0, 1.0, -1.0);  //Flip
	glTranslatef(0, 0, 1);	   //Translate the object into the drawing plane Because object is flipped this moves it 
		
		
		//glRotatef(180, 0, 1, 0);  //Rotate object
  glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glScalef(4.0f, 3.0f, 12.0f);
			glDisable(GL_DEPTH_TEST);
			switch (time){
			case present:	glBindTexture(GL_TEXTURE_2D, newwall); break;
			case past:		glBindTexture(GL_TEXTURE_2D, wallpaper);  break;
			}
		DrawBox();
	glPopMatrix();
		
	glPushMatrix();
		Table();
	glPopMatrix();
  glPopMatrix();
}

//////////////DRAWING ROOM WALLS, FLOOR AND CEILING USING VERTEX ARRAYS/////////////////
void Inside::DrawBox()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glScalef(4.0f, 3.0f, 12.0f);
		glDisable(GL_DEPTH_TEST);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glNormalPointer(GL_FLOAT, 0, nor);
	glTexCoordPointer(2,GL_FLOAT, 0, texco);

	glBegin(GL_QUADS);
// front face (RED)

glArrayElement(0);
glVertex3f(-0.5f, 0.5f, 0.5f);
glArrayElement(1);
glVertex3f(-0.5f, -0.5f, 0.5f);
glArrayElement(2);
glVertex3f(0.5f, -0.5f, 0.5f);
glArrayElement(3);
glVertex3f(0.5f, 0.5f, 0.5f);

// right face (GREEN)

glArrayElement(4);
glVertex3f(0.5f, 0.5f, 0.5f);
glArrayElement(5);
glVertex3f(0.5f, -0.5f, 0.5f);
glArrayElement(6);
glVertex3f(0.5f, -0.5f, -0.5f);
glArrayElement(7);
glVertex3f(0.5f, 0.5f, -0.5f);

//left face (WHITE)
glArrayElement(8);
glVertex3f(-0.5f, 0.5f, 0.5f);
glArrayElement(9);
glVertex3f(-0.5f, -0.5f, 0.5f);
glArrayElement(10);
glVertex3f(-0.5f, -0.5f, -0.5f);
glArrayElement(11);
glVertex3f(-0.5f, 0.5f, -0.5f);

//top face 
glArrayElement(12);
glVertex3f(-0.5f, 0.5f, -0.5f);
glArrayElement(13);
glVertex3f(0.5f, 0.5f, -0.5f);
glArrayElement(14);
glVertex3f(0.5f, 0.5f, 0.5f);
glArrayElement(15);
glVertex3f(-0.5f, 0.5f, 0.5f);



//back face (BURGUNDY)

	glColor3f(0.5f, 0.1f, 0.3f);
	glArrayElement(0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glArrayElement(1);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glArrayElement(2);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glArrayElement(3);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();//end drawing
	
	glBindTexture(GL_TEXTURE_2D, floor);
	
	// bottom face (BLUE)
	glBegin(GL_QUADS);
glArrayElement(16);
glVertex3f(0.5f, -0.5f, 0.5f);
glArrayElement(17);
glVertex3f(0.5f, -0.5f, -0.5f);
glArrayElement(18);
glVertex3f(-0.5f, -0.5f, -0.5f);
glArrayElement(19);
glVertex3f(-0.5f, -0.5f, 0.5f);
glEnd();

	glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
glPopMatrix();
}

/////////PROCEDURALLY GENERATED DISCS (PLATES)//////////////
void Inside::DrawPlate()		
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallpaper);
	glTranslatef(-0.1f, -0.8f, 0.0f);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(75, 1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	
	for(int loop=0; loop<segments+1; loop++)
	{
		glNormal3f(  0.0f,  0.0f, 1.0f);

		x = cos(angle);
		y = sin(angle);

		glTexCoord2f(u,v);
		glVertex3f(x, y, 0);
		angle += interval;

	}

	glEnd();
	glPopMatrix();

	
}

//////////AFTER EXTERNAL OBJECTS REFLECTED, FINISH MIRROR///////////
void Inside::EndMirror()
{
	glPushMatrix();
		items.drawChairs();
	glPopMatrix();
	glPopMatrix();
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
		
			glBegin(GL_QUADS);
			glColor4f(0.8f, 0.8f, 1.0f, 0.3f);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.8f, 1.0f, 0.5f);
			glVertex3f(-0.8f, 1.0f, 0.5f);
			glVertex3f(-0.8f, -1.5f, 0.5f);
			glVertex3f(0.8f, -1.5f, 0.5f);
		
			glEnd();
			
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		
glPushMatrix();
	glTranslatef(0, 0, 1);
	Table();
glPopMatrix();
}