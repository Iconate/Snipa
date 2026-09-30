
float shotPrevX = 0, shotPrevY = 0, shotPrevZ = 0;
float shotMuzzleX = 0, shotMuzzleZ = 0;

float bulletX() { return player.xstart() + bullet.xspd(); }
float bulletY() { return 6.0f - bullet.yspd(); }
float bulletZ() { return player.zstart() - bullet.zspd(); }

float segmentDistance2(float ax, float ay, float az, float bx, float by, float bz,
                       float px, float py, float pz) {
    float abx = bx - ax, aby = by - ay, abz = bz - az;
    float apx = px - ax, apy = py - ay, apz = pz - az;
    float ab2 = abx*abx + aby*aby + abz*abz;
    float along = 0.0f;
    float cx, cy, cz;
    if (ab2 > 0.0001f) {
        along = (apx*abx + apy*aby + apz*abz) / ab2;
        if (along < 0.0f) along = 0.0f;
        if (along > 1.0f) along = 1.0f;
    }
    cx = ax + abx*along - px;
    cy = ay + aby*along - py;
    cz = az + abz*along - pz;
    return cx*cx + cy*cy + cz*cz;
}

void resolveShot() {
    float bx = bulletX();
    float by = bulletY();
    float bz = bulletZ();
    float dx, dz;
    int i;
    for (i = 0; i < 5; i++) {
        float tx = targets[i].getXpos();
        float ty = targets[i].getYpos() + targets[i].getHeight();
        float tz = targets[i].getZpos();
        if (targetGrace[i] > 0)
            continue;
        if (segmentDistance2(shotPrevX, shotPrevY, shotPrevZ, bx, by, bz, tx, ty, tz) <= 49.0f) {
            registerHit(i);
            return;
        }
    }
    dx = bx - shotMuzzleX;
    dz = bz - shotMuzzleZ;
    if (by < 0.5f || dx*dx + dz*dz > 520.0f * 520.0f)
        registerMiss();
    else {
        shotPrevX = bx;
        shotPrevY = by;
        shotPrevZ = bz;
    }
}

static void bulletAnimation(int value) {
    float yrotrad = (player.yrot() / 180 * 3.141592654f);
    float xrotrad = (player.xrot() / 180 * 3.141592654f);
    if (rifle.getShooting() && !roundOver) {
        if (set) {
            bullet.setXspd(0.0);
            bullet.setYspd(-3.8);
            bullet.setZspd(0.0);
            player.setXstart(player.xpos());
            player.setZstart(player.zpos());
            bullet.setDirRate(0, sin(yrotrad));
            bullet.setDirRate(1, sin(xrotrad));
            bullet.setDirRate(2, cos(yrotrad));
            shotMuzzleX = player.xstart();
            shotMuzzleZ = player.zstart();
            shotPrevX = bulletX();
            shotPrevY = bulletY();
            shotPrevZ = bulletZ();
            set = false;
        }

        bullet.setXspd((bullet.xspd()) + (bullet.dirRate(0)*bullet.vel()) + windXY * 0.02f);
        bullet.setYspd((bullet.yspd()) + (bullet.dirRate(1)*bullet.vel()) + 0.012f);
        bullet.setZspd((bullet.zspd()) + (bullet.dirRate(2)*bullet.vel()) + windZY * 0.02f);

        resolveShot();
    }

    glutTimerFunc(1, bulletAnimation, 0);
    if (gameWindow) {
        glutSetWindow(gameWindow);
        glutPostRedisplay();
    }
}

int targetTime = 0;



const Target *  const animateTarget( Target *  tar){
    float animateSpeed = 0.075;
    int timeUp = 5; //Number of seconds allowed up, starting from when it starts to accend right before decending

    if(timeSet){targetTime = elaptime; timeSet = false;}

    if(elaptime - targetTime < timeUp){
          if(tar->getHeight() <= 5){  tar->setHeight(tar->getHeight() + animateSpeed);}        
    }else{
          if(tar->getHeight() > 0){  tar->setHeight(tar->getHeight() - animateSpeed);}
          else{timeSet = true;}
    }
    
        glPushMatrix();
        tar->translate(tar->getXpos(),tar->getYpos() + tar->getHeight(),tar->getZpos());
        targetHitbox.draw();
        tar->scale(5.0,5.0,5.0);
        tar->draw(target);
        glPopMatrix();
    return tar;
}




static void jump(int value){
       float j =1;
       if(jumping){
                if(player.ypos() < 17) player.setYpos(player.ypos() + j);
                if(player.ypos() >= 17.0) jumping = false;  
                        
        }else
                if(player.ypos() > 8) player.setYpos(player.ypos() - j);      
       

       glutTimerFunc (15, jump, 0);
       
       glutPostRedisplay();
}





