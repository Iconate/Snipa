#define mapWidth 200
#define mapLength 1000



class MapObject {
    private:
        float x,y,z;
    public:
        void translate(float,float,float);
        void rotate(float,float,float,float);
        void scale(float,float,float);
        float Length3dv(float*);  
};

void MapObject::translate(float x, float y, float z) {
    glTranslatef(x,y,z);
}

void MapObject::rotate(float angle, float x,float y,float z) {
    glRotatef(angle,x,y,z);
}

void MapObject::scale(float x, float y, float z) {
    glScalef(x,y,z);
}

float MapObject::Length3dv(float *v) {
   return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}



//World Mapobject class

class World : public MapObject {
    public:
        void draw(GLuint);
        GLUquadric *sphere;
};

void World::draw (GLuint texture) {
    this->sphere = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR

    gluQuadricNormals(sphere,GLU_SMOOTH);
    gluQuadricDrawStyle(sphere,GLU_FILL);
    gluQuadricTexture(sphere,GL_TRUE); 

    glPushMatrix();
    glTranslatef(0.0,0.0,300.0);
    glRotatef(-90.0,1.0,0.0,0.0);
   //glTranslatef(0.0,0.0,-700.0);
    float nomat[] = {0.3, 0.2, 0.2, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nomat);
    gluSphere(sphere,600,50,50); 
    glPopMatrix();
//gluDeleteQuadric(sphere); 
}

// GROUND CLASS

class Ground : public MapObject {
    public:
        void draw(GLuint);
};

void Ground::draw (GLuint texture) {
    
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glNormal3f(0.0,20.0,0.0); glVertex3f(-mapWidth,0.0, -mapWidth);
		glTexCoord2f(0.0, 20.0); glNormal3f(0.0,20.0,0.0); glVertex3f(-mapWidth,0.0, mapLength);
		glTexCoord2f(20.0, 20.0); glNormal3f(0.0,20.0,0.0); glVertex3f(mapWidth,0.0, mapLength);
		glTexCoord2f(20.0, 0.0); glNormal3f(0.0,20.0,0.0); glVertex3f(mapWidth,0.0, -mapWidth);
 	glEnd();
} 

class Wall : public MapObject {
    public:
        void draw(GLuint);
};

void Wall::draw (GLuint texture) {
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
 	glEnd();
    
}
// TARGET CLASS    
class Target : public MapObject {
    private:
            float height;
            float xpos;  
            float ypos;
            float zpos;
    public:
        void draw(GLuint);
        float getHeight();
        void setHeight(float);
        void setXpos(float);
        void setYpos(float);
        void setZpos(float);
        float getXpos();
        float getYpos();
        float getZpos();
};

void Target::draw (GLuint texture) {
    
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
    glBegin(GL_QUADS);
     	glTexCoord2f(0.0, 0.0); glNormal3f(0.0,0.0,5.0); glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 0.0); glNormal3f(0.0,0.0,5.0); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glNormal3f(0.0,0.0,5.0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glNormal3f(0.0,0.0,5.0); glVertex3f(-1.0, 1.0, 0.0);
	
 	 glEnd();
} 

float Target::getHeight(){
    return this->height;
}

void Target::setHeight(float h){
    this->height = h;
}

void Target::setXpos(float x){
     this->xpos = x;
}

void Target::setYpos(float y){
     this->ypos = y;
}

void Target::setZpos(float z){
     this->zpos = z;
}

float Target::getXpos(){
     return this->xpos;
}

float Target::getYpos(){
     return this->ypos;
}

float Target::getZpos(){
     return this->zpos;
}


// CRATE CLASS
class Crate : public MapObject {
    public:
        void draw(GLuint);
};

void Crate::draw (GLuint texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();
} 

//BLOCKADE
class Blockade : public MapObject {
    public:
        void draw(GLuint);
};

void Blockade::draw(GLuint texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST or GL_LINEAR
         
     //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTranslatef(0.0,0.0,-100.0);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glNormal3f(0.0,1.0,0.0); glVertex3f(-mapWidth, 0.0, 0.0);
	    glTexCoord2f(0.0, 1.0); glNormal3f(0.0,1.0,0.0); glVertex3f(-mapWidth, 5.0, 5.0);
		glTexCoord2f(5.0, 1.0); glNormal3f(0.0,10.0,0.0); glVertex3f(mapWidth, 5.0, 5.0);
		glTexCoord2f(5.0, 0.0); glNormal3f(0.0,10.0,0.0); glVertex3f(mapWidth, 0.0, 0.0);
 	glEnd();
}


