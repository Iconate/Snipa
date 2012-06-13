#include <math.h>
#include <windows.h>
#include <iostream>

#include "drawtextures.h"
#include "menu.h"
#include "keyboard.h"

using namespace std;

#define win_width 1024
#define win_height 768


void setOrthographicProjection() {
     
     // switch to projection mode
	 glMatrixMode(GL_PROJECTION);
	 // save previous matrix which contains the 
	 //settings for the perspective projection
	 glPushMatrix();
	 // reset matrix
	 glLoadIdentity();
	 // set a 2D orthographic projection
	 gluOrtho2D(0, win_width, 0, win_height);
	 // invert the y axis, down is positive
	 glScalef(1, -1, 1);
	 // mover the origin from the bottom left corner
	 // to the upper left corner
	 glTranslatef(0, -win_height, 0);
	 glMatrixMode(GL_MODELVIEW);
	 
}

void resetPerspectiveProjection() {
     
     glMatrixMode(GL_PROJECTION);
	 glPopMatrix();
	 glMatrixMode(GL_MODELVIEW);
	
}



void crosshair() {
      glLineWidth (0.5);
      //glColor3f (0.5F, 0.5F, 0.5F);
      float xtmp;
      //glLoadIdentity();
      glPushMatrix();
     // glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
      //glRotatef(yrot,0.0,1.0,0.0);
     // glTranslatef(-xpos - 5,-ypos - 5,-zpos);
  glBegin (GL_LINES);
  for (xtmp = -1.0F; xtmp < 1.0F; xtmp += 0.05)
    {
      glVertex2f (xtmp, -1.0);
      glVertex2f (xtmp, 1.0);
      glVertex2f (-1.0, xtmp);
      glVertex2f (1.0, xtmp);
    };
  glEnd ();
        glPopMatrix();
}
     

void camera () {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void cameraDisplay(void) {
    glEnable( GL_TEXTURE_2D ); //enable 2D texturing

    
    glClearColor (0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();  
    camera();
    
    drawGrass();
    drawSandbags();
    drawWorld();
    
    crosshair();
    
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
	setOrthographicProjection();
	glLoadIdentity();
	glColor3f(0.0f,0.5f,0.5f);
	renderBitmapString(30, 60, (void *)font, "This is a test");
	resetPerspectiveProjection();
	glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();
    
    if (movement)
       moveDirection(direction);
    
	glutSwapBuffers();
	
	

}

/*
void mouseMovement(int x, int y) {
     	if(!warped)
	{
		float diffx = x - 1024/2;
		float diffy = y - 768/2;

		//keep camera from rotating beyond vertically up/down
		if(xrot>=-90 && diffy < 0)
			xrot = xrot + 0.25f*diffy;
		else if(xrot<=90 && diffy > 0)
			xrot = xrot + 0.25f*diffy;

		yrot = yrot + 0.25f*diffx;
		warped = true;
		glutWarpPointer(1024/2, 768/2);
	}
	else
		warped = false;
  glutPostRedisplay();
}


void movePlayer(unsigned char key, int x, int y) {
    if (key=='w') {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos += float(sin(yrotrad));
    zpos -= float(cos(yrotrad));
    //ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s') {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    //ypos += float(sin(xrotrad));
    }

    if (key=='d') {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos += float(cos(yrotrad)) ;
    zpos += float(sin(yrotrad)) ;
    }

    if (key=='a') {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos -= float(cos(yrotrad)) ;
    zpos -= float(sin(yrotrad)) ;
    }

    if (key==27)
    {
    exit(0);
    }
}*/
