#include <math.h>

class Player {
    private:
        float x;
        float y;
        float z;
        float xrotation;
        float yrotation;
        float playerAngle;
        float xstarting;
        float zstarting;
        float lastX;
        float lastY;
        int Direction;
        int Movement;
        float PlayerSpeed;
        float xrotrad, yrotrad;
        
    public:
           Player();
           float xpos();
           float ypos();
            float zpos();
            float xrot();
            float yrot();
            float angle();
            float xstart();
            float zstart();
            int direction();
            int movement();
            float playerSpeed();

           void setXpos(float);
           void setYpos(float);
           void setZpos(float);
           void setXrot(float);
           void setYrot(float);
           void setAngle(float);
           void setXstart(float);
           void setZstart(float);
           void setDirection(int);
           void setMovement(int);
           void setPlayerSpeed(float);

           void up();
           void down();
           void left();
           void right();

        
};

Player::Player(){
    this->x = 0;
    this->y = 10;
    this->z = -110;
    this->xrotation = 0;
    this->yrotation = 0;
    this->playerAngle = 0.0;
    this->Direction = 0;
    this->Movement = 0;
    this->PlayerSpeed = 2;
    this->xstarting = 0;
    this->zstarting = 0;
}

/* Obtain Player Values */

float Player::xpos(){
      return this->x;
}
float Player::ypos(){
      return this->y;
}
float Player::zpos(){
      return this->z;
}
float Player::xrot(){
      return this->xrotation;
}
float Player::yrot(){
      return this->yrotation;
}
float Player::xstart(){
      return this->xstarting;
}
float Player::zstart(){
      return this->zstarting;
}

float Player::angle(){
      return this->playerAngle;
}
float Player::playerSpeed(){
      return this->PlayerSpeed;
}
int Player::direction(){
      return this->Direction;
}
int Player::movement(){
      return this->Movement;
}

/* Set Player Values */

void Player::setXpos(float f){
      this->x = f;
}
void Player::setYpos(float f){
      this->y = f;
}
void Player::setZpos(float f){
      this->z = f;
}
void Player::setXrot(float f){
      this->xrotation = f;
}
void Player::setYrot(float f){
      this->yrotation = f;
}
void Player::setXstart(float f){
      this->xstarting = f;
}
void Player::setZstart(float f){
      this->zstarting = f;
}

void Player::setAngle(float f){
      this->playerAngle = f;
}
void Player::setPlayerSpeed(float i){
      this->PlayerSpeed = i;
}
void Player::setDirection(int i){
      this->Direction = i;
}
void Player::setMovement(int i){
      this->Movement = i;
}
       
/* Player Movements */

void Player::up(){
        this->yrotrad = (this->yrotation / 180 * 3.141592654f);
        this->x += float(sin((this->yrotrad)))/(this->PlayerSpeed);
        this->z -= float(cos(this->yrotrad))/this->PlayerSpeed;
}

void Player::down(){
        this->yrotrad = (this->yrotation / 180 * 3.141592654f);
        this->x -= float(sin(this->yrotrad)/this->PlayerSpeed);
        this->z += float(cos(this->yrotrad)/this->PlayerSpeed) ;
}

void Player::left(){
        this->yrotrad = (this->yrotation / 180 * 3.141592654f);
        this->x -= float(cos(this->yrotrad)/PlayerSpeed) ;
        this->z -= float(sin(this->yrotrad)/PlayerSpeed) ;
}

void Player::right(){
        this->yrotrad = (this->yrotation / 180 * 3.141592654f);
        this->x += float(cos(this->yrotrad)/PlayerSpeed) ;
        this->z += float(sin(this->yrotrad)/PlayerSpeed) ;
    }

Player player = Player();


