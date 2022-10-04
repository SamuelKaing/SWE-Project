// Raul Verduzco
//  source file:
//  GAMEOVER screen
//
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"


unsigned int manage_gameover_state(unsigned int g)
{
    g = g ^ 1;
    return g;
}


void show_gameover_screen( int xres, int yres)
{
     Rect r2;
        r2.left = xres/2.7 ;
        r2.bot = yres/1.8;
        r2.center = 0;
        int xcent = xres / 2;
        int ycent = yres / 2;
        int w = 200;
        glColor3f(0.5f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
                glVertex2f( xcent-w, ycent-w);
                glVertex2f( xcent-w, ycent+w);
                glVertex2f( xcent+w, ycent+w);
                glVertex2f( xcent+w, ycent-w);
        glEnd();

        ggprint16(&r2, 40, 0x000000 , "xx_GAMEOVER_xx ");
        ggprint8b(&r2, 15, 0x000000 , "      Main Menu");
        ggprint8b(&r2, 15, 0x000000 , "        Quit");

}


