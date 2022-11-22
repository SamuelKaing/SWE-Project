//Juan Sanchez Casanova
//Individual Source file
#include "fonts.h"
#include <GL/glx.h>
typedef float Flt;
unsigned int manage_state(unsigned int s)
{
    s = s^1;
    return s;
}
void show_pause(int xres, int yres){
        Rect r3;
        r3.left = xres /2.3;
	r3.bot = yres/1.8;
        r3.center = 0;  
        int xcent = xres ;
        int ycent = yres ;
       
        
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.0f, 0.0f, 0.0f, 0.5);
        glBegin(GL_QUADS);
                
		glVertex2f( -xcent, -ycent);
                glVertex2f( -xcent,  ycent);
                glVertex2f(  xcent,  ycent);
                glVertex2f(  xcent, -ycent);  

	
	glEnd();
 	glDisable(GL_BLEND);       
        
        ggprint16(&r3, 40, 0x4e23838 , "PAUSE");
	ggprint10(&r3, 40, 0x4e23838 , "Press 'p' to resume");

}
void juanfeature(int xres, int yres){
    	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glEnable(GL_BLEND);

         glColor3f(1.0, 0.5, 0.5);
         glColor4f(1.0, 0.5, 0.5, 0.5);
         int w = 40;
         glBegin(GL_TRIANGLE_STRIP);
         
	 	glVertex2i(0, 0);
         	glVertex2i(0+w, w);

         	glVertex2i(0, yres);
         	glVertex2i(0+w, yres-w);

         	glVertex2i(xres, yres);
         	glVertex2i(xres-w, yres-w);

         	glVertex2i(xres, 0);
         	glVertex2i(xres-w, w);

         	glVertex2i(0,0);
         	glVertex2i(0+w, w);

         glEnd();
         glDisable(GL_BLEND);

	Rect r3;
        r3.left = xres/2.75;
	r3.bot = yres-20;
        r3.center = 0;  

	ggprint16(&r3, 40, 0xff0000, "COLLISION MODE");

	
}

int collision_mode(int radius, int ship_pos_y, int ship_pos_x, int ast_pos_x, int ast_pos_y ){
	
    	Flt test1,test2,dist;
	test1= ship_pos_y - ast_pos_y;
	test2= ship_pos_x - ast_pos_x;
	dist = (test1*test1 + test2*test2);
	if(dist < (radius*radius)){
	    return 1;
	}
	else 
	    return 0;

}

void win_screen(int xres, int yres){

   	Rect r3;
        r3.left = xres /2.3;
	r3.bot = yres/1.8;
        r3.center = 0;  
        int xcent = xres ;
        int ycent = yres ;
       
        
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.0f, 0.5f, 0.0f, 0.5);
        glBegin(GL_QUADS);
                
		glVertex2f( -xcent, -ycent);
                glVertex2f( -xcent,  ycent);
                glVertex2f(  xcent,  ycent);
                glVertex2f(  xcent, -ycent);  

	
	glEnd();
 	glDisable(GL_BLEND);       
        
        ggprint16(&r3, 40, 0x4e23838 , "CONGRATULATIONS");
	ggprint10(&r3, 40, 0x4e23838 , "You stopped the invaders!");
	ggprint10(&r3, 40, 0x4e23838 , "Press 'esc' to return back home!");



}

