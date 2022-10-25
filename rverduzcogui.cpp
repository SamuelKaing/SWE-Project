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
        int width = 200;
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
                glVertex2f( xcent-width, ycent-width);
                glVertex2f( xcent-width, ycent+width);
                glVertex2f( xcent+width, ycent+width);
                glVertex2f( xcent+width, ycent-width);

        glEnd();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
           glEnable(GL_BLEND);
           // draw a border using a triangle strip
       glColor3f(1.0, 0.0, 0.0);
       glColor4f(1.0, 0.0, 0.0, 0.5);
       glBegin(GL_TRIANGLE_STRIP);
       int w = 200;
              glVertex2i(0, 0 );
          glVertex2i(0+w, w );

          glVertex2i(0, yres);
          glVertex2i(0+w, yres-w );

          glVertex2i(xres, yres );
                  glVertex2i(xres - w, yres -  w );

                  glVertex2i(xres, 0);
                  glVertex2i(xres-w, w );

          glVertex2i( 0,0) ;
          glVertex2i(0 + w, w);

          glEnd();
      glDisable(GL_BLEND);


        ggprint16(&r2, 40, 0x000000 , "xx_GAMEOVER_xx ");
        ggprint8b(&r2, 15, 0x000000 , "      Main Menu");
        ggprint8b(&r2, 15, 0x000000 , "        Quit");

}

void feature_weapons() {
    // generates weapons at random times for player
    //
}

