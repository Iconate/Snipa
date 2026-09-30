#include <math.h>

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#endif

#include "menu.h"

#define mapWidth 200
#define mapLength 1000


bool warped; // used to check if the mouse has gone off screen



bool jumping = false;
//double zoom = 5;

void applyMouseLook(float diffx, float diffy) {
    float scale = rifle.getZoom() ? 0.01f : 0.25f;

    //keep camera from rotating beyond vertically up/down
    if ((player.xrot() >= -90 && diffy < 0) || (player.xrot() <= 90 && diffy > 0))
        player.setXrot(player.xrot() + scale * diffy);
    player.setYrot(player.yrot() + scale * diffx);
}

#ifdef __APPLE__
/* glutWarpPointer round-trips through the window server on every mouse
   event. A high-rate mouse then spends more time warping the cursor than
   drawing, which is why looking around drops to a few frames per second. */
static void useRelativeMouse() {
    CGAssociateMouseAndMouseCursorPosition(false);
}

static float macMouseScale() {
    static float scale = 0.0f;
    CGRect bounds;
    size_t pixelsWide;
    if (scale > 0.0f)
        return scale;
    bounds = CGDisplayBounds(CGMainDisplayID());
    pixelsWide = CGDisplayPixelsWide(CGMainDisplayID());
    scale = (bounds.size.width > 0) ? (float)pixelsWide / (float)bounds.size.width : 1.0f;
    return scale;
}
#endif

void setRelativeMouse(bool relative) {
#ifdef __APPLE__
    CGAssociateMouseAndMouseCursorPosition(relative ? false : true);
#else
    (void)relative;
#endif
}

void mouseMovement(int x, int y) {
#ifdef __APPLE__
    if (!(inGame && !roundOver))
        return;
    int32_t dx = 0;
    int32_t dy = 0;
    float pointScale;
    (void)x;
    (void)y;
    useRelativeMouse();
    CGGetLastMouseDelta(&dx, &dy);
    pointScale = macMouseScale();
    if (pointScale > 0.0f)
        applyMouseLook((float)dx / pointScale, (float)dy / pointScale);
#else
    if (!(inGame && !roundOver))
        return;
    if(!warped) {
        applyMouseLook((float)(x - 1024/2), (float)(y - 768/2));
		warped = true;
		glutWarpPointer(1024/2, 768/2);
	}
	else
		warped = false;
#endif
    glutPostRedisplay();
}

void processMouse(int button, int state, int x, int y) {
     
	if (state == GLUT_DOWN && inGame == true && !roundOver)  {
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




void menuDown() {
    playBeep();
    if (selection && menuSelection == 0) {
        diffselect -= 1;
        if (diffselect < 0)
            diffselect = 2;
    }
    if (!selection) {
        menuSelection += 1;
        if (menuSelection > menuItems)
            menuSelection = 0;
    }
}

void menuUp() {
    playBeep();
    if (selection && menuSelection == 0) {
        diffselect += 1;
        if (diffselect > 2)
            diffselect = 0;
    }
    if (!selection) {
        menuSelection -= 1;
        if (menuSelection < 0)
            menuSelection = menuItems;
    }
}

void menuConfirm() {
    if (selection && menuSelection == 0)
        go = true;
    playSelectBeep();
    selection = true;
}

void specialKeyDown(int key, int x, int y) {
    (void)x;
    (void)y;
    if (inGame)
        return;
    if (key == GLUT_KEY_DOWN)
        menuDown();
    else if (key == GLUT_KEY_UP)
        menuUp();
    glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) { // CHECK IF STRAFE AND FORWARD OR BACK IS PRESSED TO MOVE DIAGONALLY

    if (roundOver)
        return;

    if (inGame == true)   // In Game Controls
    {
                
        switch (key) {
            case 'w' : player.setMovement(1);player.setDirection(1);break;
            case 's' : player.setMovement(1);player.setDirection(2);break;
            case 'a' : player.setMovement(1);player.setDirection(3);break;
            case 'd' : player.setMovement(1);player.setDirection(4);break;
            case 'r': rifle.reload(); set = true; break;
            //case 32: jumping = true; break;
            case 'k' : startTime = true;
        }
    }else            // Menu Controls
    {
        switch(key) 
        {
               case 's': //Down
                    menuDown();
                    break;
                    
               case 'w': //Up
                    menuUp();
                    break;
                     
               case 13: //Enter
                    menuConfirm();
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


