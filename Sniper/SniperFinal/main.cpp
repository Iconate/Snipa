/*Christo Mitov & Nathan Kreuger 
*Snipa 
*Code used from Prof Ebrahim and some online googling resources
*
*/
#include <GL/glut.h>
#include <GL/gl.h>

bool set = true;
int level = 1;
int score = 0;
int fintime = 0;
int difficulty;
int resetcount = 0;
float windXY = 0.00; //Negative values change direction
float windZY = 0.00; // Zero idicates no wind
#include "sound.h"
#include "initialize.h" //Initialize world/levels 
#include "render.h"

#define GLUT_DISABLE_ATEXIT_HACK

#define win_width 1024
#define win_height 768


int main(int argc, char** argv) {
    glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 	glutInitWindowSize(win_width, win_height);
 	//glutFullScreen();
 	glutInitWindowPosition(0,0);
 	glutCreateWindow("Snipa");
    gameInit();  //initialize the game, load textures and stuffs
    

	glutSetCursor(GLUT_CURSOR_NONE); // hide mouse
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutMouseFunc(processMouse); //check for mouse clicks
	
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);  
	
   
    
    glutDisplayFunc(renderScene); //decide which display handlers to use
    

    glutIdleFunc(renderScene); 
 
     
    glutReshapeFunc(gameReshape);
        
    playTheme();
     
 
    glutTimerFunc (1, bulletAnimation, 0);
   

    glutMainLoop();
}
