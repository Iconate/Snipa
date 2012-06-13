#include "Bullet.h"
#define win_width 1024
#define win_height 768

GLUquadric *cylinder = gluNewQuadric();
GLUquadric *scopecylinder = gluNewQuadric();
GLUquadric *barrel = gluNewQuadric();

//Text object errors that are bound to come up ingame.
Text reloadError = Text("RELOAD!",(int)(win_width*0.45),(int)(win_height*0.3333),0,(void *)font);
Text ammoError = Text("OUT OF AMMO!",(int)(win_width*0.42),(int)(win_height*0.3333),0,(void *)font);


class Gun {
    private:
        int ammo;
        int clip;
        double zoomFactor;
        bool isZoomed;
        bool isShooting;
        
        
    public:
        Gun();
        void draw(GLuint);
        void translate(float, float, float);
        void rotate(float angle, float, float, float);
        void shoot();
        void reload();
        void zoom();
        int getAmmo();
        int getClip();
        void setAmmo(int);
        bool getZoom();
        bool getShooting();
        void setShooting(bool);
        
};

void Gun::setAmmo(int i){
    this->ammo = i;   
}
Gun::Gun() {
    this->ammo = 0;
    this->clip = 5;
    this->zoomFactor = 7;
    this->isZoomed = false;
    this->isShooting = false;
}

void Gun::draw(GLuint texture) {
    //Using uber artistic skills to draw the scope
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
        
    gluQuadricNormals(cylinder,GLU_SMOOTH);
    gluQuadricDrawStyle(cylinder,GLU_FILL);
    gluQuadricTexture(cylinder,GL_TRUE);
    
    gluCylinder(cylinder, 1,1,3,32,200);
    
    gluQuadricNormals(scopecylinder,GLU_SMOOTH);
    gluQuadricDrawStyle(scopecylinder,GLU_FILL);
    gluQuadricTexture(scopecylinder,GL_TRUE);
    
    
    glTranslatef(0.0,2.0,0.0);
    gluCylinder(scopecylinder, 1,1,7,32,200);
}

void Gun::translate(float x, float y, float z) {
    glTranslatef(x,y,z);   
}

void Gun::rotate(float angle, float x,float y,float z) {
    glRotatef(angle,x,y,z);
}
//Shooting method, does some checks and plays sound to signal a shot.
void Gun::shoot() {
    if (this->clip == 0) {
        reloadError.draw();
    }
    if (this->clip > 0){ 
        isShooting = true;
        playShot();
        set = true;
        this->clip -= 1;
   }
}
void Gun::reload() {
    if (this->ammo == 0) {
        reloadError.draw();
    }else {
        playReload();
        this->clip = 5;
        this->ammo -= clip;
    }
    this->isShooting = false;
}

//Zoom code, used to zoom the scope when the player needs more accurate shots.
void Gun::zoom() {
    if (!isZoomed) {
            glMatrixMode (GL_PROJECTION); //set the matrix to projection
            glLoadIdentity ();
            gluPerspective (this->zoomFactor, (GLfloat)win_width / (GLfloat)win_height, 1.0, 1000.0);
            glMatrixMode (GL_MODELVIEW);
            isZoomed = true;
    }
    else {
            //zoomout();
            glMatrixMode (GL_PROJECTION); //set the matrix to projection
            glLoadIdentity ();
            gluPerspective (60, (GLfloat)win_width / (GLfloat)win_height, 1.0, 1000.0);
            glMatrixMode (GL_MODELVIEW);
            isZoomed = false;
    }
}
//Some getters for private attributes
int Gun::getAmmo() {
    return this->ammo;
}

int Gun::getClip() {
    return this->clip;
}

bool Gun::getZoom(){
     return this->isZoomed;
}

bool Gun::getShooting(){
     return this->isShooting;
}

void Gun::setShooting(bool b) {
    this->isShooting = b;
}
//Finally instantiate the single and only rifle used in the game.
Gun rifle = Gun();

