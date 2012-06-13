#define win_width 1024
#define win_height 768


char buffer[3];


Text timeError = Text("YOU RAN OUT OF TIME!",(int)(win_width*0.35),(int)(win_height*0.4),0,(void *)font);

Text hudammotext = Text("Ammo :      /",(int)(win_width*0.83),(int)(win_height*0.98307),0,(void *)font);
Text hudclip = Text((itoa(rifle.getClip(),buffer,10)),(int)(win_width*0.9277),(int)(win_height*0.98307),0,(void *)font);
Text hudammo = Text((itoa(rifle.getAmmo(),buffer,10)),(int)(win_width*0.9570),(int)(win_height*0.98307),0,(void *)font);
Text hudtargettext = Text("Targets: ", (int)(10), (int)(60), 0,(void *)font);
Text remainingTargets = Text("10", (int)(100), (int)(60), 0,(void *)font);

bool initTime = true;
bool timeExpired = false;


int elaptime;


void timer(){
     elaptime = glutGet(GLUT_ELAPSED_TIME)/1000;
     if(startTime){
        if(initTime){fintime += elaptime; initTime = false;}

        remainingTime.textUpdate((fintime - elaptime));  
        
        if((fintime - elaptime) <=0) {
            startTime = false;
            timeExpired = true;
        }
     }
  
     
     if(timeExpired) timeError.draw(1,1,1);
     
     timetext.draw();
     remainingTime.draw();
     
}

void targetText(){
    remainingTargets.draw(1.0,1.0,1.0);
    hudtargettext.draw(1.0,1.0,1.0);    
}

void ammo(){
        hudammotext.draw(0,0,0);
        hudclip.draw(); 
	    hudclip.textUpdate(rifle.getClip());
	    hudammo.draw(); 
	    hudammo.textUpdate(rifle.getAmmo());  
}


void arrow(){
        
        glBegin(GL_LINES);
        
        glVertex2f(0,0);
        glVertex2f(0,win_height*0.0651);
        glVertex2f(0,win_height*0.0651);
        glVertex2f(win_width*0.0097,win_height*0.0520);
        glVertex2f(0,win_height*0.0651);
        glVertex2f(-win_width*0.0097,win_height*0.0520);
        glEnd();
}

void windCompass(){
   
   glClearColor(1.0f,1.0f,1.0f,0.0f);
    glPushMatrix();
    setOrthographicProjection();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(win_width*0.95, win_height*0.075, 0.0);
    
    if(windXY !=0  && windZY == 0.0){
            glRotatef(player.yrot()-90, 0.0, 0.0, 1.0);
            arrow();
            NSwind.draw();
            EWwind.draw();

            NSwindvalue.textUpdate((int)(windZY*100));
            EWwindvalue.textUpdate((int)(windXY*100));

            NSwindvalue.draw();
            EWwindvalue.draw();

     }else if(windXY == 0.0 && windZY != 0.0){
           glRotatef(player.yrot(), 0.0, 0.0, 1.0);
           arrow();
           NSwind.draw();
           EWwind.draw();

           NSwindvalue.textUpdate((int)(windZY*100));
           EWwindvalue.textUpdate((int)(windXY*100));

           NSwindvalue.draw();
           EWwindvalue.draw();

     }else if (windXY == 0.0 && windZY == 0.0){
           renderBitmapString(-60, 0, 0,(void *)font, "No Wind");
           NSwind.draw();
           EWwind.draw();

           NSwindvalue.textUpdate((int)(windZY*100));
           EWwindvalue.textUpdate((int)(windXY*100));
           
           NSwindvalue.draw();
           EWwindvalue.draw();
           
     
     }else{
           glRotatef(player.yrot()-45, 0.0, 0.0, 1.0);
           arrow();
           NSwind.draw();
           EWwind.draw();

           NSwindvalue.textUpdate((int)(windZY*100));
           EWwindvalue.textUpdate((int)(windXY*100));

           NSwindvalue.draw();
           EWwindvalue.draw();

     }


    glColor3f(1.0f,1.0f,1.0f);     
    resetPerspectiveProjection();

    glPopMatrix();  
}

void crosshair(){
     glColor3f(1.0f,1.0f,1.0f); 
     glPushMatrix();
     setOrthographicProjection();
     glLoadIdentity();
     
      glBegin(GL_LINES);
        glVertex2f(win_width/2,win_height*.475);
        glVertex2f(win_width/2,win_height*.49);
        glVertex2f(win_width/2,win_height*.51);
        glVertex2f(win_width/2,win_height*.525);

        glVertex2f(win_width*.48,win_height/2);
        glVertex2f(win_width*.49,win_height/2);
        glVertex2f(win_width*.51,win_height/2);
        glVertex2f(win_width*.52,win_height/2);
        glEnd();
     glColor3f(1.0f,1.0f,1.0f);     
     resetPerspectiveProjection();
     glPopMatrix(); 
       
}



