#include "BMPLoader.h"
#include <stdio.h>

bool inGame = false;
bool startTime = false;
unsigned char* bitmapData;
LOAD_TEXTUREBMP_RESULT loadBMP(const char* filename, 
                               unsigned char** bitmapData);
                               
GLuint grass, sand ,gravel, blockade, crate, world, target, gun, scope,wallt, hedges;

static void loadGameTexture(const char *filename, GLuint *id) {
    LOAD_TEXTUREBMP_RESULT result = loadOpenGL2DTextureBMP(filename, id, GL_RGB);
    if (result != LOAD_TEXTUREBMP_SUCCESS)
        fprintf(stderr, "Snipa: failed to load %s (error %d)\n", filename, (int)result);
}

//Load Textures for the game

void gameInit() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	
    
    initSounds();
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_DEPTH_TEST);
	loadGameTexture("textures/world.bmp", &world);
	glEnable(GL_DEPTH_TEST);
    loadGameTexture("textures/grass.bmp", &grass);
    loadGameTexture("textures/crate.bmp", &crate);
    loadGameTexture("textures/blockade.bmp", &blockade);
    loadGameTexture("textures/target.bmp", &target);
    loadGameTexture("textures/building.bmp", &wallt);
    loadGameTexture("textures/scope.bmp", &scope);
    loadGameTexture("textures/sand.bmp", &sand);
    loadGameTexture("textures/gravel.bmp", &gravel);
    loadGameTexture("textures/hedges.bmp", &hedges);

}

void gameReshape(int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewportto the current window specificatios
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
  
          gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height,
  
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

