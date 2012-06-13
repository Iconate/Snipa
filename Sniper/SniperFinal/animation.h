
float t = 0.0;

const Target *  const collision( Target *  tar){

     
     float xxx = tar->getXpos() - (player.xstart() + bullet.xspd());
     float yyy = (tar->getYpos()+tar->getHeight()) - (6 - bullet.yspd());
    
     float zzz = tar->getZpos() - (player.zstart()- bullet.zspd());
     
     if (sqrt( (xxx*xxx) + (yyy*yyy) + (zzz*zzz)) <= 3.20) {
      score++;
      if (10 - score == 0){
        remainingTargets.textUpdate(10);  
      }else{
         remainingTargets.textUpdate((10-score));
    }  
      rifle.setShooting(false);
      set = true;
}
          
}

static void bulletAnimation(int value) { 
       
    
    
    float yrotrad = (player.yrot() / 180 * 3.141592654f);
    float xrotrad = (player.xrot() / 180 * 3.141592654f);
    float gravity = 9.8; //   Pulls the bullet down relative to the time traveled
                          //   **Toy with bullet velocity to get desired results first**
    if (rifle.getShooting()){
    
    if(set){
            t = 0.0;
            bullet.setXspd(0.0); 
            bullet.setYspd(-3.8);
            bullet.setZspd(0.0);
            player.setXstart(player.xpos());
            player.setZstart(player.zpos());
            bullet.setDirRate(0,sin(yrotrad));
            bullet.setDirRate(1,sin(xrotrad)); 
            bullet.setDirRate(2,cos(yrotrad));
            set = false;
            }
                        
          

        t += 0.005;  // Higher values make pinnicle of the trajectory sooner 
                    // Shouldn't really be changed ever
                    // Adjusting bullet.vel can achieve many of the same  results
                    
        
        bullet.setXspd((bullet.xspd()) + (bullet.dirRate(0)*bullet.vel()) + windXY*gravity*(t*t)); 
        bullet.setYspd((bullet.yspd()) + (bullet.dirRate(1)*bullet.vel()) + 0.5*gravity*(t*t));
        bullet.setZspd((bullet.zspd()) + (bullet.dirRate(2)*bullet.vel()) + windZY*gravity*(t*t)); 
        
        
        collision(&targets[targetChoice]); // Check collision with current animating target.
        
        } 
        
     
    
    glutTimerFunc (1, bulletAnimation, 0);
    glutPostRedisplay();
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





