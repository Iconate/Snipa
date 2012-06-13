#include "BMPLoader.h"

bool inGame = false;
bool startTime = false;
unsigned char* bitmapData;
LOAD_TEXTUREBMP_RESULT loadBMP(const char* filename, 
                               unsigned char** bitmapData);
                               
GLuint grass, sand ,gravel, blockade, crate, world, target, gun, scope,wallt, hedges;

//Load Textures for the game

void gameInit() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	
    
    initSounds();
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_DEPTH_TEST);
	loadOpenGL2DTextureBMP("textures/world.bmp", &world, GL_RGB);
	glEnable(GL_DEPTH_TEST);
    loadOpenGL2DTextureBMP("textures/grass.bmp", &grass, GL_RGB);
    loadOpenGL2DTextureBMP("textures/crate.bmp", &crate, GL_RGB);
    loadOpenGL2DTextureBMP("textures/blockade.bmp", &blockade, GL_RGB);
    loadOpenGL2DTextureBMP("textures/target.bmp", &target, GL_RGB);
    loadOpenGL2DTextureBMP("textures/building.bmp", &wallt, GL_RGB);
    loadOpenGL2DTextureBMP("textures/scope.bmp", &scope, GL_RGB);
    loadOpenGL2DTextureBMP("textures/sand.bmp", &sand, GL_RGB);
    loadOpenGL2DTextureBMP("textures/gravel.bmp", &gravel, GL_RGB);
    loadOpenGL2DTextureBMP("textures/hedges.bmp", &hedges, GL_RGB);

}

void gameReshape(int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewportto the current window specificatios
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
  
          gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height,
  
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

