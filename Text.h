#include <iostream>
#define win_width 1024
#define win_height 768
int font = (int)GLUT_BITMAP_TIMES_ROMAN_24;
int font2 = (int)GLUT_BITMAP_TIMES_ROMAN_10;


void setOrthographicProjection() 
{
     
     // switch to projection mode
	 glMatrixMode(GL_PROJECTION);
	 // save previous matrix which contains the 
	 //settings for the perspective projection
	 glPushMatrix();
	 // reset matrix
	 glLoadIdentity();
	 // set a 2D orthographic projection
	 gluOrtho2D(0, win_width, 0, win_height);
	 // invert the y axis, down is positive
	 glScalef(1, -1, 1);
	 // mover the origin from the bottom left corner
	 // to the upper left corner
	 glTranslatef(0, -win_height, 0);
	 glMatrixMode(GL_MODELVIEW);
	 
}

void resetPerspectiveProjection() 
{
     
     glMatrixMode(GL_PROJECTION);
	 glPopMatrix();
	 glMatrixMode(GL_MODELVIEW);
	
}

void renderBitmapString(float x, float y, float z, void *font, char *string) {
     char *c;
     glRasterPos3f(x, y, z);
     for (c=string; *c != '\0'; c++) {
         glutBitmapCharacter(font, *c);
     }
}

class Text{
      private:
              char *text;
              int x,y,z;
              char buffer[5];
              char *temp;
              float red,green,blue;
              void *font;
      public:
             Text(char*,int,int,int);
             Text(char*,int,int,int,void*);
             Text(char*,int,int,int,float,float,float);
             void draw();
             void move(int,int);
             void textUpdate(char*);
             void textUpdate(int);
             void draw(float, float, float);
             
};

Text::Text (char *text, int x, int y, int z, float red, float green, float blue){
           this->text = text;
           this->x = x;
           this->y = y;
           this->z = z;
           this->red = red;
           this->green = green;  
           this->blue = blue;    
} 

Text::Text (char *text, int x, int y, int z, void *font){
           this->text = text;
           this->x = x;
           this->y = y;
           this->z = z;
           this->font = font;
           this->red = 1.0;
           this->blue = 1.0;  
           this->green = 1.0;       
}   

Text::Text (char *text, int x, int y, int z){
           this->text = text;
           this->x = x;
           this->y = y;
           this->z = z;
           this->red = 1.0;
           this->blue = 1.0;  
           this->green = 1.0;       
}      

void Text::draw(){
     glClearColor(1.0f,1.0f,1.0f,0.0f);
     glPushMatrix();
     setOrthographicProjection();
     glLoadIdentity();
     glColor3f(this->red, this->green, this->blue);
     renderBitmapString(this->x,this->y,this->z,(void *)font,this->text);
    //lColor3f(1.0f,1.0f,1.0f);     
     resetPerspectiveProjection();
     glPopMatrix();   
}

void Text::draw(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
    glClearColor(1.0f,1.0f,1.0f,1.0f);
     glPushMatrix();
     setOrthographicProjection();
     glLoadIdentity();
     glColor3f(this->red, this->green, this->blue);
     renderBitmapString(this->x,this->y,this->z,(void *)font,this->text);
    glColor3f(1.0f,1.0f,1.0f);     
     resetPerspectiveProjection();
     glPopMatrix();   
}

void Text::move(int x, int y){
     this->x = x;
     this->y = y;
}

void Text::textUpdate(char *text){
     this->text = text;
}

void Text::textUpdate(int i){ 
     this->text = itoa(i,buffer,10);

}


//MENU TEXT
Text start = Text("Start", (int)(win_width - win_width/4),(int)(win_height - (win_height/4)*3),0,(void *)font);
Text options = Text("Options", (int)(win_width - win_width/4),(int)(win_height - (win_height/4)*2),0,(void *)font);
Text optionsTitle = Text("OPTIONS", (int)win_width/2 - 50, (int)25,0);
Text exittext = Text("Exit", (int)(win_width - win_width/4),(int)(win_height - (win_height/4)*1),0,(void *)font);
Text music = Text("Music:", (int)(win_width/2 - 80),(int)(win_height/2),0,(void *)font);
Text on = Text("ON", (int)(win_width/2),(int)(win_height/2),0,(void *)font);
Text off = Text("OFF", (int)(win_width/2 + 60),(int)(win_height/2),0,(void *)font);
Text back = Text("Press 'b' to go BACK.", 30,win_height - 30,0,(void *)font);    

Text easy = Text("easy", (int)(win_width/2),(int)(win_height/2 + 60),0,(void *)font);
Text medium = Text("medium", (int)(win_width/2),(int)(win_height/2),0,(void *)font);
Text hard = Text("hard", (int)(win_width/2),(int)(win_height/2 - 60),0,(void *)font);

//HUD TEXT
Text NSwind = Text("NS Wind:              km/h", (int)(win_width*0.9), (int)(win_height*0.1302),0,(void *)font2);
Text EWwind = Text("WE Wind:              km/h", (int)(win_width*0.9), (int)(win_height*0.1452),0,(void *)font2); 
Text NSwindvalue = Text("0.0", (int)(win_width*0.945), (int)(win_height*0.1302),0,(void *)font2);
Text EWwindvalue = Text("0.0", (int)(win_width*0.9455), (int)(win_height*0.1452),0,(void *)font2);

Text timetext = Text("Time:      sec", (int)(10), (int)(30), 0,(void *)font);
Text remainingTime = Text("60", (int)(75), (int)(30), 0,(void *)font);

Text startGame = Text("Press 'k' to start the game", (int)(win_width*0.4), (int)(win_height*0.5), 0,(void *)font);




