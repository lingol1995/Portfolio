#include "Scenery.h"


Scenery::Scenery(void)
{
}


Scenery::~Scenery(void)
{
}


/////////////SKYBOX///////////////////
void Scenery::SkyBox(Camera cam)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();
		glTranslatef(cam.GetPositionX(),cam.GetPositionY(),cam.GetPositionZ());
		glDisable(GL_DEPTH_TEST);
		
		glBindTexture(GL_TEXTURE_2D, skyboxFront);
		glBegin(GL_QUADS);

		glNormal3f(0.0f, 0.0f, 1.0f); 
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.5f, 1.5f, 1.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.5f, 1.5f, 1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.5f, -1.5f, 1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.5f, -1.5f, 1.5f);
		glEnd();

// right face (GREEN)
glBindTexture(GL_TEXTURE_2D, skyboxRight);
glBegin(GL_QUADS);

glNormal3f(1.0f, 0.0f, 0.0f); 
glTexCoord2f(0.0f, 0.0f);
glVertex3f(1.5f, 1.5f, -1.5f);

glTexCoord2f(1.0f, 0.0f);
glVertex3f(1.5f, 1.5f, 1.5f);
glTexCoord2f(1.0f, 1.0f);
glVertex3f(1.5f, -1.5f, 1.5f);
glTexCoord2f(0.0f, 1.0f);
glVertex3f(1.5f, -1.5f, -1.5f);

// bottom face (BLUE)

glNormal3f(0.0f, -1.0f, 0.0f);
glVertex3f(1.5f, -1.5f, 1.5f);
glVertex3f(1.5f, -1.5f, -1.5f);
glVertex3f(-1.5f, -1.5f, -1.5f);
glVertex3f(-1.5f, -1.5f, 1.5f);

//top face (YELLOW)
glNormal3f(0.0f, 1.0f, 0.0f);
glVertex3f(-1.5f, 1.5f, -1.5f);
glVertex3f(1.5f, 1.5f, -1.5f);
glVertex3f(1.5f, 1.5f, 1.5f);
glVertex3f(-1.5f, 1.5f, 1.5f);
glEnd();
//left face (WHITE)

glBindTexture(GL_TEXTURE_2D, skyboxLeft);
glBegin(GL_QUADS);
glNormal3f(-1.0f, 0.0f, 0.0f);
glTexCoord2f(0.0f, 0.0f);
glVertex3f(-1.5f, 1.5f, 1.5f);
glTexCoord2f(1.0f, 0.0f);
glVertex3f(-1.5f, 1.5f, -1.5f);
glTexCoord2f(1.0f, 1.0f);
glVertex3f(-1.5f, -1.5f, -1.5f);
glTexCoord2f(0.0f, 1.0f);
glVertex3f(-1.5f, -1.5f, 1.5f);
glEnd();

//back face (BURGUNDY)
glBindTexture(GL_TEXTURE_2D, skyboxBack);
glBegin(GL_QUADS);

	glNormal3f(  0.0f,  0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.5f, 1.5f, -1.5f);

	glNormal3f(  0.0f,  0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.5f, 1.5f, -1.5f);
		
	glNormal3f(  0.0f,  0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.5f, -1.5f, -1.5f);

	glNormal3f(  0.0f,  0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.5f, -1.5f, -1.5f);
 glEnd();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glEndList();	
}

///////////////////////TEXTURES/////////////////
void Scenery::Textures()
{
	skyboxBack = LoadTexture("negz.jpg");
	skyboxRight = LoadTexture("negx.jpg");
	skyboxLeft = LoadTexture("posx.jpg");
	skyboxFront = LoadTexture("posz.jpg");
	ground = LoadTexture("negy.jpg");
	windows = LoadTexture("crateTrans.png");

}
void Scenery::initScenery()
{
	segments = 20;
	theta = (2*PI) / segments;
	delta = PI / segments;
	x = cos(theta)*sin(delta);
	y = cos(delta);
	z = sin(theta)* sin(delta);
	lat = theta;
	longitude = delta;
	


}
/////////////////////OUTSIDE GROUND/////////////
void Scenery::DrawGround()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.5f, -1.0f, 5.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.5f, -1.0f, -5.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.5f, -1.0f, -5.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.5f, -1.0f, 5.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLuint Scenery::LoadTexture(const char* filename)
{
	GLuint temp;

	temp =  SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO, 
		SOIL_CREATE_NEW_ID, 
		SOIL_FLAG_MIPMAPS | 
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	return temp;
}

void Scenery::window()
{
	glPushMatrix();
		glTranslatef(2.0f, -1.0f, -3.0f);
		glRotatef(90,0, 1,0);
	
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glColor4f(0.2, 0.6, 0.8, 0.2);
		glNormal3f(  0.0f,  0.0f, 1.0f);
			//glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0f,  2.0f, 0.0f);		
		glNormal3f( 0.0f,  0.0f, 1.0f);
			//glTexCoord2f(0.0f, 1.0f);
				glVertex3f( 0.0f, 0.0f, 0.0f);
		glNormal3f( 0.0f,  0.0f, 1.0f);
			//glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 2.0f, 0.0f, 0.0f);
		glNormal3f( 0.0f, 0.0f, 1.0f);
			//glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 2.0f, 2.0f, 0.0f);
				
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			glEnd();

			
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, windows);
		glBegin(GL_QUADS);

		glColor4f(0.5, 0.5, 0.5, 1.0);
		glNormal3f(  0.0f,  0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0f,  2.0f, 0.0f);		
		glNormal3f( 0.0f,  0.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
				glVertex3f( 0.0f, 0.0f, 0.0f);
		glNormal3f( 0.0f,  0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f);
				glVertex3f( 2.0f, 0.0f, 0.0f);
		glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
				glVertex3f( 2.0f, 2.0f, 0.0f);
				
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			glEnd();
		
				glDisable(GL_DEPTH_TEST);
				glEnable(GL_LIGHTING);

		glPopMatrix();
			
}
