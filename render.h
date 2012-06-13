
#include "Player.h"
#include "Text.h"

#include "Gun.h"

#include "keyboard.h"  //Handle user input and reflect changes for player
#include "levels.h"

Blockade block1 = Blockade();
World realworld = World();

void reset() {
    resetcount += 1;
    
    if (resetcount == 1) windXY = 0.25; //Negative values change direction
    if (resetcount == 2){ windZY = 0.25; windXY = 0.25;} 
    
    
   if (difficulty == 0){
       score = 0; 
       rifle.setAmmo(50);
    }else if (difficulty ==1){
        score = 0;
        rifle.setAmmo(30);
    }else {
        score = 0; 
        rifle.setAmmo(10); 
    }
       level++;
}

void camera () {
    glRotatef(player.xrot(),1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(player.yrot(),0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-player.xpos(),-player.ypos(),-player.zpos()); //translate the screen to the position of our camera
}


void renderScene() 
{     
    glEnable( GL_TEXTURE_2D ); //enable 2D texturing
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
    if (inGame == true)            // All world objects here
    {    
        lights();
        camera();  //Lights camera action.
        ammo();
        windCompass();
        crosshair();
        timer();
        targetText();
        
        if(rifle.getShooting()) { bullet.shootAnimate();  bulletHitbox.bulletSphere(bullet, player);  } //decide when to animate bullet
        
        
        glPushMatrix(); //position the players rifle appropriately
        rifle.translate(player.xpos(),player.ypos()-1.75,player.zpos() + 4);
        rifle.rotate(player.yrot(),0.0,-1.0,0.0);
        rifle.rotate(player.xrot() + 180,-1.0,0.0,0.0);
      //  rifle.translate(-player.xpos(),-(player.ypos()-1.75),-(player.zpos() + 4));
        rifle.draw(scope);
        glPopMatrix();
    
    
        //Decide which level we're on, and render it
        if (score == 10) {
            reset();
        }  
        
        if (level == 1) level1();
        if (level == 2) level2();
        if (level == 3) level3();
        //Render the sky and blockade, which are used in each of the three levels.
        block1.draw(blockade);
        realworld.draw(world);

    }
    
    else {                             // All menu features here
        menuCheck(selection, menuSelection);                                                              
    }

    glDisable(GL_TEXTURE_2D);
    
    if (player.movement()) {
       moveDirection(player.direction());
}
	glutSwapBuffers();

}

