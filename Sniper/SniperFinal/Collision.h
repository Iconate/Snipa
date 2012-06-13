class Hitbox{
      private:
              float radius;
              int zstacks;
              int xstacks;
      public:
          
             Hitbox(float);
             void bulletSphere(Bullet, Player);
             void draw();
             float getRadius();
};


Hitbox::Hitbox(float rad){
     this->radius = rad;
     this->zstacks = 10;
     this->xstacks = 10;
                          
}

//Create the wireframe around the bullet and translate it accordingly.
void Hitbox::bulletSphere(Bullet bullet, Player player){
     glColor3f(1.0,1.0,1.0);
     
     glPushMatrix();
     glTranslatef(player.xstart()+(bullet.xspd()),6-(bullet.yspd()),player.zstart()-(bullet.zspd()));
     glutWireSphere(this->radius, this->zstacks, this->xstacks);   
     glPopMatrix(); 
     glColor3f(1.0,1.0,1.0);
}

float Hitbox::getRadius(){
      return this->radius;     
}

void Hitbox::draw(){
      glutWireSphere(this->radius, this->zstacks, this->xstacks);  
}
