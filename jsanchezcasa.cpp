//Juan Sanchez Casanova
//Individual Source file
#include "fonts.h"
#include <GL/glx.h>
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

