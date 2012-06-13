#include <math.h>


#include "menu.h"

#define mapWidth 200
#define mapLength 1000


bool warped; // used to check if the mouse has gone off screen



bool jumping = false;
//double zoom = 5;

void mouseMovement(int x, int y) {
    if(!warped) {
		float diffx = x - 1024/2;
		float diffy = y - 768/2;

		//keep camera from rotating beyond vertically up/down
		if(player.xrot()>=-90 && diffy < 0)
            if(rifle.getZoom()){                     
			      player.setXrot(player.xrot() + 0.01f*diffy);
            }else{
                  player.setXrot(player.xrot() + 0.25f*diffy);
            }
		else if(player.xrot()<=90 && diffy > 0)
			if(rifle.getZoom()){                     
			      player.setXrot(player.xrot() + 0.01f*diffy);
            }else{
                  player.setXrot(player.xrot() + 0.25f*diffy);
            }
        
        if(rifle.getZoom()){  //when player is zoomed in, camera wont move at the same rate as zoomed out
		    player.setYrot(player.yrot() + 0.01f*diffx); 
        }else{
            player.setYrot(player.yrot() + 0.25f*diffx);
        }
		warped = true;
		glutWarpPointer(1024/2, 768/2);
	}
	else
		warped = false;
    glutPostRedisplay();
}

void processMouse(int button, int state, int x, int y) {
     
	if (state == GLUT_DOWN && inGame == true)  {
		if (button == GLUT_LEFT_BUTTON) { //shoot
               
			     rifle.shoot();

		}

		if (button == GLUT_RIGHT_BUTTON) { // zoom
		           rifle.zoom();
   
		}
	}
}

void moveDirection(int i) {   
    if (i == 1){  //up
        player.up();
    }
    if (i == 2){  //down
        player.down();
    }
    if (i == 3){  //left
        player.left();
    }
    if (i == 4){  //right
        player.right();
    }
    
    if (player.xpos() > mapWidth) {
        player.setXpos(mapWidth);
    }
    if (player.xpos() < -mapWidth) {
        player.setXpos(-mapWidth);
    }
    if (player.zpos() < -mapWidth) {
        player.setZpos(-mapWidth);
    }
    if (player.zpos() > -105) {
        player.setZpos(-105);
    }
}




void keyboardDown(unsigned char key, int x, int y) { // CHECK IF STRAFE AND FORWARD OR BACK IS PRESSED TO MOVE DIAGONALLY

    if (inGame == true)   // In Game Controls
    {
                
        switch (key) {
            case 'w' : player.setMovement(1);player.setDirection(1);break;
            case 's' : player.setMovement(1);player.setDirection(2);break;
            case 'a' : player.setMovement(1);player.setDirection(3);break;
            case 'd' : player.setMovement(1);player.setDirection(4);break;
            case 'r': if(rifle.getClip() != 5) rifle.reload(); set = true; break;
            //case 32: jumping = true; break;
            case 'k' : startTime = true;
        }
    }else            // Menu Controls
    {
        switch(key) 
        {
               case 's': //Down
               playBeep();
               if(selection && menuSelection == 0){
                    diffselect -= 1;
                    if (diffselect < 0)
                        diffselect = 2;
               }
               if (!selection) {
                    menuSelection += 1;
                    if (menuSelection > menuItems)
                       menuSelection = 0;
               }
                    break;
                    
               case 'w': //Up
               playBeep();
               if(selection && menuSelection == 0){
                    diffselect += 1;
                    if (diffselect > 2)
                        diffselect = 0;
               }
               if (!selection) {
                     menuSelection -=1;
                     if (menuSelection < 0)
                        menuSelection = menuItems;
               }    
                     break;
                     
               case 13: //Enter
                    if(selection && menuSelection == 0) go = true;
                    playSelectBeep();
                    selection = true;
                    break;
                    
               case 'b':
               playSelectBeep();
               if(!inGame & menuSelection != 0)
                    selection = false;
                    break;
               
               case 'a':  //Sound ON
                    if(menuSelection == 1 && selection){
                        playBeep();
                        sound = true;
                        playTheme();
                        }
                        break;
               
               case 'd':  //Sound OFF
                   if(menuSelection == 1 && selection){
                        playBeep();
                        sound = false;
                        stopTheme();
                        }
                        break;
               
                    
               default:
                     break;            
         } //end switch
     }//end else
	 if (key==27)
     {
        exit(0);
     }
}

void keyboardUp(unsigned char key, int x, int y) {

	switch (key) {
		case 'w' : player.setMovement(0);player.setDirection(0);break;
		case 's' : player.setMovement(0);player.setDirection(0);break;
        case 'a' : player.setMovement(0);player.setDirection(0);break;
        case 'd' : player.setMovement(0);player.setDirection(0);break;
	}
}


