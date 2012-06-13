class Bullet{
    private:
        float xspeed,yspeed,zspeed;
        float direction[3]; //x,y,z
        float velocity;
    public:
        Bullet();
        void draw();
        float xspd();
        float zspd();
        float yspd();
        void setXspd(float);
        void setYspd(float);
        void setZspd(float);
        float dirRate(int);
        void setDirRate(int, float);
        float vel();
        void setVel(float);
        void translate(float, float, float);
        void scale(float, float, float);
        void shootAnimate();
        
             
};
void Bullet::translate(float x, float y, float z) {
    glTranslatef(x,y,z);   
}

void Bullet::scale(float x,float y,float z) {
    glScalef(x,y,z);
}

Bullet::Bullet() {
    this->xspeed = 0.0;
    this->yspeed = 0.0;
    this->zspeed = 0.0;
    this->velocity = 7.0;
}

float Bullet::vel() {
    return this->velocity;
}

void Bullet::setVel(float f) {
    this->velocity = f;    
}

float Bullet::dirRate(int i) {
    return this->direction[i];
}

void Bullet::setDirRate(int i, float f) {
    this->direction[i] = f;
}

float Bullet::xspd() {
    return this->xspeed;
}
 
void Bullet::setXspd(float f) {
    this->xspeed = f;     
}

float Bullet::yspd() {
    return this->yspeed;
}
 
void Bullet::setYspd(float f) {
    this->yspeed = f;     
}

float Bullet::zspd() {
    return this->zspeed;
}
 
void Bullet::setZspd(float f) {
    this->zspeed = f;                                 
}                 
void Bullet::draw() {
    glBegin(GL_POINT);
        glVertex3f(0.0,0.0,0.0);
		
    glEnd();	
}


void Bullet::shootAnimate() {
    glPushMatrix();
    draw();
    translate(player.xstart()+(this->xspd()),(this->yspd()),player.zstart()-(this->zspd()));
    //scale(2.0,2.0,2.0);
    glPopMatrix();
            
}
Bullet bullet = Bullet();
 //end function
    
