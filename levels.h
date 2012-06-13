#include "MapObjects.h"
#include "Collision.h"


Target targets[5];

bool timeSet = true;

Hitbox bulletHitbox = Hitbox(0.20);
Hitbox targetHitbox = Hitbox(3.0); 
int targetChoice = 0; 

#include "hud.h"
#include "animation.h"

#include "light.h"



Ground Sand = Ground();
Crate crates[30];
Wall wall[10];

//Choose random target to animate from the array
void animateRandom() {  
        if (timeSet){
            targetChoice = rand() % 5;
            //substitute &target1 for targetChoice in the  array
            animateTarget(&targets[targetChoice]);
        }else
        {
            animateTarget(&targets[targetChoice]);
        }
}

//sand level
void level1() {
Sand.draw(sand);
        
        glPushMatrix();
        crates[1].translate(10.0,4.0,190.0);
        crates[1].scale(5.0,5.0,5.0);
        crates[1].draw(crate);
        glPopMatrix();
        
        glPushMatrix();
        crates[2].translate(30.0,3.0,140);
        crates[2].scale(4.0,4.0,4.0);
        crates[2].draw(crate);
        glPopMatrix();
        
        glPushMatrix();
        crates[3].translate(80.0,5.0,220.0);
        crates[3].scale(5.0,5.0,5.0);
        crates[3].draw(crate);
        glPopMatrix();
        
        glPushMatrix();
        crates[4].translate(-50.0,5.0,240.0);
        crates[4].scale(4.0,4.0,4.0);
        crates[4].draw(crate);
        glPopMatrix();
        
        glPushMatrix();
        crates[5].translate(-80.0,3.0,70.0);
        crates[5].scale(6.0,6.0,6.0);
        crates[5].draw(crate);
        glPopMatrix();
        
        //if time has started, start target animation  
   
        if(startTime){
        //Some function should call these...but they only work when they are in here
        //I know they should be only called once...but I get gay errors...
        int i;
        for(i = 0; i < 10; i++) {
            targets[i].setYpos(5.0);
        }
        targets[0].setXpos(10.0);
        targets[0].setZpos(200.0);
        
        targets[1].setXpos(30.0);
        targets[1].setZpos(150.0);
        
        targets[2].setXpos(80.0);
        targets[2].setZpos(225.0);
        
        targets[3].setXpos(-50.0);
        targets[3].setZpos(250.0);
        
        targets[4].setXpos(100.0);
        targets[4].setZpos(125.0);

        
        animateRandom();
    }
}
//grass jungle levell
void level2() {
    Ground Grass = Ground();
    Grass.draw(grass);
    
    glPushMatrix();
    glTranslatef(-40.0, 0.0, 290.0);
    glScalef(10.0,10.0,10.0);
    wall[1].draw(hedges);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(80.0, 0.0, 140.0);
    glScalef(15.0,15.0,15.0);
    wall[1].draw(hedges);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.0,0.0,340.0);
    glScalef(10.0,10.0,10.0);
    wall[1].draw(hedges);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(100.0,0.0,70.0);
    glScalef(20.0,20.0,20.0);
    wall[1].draw(hedges);
    glPopMatrix();
    
    targets[0].setXpos(-40.0);
    targets[0].setZpos(300.0);
        
    targets[1].setXpos(80.0);
    targets[1].setZpos(150.0);
        
    targets[2].setXpos(4.0);
    targets[2].setZpos(350.0);
        
    targets[3].setXpos(-50.0);
    targets[3].setZpos(200.0);
        
    targets[4].setXpos(100.0);
    targets[4].setZpos(75.0);
    
    animateRandom();
    
}
//moon level
void level3() {
    Ground Gravel = Ground();
    
    glPushMatrix();
    glTranslatef(20.0,10.0,50.0);
    glScalef(10.0,10.0,10.0);
    wall[1].draw(wallt);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-40.0, 10.0, 100.0);
    glScalef(10.0, 10.0, 10.0);
    wall[2].draw(wallt);
    glPopMatrix();
    
    targets[0].setXpos(10.0);
    targets[0].setZpos(150.0);
        
    targets[1].setXpos(30.0);
    targets[1].setZpos(100.0);
        
    targets[2].setXpos(80.0);
    targets[2].setZpos(75.0);
        
    targets[3].setXpos(-50.0);
    targets[3].setZpos(200.0);
        
    targets[4].setXpos(100.0);
    targets[4].setZpos(75.0);
    Gravel.draw(gravel);
    
    animateRandom();
}
