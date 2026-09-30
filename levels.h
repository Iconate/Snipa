#include "MapObjects.h"
#include "Collision.h"
#include <stdlib.h>


Target targets[5];

bool timeSet = true;
bool lanesReady = false;
int lanesLevel = 0;
float targetSpeed[5];
float targetMinX[5];
float targetMaxX[5];
float targetBaseY[5];
int targetGrace[5];
int breakTime[5];
float breakX[5];
float breakY[5];
float breakZ[5];
float targetBaseZ[5];

Hitbox bulletHitbox = Hitbox(0.20);
Hitbox targetHitbox = Hitbox(3.0); 
int targetChoice = 0; 

#include "hud.h"
#include "animation.h"

#include "light.h"



Ground Sand = Ground();
Crate crates[30];
Wall wall[10];

void knockTarget(int index) {
    float oldX = targets[index].getXpos();
    float oldZ = targets[index].getZpos();
    float nextX = oldX;
    float nextZ = oldZ;
    int guard = 0;
    breakX[index] = oldX;
    breakY[index] = targets[index].getYpos() + targets[index].getHeight();
    breakZ[index] = oldZ;
    breakTime[index] = 22;
    do {
        float span = targetMaxX[index] - targetMinX[index];
        nextX = targetMinX[index] + span * ((rand() % 100) / 99.0f);
        nextZ = targetBaseZ[index] + ((rand() % 5) - 2) * 28.0f;
        if (nextZ < 70.0f) nextZ = 70.0f;
        if (nextZ > 360.0f) nextZ = 360.0f;
        guard += 1;
    } while (guard < 8 && (nextX - oldX)*(nextX - oldX) + (nextZ - oldZ)*(nextZ - oldZ) < 2500.0f);
    targets[index].setXpos(nextX);
    targets[index].setZpos(nextZ);
    targetSpeed[index] = -targetSpeed[index];
    targetGrace[index] = 10;
}

void ensureLanes() {
    int i;
    float xs[5], zs[5], speeds[5];
    if (lanesReady && lanesLevel == level)
        return;
    if (level == 2) {
        xs[0] = -40; zs[0] = 300; speeds[0] = 0.22f;
        xs[1] = 80;  zs[1] = 150; speeds[1] = -0.30f;
        xs[2] = 4;   zs[2] = 350; speeds[2] = 0.18f;
        xs[3] = -50; zs[3] = 200; speeds[3] = -0.26f;
        xs[4] = 100; zs[4] = 75;  speeds[4] = 0.34f;
    } else if (level == 3) {
        xs[0] = 10;  zs[0] = 150; speeds[0] = 0.20f;
        xs[1] = 30;  zs[1] = 100; speeds[1] = -0.28f;
        xs[2] = 80;  zs[2] = 75;  speeds[2] = 0.24f;
        xs[3] = -50; zs[3] = 200; speeds[3] = -0.16f;
        xs[4] = 100; zs[4] = 75;  speeds[4] = 0.32f;
    } else {
        xs[0] = 10;  zs[0] = 200; speeds[0] = 0.22f;
        xs[1] = 30;  zs[1] = 150; speeds[1] = -0.30f;
        xs[2] = 80;  zs[2] = 225; speeds[2] = 0.18f;
        xs[3] = -50; zs[3] = 250; speeds[3] = -0.26f;
        xs[4] = 100; zs[4] = 125; speeds[4] = 0.34f;
    }
    for (i = 0; i < 5; i++) {
        targetSpeed[i] = speeds[i];
        targetMinX[i] = xs[i] - 55.0f;
        targetMaxX[i] = xs[i] + 55.0f;
        targetBaseY[i] = 8.0f;
        targetBaseZ[i] = zs[i];
        targetGrace[i] = 0;
        breakTime[i] = 0;
        targets[i].setXpos(xs[i]);
        targets[i].setYpos(targetBaseY[i]);
        targets[i].setZpos(zs[i]);
        targets[i].setHeight(0.0f);
    }
    lanesReady = true;
    lanesLevel = level;
}

void drawMovingTargets() {
    int i;
    ensureLanes();
    for (i = 0; i < 5; i++) {
        float x;
        if (targetGrace[i] > 0)
            targetGrace[i] -= 1;
        if (!roundOver) {
            x = targets[i].getXpos() + targetSpeed[i];
            if (x > targetMaxX[i]) {
                x = targetMaxX[i];
                targetSpeed[i] = -targetSpeed[i];
            } else if (x < targetMinX[i]) {
                x = targetMinX[i];
                targetSpeed[i] = -targetSpeed[i];
            }
            targets[i].setXpos(x);
            targets[i].setYpos(targetBaseY[i] + sin(targets[i].getXpos() * 0.05f) * 1.2f);
        }
        if (breakTime[i] > 0) {
            float life = breakTime[i] / 22.0f;
            int shard;
            glPushMatrix();
            glTranslatef(breakX[i], breakY[i], breakZ[i]);
            for (shard = 0; shard < 3; shard++) {
                glPushMatrix();
                glTranslatef((shard - 1) * (1.0f - life) * 5.0f, (1.0f - life) * (2.0f + shard), 0.2f * shard);
                glRotatef((22 - breakTime[i]) * (35.0f + shard * 20.0f), 1.0f, 1.0f, 0.0f);
                glScalef(2.4f * life, 2.4f * life, 2.4f * life);
                targets[i].draw(target);
                glPopMatrix();
            }
            glPopMatrix();
            if (!roundOver)
                breakTime[i] -= 1;
        }
        glPushMatrix();
        targets[i].translate(targets[i].getXpos(), targets[i].getYpos() + targets[i].getHeight(), targets[i].getZpos());
        targets[i].scale(5.0f, 5.0f, 5.0f);
        targets[i].draw(target);
        glPopMatrix();
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
    
    Gravel.draw(gravel);
}
