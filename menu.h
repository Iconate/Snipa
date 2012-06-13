#define win_width 1024
#define win_height 768
//GLUT_BITMAP_8_BY_13

int menuSelection = 0, menuItems = 2; // 0 is included as the number of menuItems
bool selection = false, sound = true;
int diffselect = 0;
bool go = false;

using namespace std;


void menuCheck(bool selection, int menuSelection) 
{
     if (!selection && menuSelection == 0){
         start.draw(1,0,0);
         options.draw(0,1,0);
         exittext.draw(0,1,0);
         
                    
     }
     else if (!selection && menuSelection == 1){
           start.draw(0,1,0);
         options.draw(1,0,0);
         exittext.draw(0,2,0);
      
         
     }
     else if (!selection && menuSelection == 2){
           
        start.draw(0,1,0);
        options.draw(0,1,0);
        exittext.draw(1,0,0);
         
     }
     else if (selection && menuSelection == 0) {      //Start Game
        
        if(diffselect == 0){
            easy.draw(1,0,0);
            medium.draw(0,1,0);
            hard.draw(0,1,0);
            if(go){
                inGame = true;
                 playSelectBeep();
                 stopTheme();
                 difficulty = 0;
                 rifle.setAmmo(50);
                 fintime = 180;
            }
        }else if (diffselect == 1){
            easy.draw(0,1,0);
            medium.draw(1,0,0);
            hard.draw(0,1,0);
            if(go){
                inGame = true;
                 playSelectBeep();
                 stopTheme();
                 difficulty = 1;
                 rifle.setAmmo(30);
                fintime = 120;
            }
        }else{
            easy.draw(0,1,0);
            medium.draw(0,1,0);
            hard.draw(1,0,0);
            if(go){
                inGame = true;
                 playSelectBeep();
                 stopTheme();
                 difficulty = 2;
                 rifle.setAmmo(10);
                fintime = 60;
                 
            }
        }
         
        
     }
     else if (selection && menuSelection == 1) { //options
        optionsTitle.draw(0,1,0);
        music.draw(0,1,0);
        back.draw(0,1,0); 
        
    	 if(sound){
             on.draw(1,0,0);
             off.draw(0,1,0);
          }
          else{
             on.draw(0,1,0);
             off.draw(1,0,0);
          }  
         
     }else {
         exit(0);
     } 
   

}

