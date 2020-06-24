#include "Objects.h"


Objects::Objects()
{

}

////////////////////INITIALISE OBJECTS///////////////////////
void Objects::InitObjects()
{
	chair.Load("Models/chair.obj", "wood.jpg");
	
	 
	speed = 15; 
	anglerot =90;

	goo = SOIL_load_OGL_texture
	(
		"Blackgoo.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	wood = SOIL_load_OGL_texture
	(
		"wood.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

////////////////////EXTERNALLY LOADED IN MODEL (CHAIR)/////////////////////////
void Objects::Chair()
{		
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0, -1.5, 0.0);
	glScalef(0.03, 0.026, 0.03);
	glRotatef(180, 0, 1, 0);
	chair.Render();
	glDisable(GL_TEXTURE_2D);
	
}

////////////////////DRAW THREE CHAIRS UPRIGHT///////////////////
void Objects::drawChairs()
{	
	glPushMatrix();
		Chair();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,0.0, -1.0);
		Chair();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.8,0.0, -1.0);
		glRotatef(180, 0, 1, 0);
		Chair();
	glPopMatrix();
				
}

/////////////////PROCEDURALLY GENERATED SPHERE////////////////////////
void Objects::sphere(int segments, int radius )
{
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	  double x, y, z, angleLat=180/segments, angleLong=360/segments, degToRad=3.141592665885/180 ;

    for(double latitude =0; latitude <=180; latitude+=angleLat)			//increase by section (latitude)
    {
		glBegin( GL_QUAD_STRIP ) ;
        for(double longitude =0 ; longitude <=360 ; longitude+=angleLong)		//increase by section (longitude)
        {  
			//Part 1
            x = radius*cos(longitude * degToRad) * sin(latitude * degToRad) ;
            y = radius*cos(latitude * degToRad) ;
            z = radius*sin(longitude * degToRad) * sin(latitude * degToRad) ;
            glNormal3d( x, y, z) ;
            glTexCoord2d(longitude/360, latitude/180);
            glVertex3d( x, y, z ) ;


            //Part 2
            x = radius*cos(longitude * degToRad) * sin( (latitude + angleLat)* degToRad) ;
            y =radius*cos( (latitude + angleLat) * degToRad ) ;
            z = radius*sin(longitude * degToRad) * sin((latitude + angleLat) * degToRad) ;
            glNormal3d( x, y, z ) ;
            glTexCoord2d(longitude/360, (latitude + angleLat-1)/(180)); 
            glVertex3d( x, y, z ) ;


            //Part 3
            x = radius*cos((longitude + angleLong) * degToRad) * sin((latitude) * degToRad) ;
            y = radius*cos((latitude) * degToRad ) ;
            z = radius*sin((longitude + angleLong) * degToRad) * sin((latitude) * degToRad) ;
            glNormal3d( x, y, z ) ;
           glTexCoord2d((longitude + angleLong)/360 ,(latitude)/180);
             glVertex3d( x, y, z ) ;


            //Part 4
            x = radius*cos((longitude + angleLong) * degToRad) * sin((latitude + angleLat)* degToRad) ;
            y = radius*cos((latitude + angleLat)* degToRad ) ;
            z = radius*sin((longitude + angleLong)* degToRad) * sin((latitude + angleLat)* degToRad) ;
            glNormal3d( x, y, z ) ;
            glTexCoord2d((longitude + angleLong)/360, (latitude + angleLat)/(180));
             glVertex3d( x, y, z ) ;
		}
        glEnd() ;

    }
	
}

////////////////DRAW FLIES/SPIRITS USING PROCEDURALLY ANIMATED GENERATED SPHERES///////////////////
void Objects::DrawFlies(float dt)
{
		
	glEnable(GL_TEXTURE_2D);

	rotation += (speed*3) * dt;
	rotation2 += (speed*4) * dt;
	rotation3 += (speed*5) *dt;

		glTranslatef(0.0f, 1.0f, -1.0f);
		glScalef(0.03f, 0.03f, 0.03f);
		glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	sphere(25, 3);
	glPopMatrix();
	
glBindTexture(GL_TEXTURE_2D, goo);
	sphere(25, 2);

glPushMatrix();
	
	//render fly
		glRotatef(rotation*2.0,0,0,1);	//rotate round z
		glTranslatef(3,0,0);			//moved out
		sphere(25, 1);					//sphere, 25 segments, radius 1
glPopMatrix();//GO BACK TO SUN

glPushMatrix(); // REMEMBER WHERE WE ARE
	// render fly 2
	glRotatef(rotation2*2.0,0,0,1);
	glTranslatef(3.5,0,0);
	sphere(25, 1);
   glPushMatrix(); // REMEMBER WHERE WE ARE
		// Render a fly around second fly
		glRotatef((rotation2*2.0),0,1,0);
		glTranslatef(4.5,0,0);
		sphere(25, 1);
	glPopMatrix();
glPopMatrix();//Return to white sphere

glPushMatrix();
	//render next fly
		glRotatef((rotation2),0,1,0);
		glTranslatef(5.0f,-1,0);
		sphere(25, 1);
	glPushMatrix();
		//render next fly
		glRotatef((rotation2*2.0),0,1,0);
		glTranslatef(4.5,0,0);
		sphere(25, 1);
	glPopMatrix();

	glPushMatrix();
		//render next fly
		glRotatef((rotation3*2.0),0,1,0);
		glTranslatef(4.0f,3.0f,2.0f);		//further out up and along
		sphere(25, 1);

		glPushMatrix();
			glRotatef((rotation3*2.0),0,1,0);	//render last fly
			glTranslatef(4.0f,0.0f,2.0f);
			sphere(25, 1);

		glPopMatrix();
	glPopMatrix();	
glPopMatrix();

glDisable(GL_TEXTURE_2D);
}