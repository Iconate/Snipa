
#include <stdio.h>
#include "Player.h"
#include "Text.h"

#include "Gun.h"

#include "keyboard.h"  //Handle user input and reflect changes for player
#include "levels.h"

Blockade block1 = Blockade();
World realworld = World();

void dismissResults() {
    int window;
    if (!resultsWindow)
        return;
    window = resultsWindow;
    resultsWindow = 0;
    glutDestroyWindow(window);
}

void returnToMenu() {
    inGame = false;
    go = false;
    selection = false;
    menuSelection = 0;
    roundOver = false;
    wantResults = false;
    startTime = false;
    timeExpired = false;
    rifle.setShooting(false);
    set = true;
    player.setMovement(0);
    setRelativeMouse(false);
    dismissResults();
    if (gameWindow) {
        glutSetWindow(gameWindow);
        glutShowWindow();
    }
    if (sound)
        playTheme();
}

void beginRound() {
    score = 0;
    shotsHit = 0;
    shotsMissed = 0;
    roundOver = false;
    wantResults = false;
    resultsChoice = 0;
    lanesReady = false;
    set = true;
    startTime = true;
    timeExpired = false;
    initTime = true;
    go = false;
    rifle.setShooting(false);
    if (difficulty == 0)
        rifle.setAmmo(10);
    else if (difficulty == 1)
        rifle.setAmmo(6);
    else
        rifle.setAmmo(2);
    player.setXpos(0);
    player.setYpos(10);
    player.setZpos(-110);
    player.setXrot(0);
    player.setYrot(180);
    player.setMovement(0);
    player.setDirection(0);
    setRelativeMouse(true);
    if (gameWindow) {
        glutSetWindow(gameWindow);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}

void tryAgain() {
    beginRound();
    dismissResults();
    if (gameWindow) {
        glutSetWindow(gameWindow);
        glutShowWindow();
    }
}

void registerHit(int targetIndex) {
    if (!rifle.getShooting())
        return;
    shotsHit += 1;
    score += 100;
    rifle.setShooting(false);
    set = true;
    knockTarget(targetIndex);
}

void registerMiss() {
    if (!rifle.getShooting())
        return;
    shotsMissed += 1;
    score -= 25;
    rifle.setShooting(false);
    set = true;
}

void resultsString(float x, float y, const char *text) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void paintResultChoice(int index, float y, const char *label) {
    if (resultsChoice == index) {
        glColor3f(0.82f, 0.62f, 0.18f);
        glBegin(GL_QUADS);
        glVertex2f(28, y - 8);
        glVertex2f(240, y - 8);
        glVertex2f(240, y + 22);
        glVertex2f(28, y + 22);
        glEnd();
        glColor3f(0.08f, 0.08f, 0.08f);
    } else {
        glColor3f(0.90f, 0.90f, 0.90f);
    }
    resultsString(40, y, label);
}

void drawResultsWindow() {
    char line[80];
    int shots = shotsHit + shotsMissed;
    int accuracy = shots > 0 ? (shotsHit * 100) / shots : 0;
    const char *mode = "Hard";
    if (difficulty == 0)
        mode = "Easy";
    else if (difficulty == 1)
        mode = "Medium";

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glClearColor(0.12f, 0.13f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, resultsW, 0, resultsH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    resultsString(36, resultsH - 48, "Out of Ammo");
    snprintf(line, sizeof(line), "Difficulty: %s", mode);
    resultsString(36, resultsH - 88, line);
    snprintf(line, sizeof(line), "Score: %d", score);
    resultsString(36, resultsH - 124, line);
    snprintf(line, sizeof(line), "Hits: %d", shotsHit);
    resultsString(36, resultsH - 160, line);
    snprintf(line, sizeof(line), "Misses: %d", shotsMissed);
    resultsString(36, resultsH - 196, line);
    snprintf(line, sizeof(line), "Shots: %d", shots);
    resultsString(36, resultsH - 232, line);
    snprintf(line, sizeof(line), "Accuracy: %d%%", accuracy);
    resultsString(36, resultsH - 268, line);
    resultsString(36, resultsH - 310, "Hit +100     Miss -25");
    paintResultChoice(0, 96, "Try Again");
    paintResultChoice(1, 52, "Close");
    glColor3f(0.65f, 0.65f, 0.65f);
    resultsString(36, 18, "Up/Down and Enter. Close returns to the menu.");
    glutSwapBuffers();
}

void resultsReshape(int w, int h) {
    if (h < 1)
        h = 1;
    resultsW = w;
    resultsH = h;
    glViewport(0, 0, w, h);
}

void chooseResult() {
    if (resultsChoice == 0)
        tryAgain();
    else
        returnToMenu();
}

void resultsKey(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    if (key == 'w' || key == 'W' || key == 's' || key == 'S')
        resultsChoice = 1 - resultsChoice;
    else if (key == 13 || key == ' ')
        chooseResult();
    else if (key == 27)
        returnToMenu();
    if (resultsWindow) {
        glutSetWindow(resultsWindow);
        glutPostRedisplay();
    }
}

void resultsSpecial(int key, int x, int y) {
    (void)x;
    (void)y;
    if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
        resultsChoice = 1 - resultsChoice;
    if (resultsWindow) {
        glutSetWindow(resultsWindow);
        glutPostRedisplay();
    }
}

void resultsClick(int button, int state, int x, int y) {
    int yUp;
    (void)x;
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;
    yUp = resultsH - y;
    if (yUp >= 84 && yUp <= 122) {
        resultsChoice = 0;
        tryAgain();
    } else if (yUp >= 40 && yUp <= 78) {
        resultsChoice = 1;
        returnToMenu();
    }
}

void openResults() {
    wantResults = false;
    if (resultsWindow || !inGame)
        return;
    roundOver = true;
    player.setMovement(0);
    rifle.setShooting(false);
    set = true;
    setRelativeMouse(false);
    resultsChoice = 0;
    resultsW = 520;
    resultsH = 440;
    glutInitWindowSize(resultsW, resultsH);
    glutInitWindowPosition(220, 140);
    resultsWindow = glutCreateWindow("Results");
    glutDisplayFunc(drawResultsWindow);
    glutReshapeFunc(resultsReshape);
    glutKeyboardFunc(resultsKey);
    glutSpecialFunc(resultsSpecial);
    glutMouseFunc(resultsClick);
    glutWMCloseFunc(returnToMenu);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void pumpFrames() {
    if (wantResults)
        openResults();
    if (gameWindow) {
        glutSetWindow(gameWindow);
        glutPostRedisplay();
    }
    if (resultsWindow) {
        glutSetWindow(resultsWindow);
        glutPostRedisplay();
    }
}

void reset() {
    resetcount += 1;
    
    if (resetcount == 1) windXY = 0.25; //Negative values change direction
    if (resetcount == 2){ windZY = 0.25; windXY = 0.25;} 
    
    
   if (difficulty == 0){
       score = 0; 
       rifle.setAmmo(10);
    }else if (difficulty ==1){
        score = 0;
        rifle.setAmmo(6);
    }else {
        score = 0; 
        rifle.setAmmo(2); 
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
        
        if(!roundOver && rifle.getShooting()) { bullet.shootAnimate();  bulletHitbox.bulletSphere(bullet, player);  } //decide when to animate bullet
        
        
        glPushMatrix(); //position the players rifle appropriately
        rifle.translate(player.xpos(),player.ypos()-1.75,player.zpos() + 4);
        rifle.rotate(player.yrot(),0.0,-1.0,0.0);
        rifle.rotate(player.xrot() + 180,-1.0,0.0,0.0);
      //  rifle.translate(-player.xpos(),-(player.ypos()-1.75),-(player.zpos() + 4));
        rifle.draw(scope);
        glPopMatrix();
    
    
        if (level == 1) level1();
        if (level == 2) level2();
        if (level == 3) level3();
        drawMovingTargets();
        //Render the sky and blockade, which are used in each of the three levels.
        block1.draw(blockade);
        realworld.draw(world);

        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        ammo();
        windCompass();
        crosshair();
        timer();
        targetText();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);

        if (!roundOver && !rifle.getShooting() && rifle.getClip() == 0 && rifle.getAmmo() == 0)
            wantResults = true;

    }
    
    else {                             // All menu features here
        menuCheck(selection, menuSelection);                                                              
    }

    glDisable(GL_TEXTURE_2D);
    
    if (!roundOver && player.movement()) {
       moveDirection(player.direction());
}
	glutSwapBuffers();

}

