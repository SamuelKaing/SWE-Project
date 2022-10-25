//Jacob Flanders
//my source file
//
#include <stdio.h>
#include <GL/glx.h>
#include "fonts.h"


unsigned int manage_game(unsigned int z)
{
    z = z ^ 1;
    return z;
}

unsigned int manage_mode(unsigned int v)
{
    v = v ^ 1;
    return v;
}

void tester_mode(int xres, int yres)
{
    int xcent = xres;
    int ycent = yres;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor3f(1.0, 1.0, 0.0);
    glColor4f(1.0, 1.0, 0.0, 0.5);
    int w = 20;
     glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0, 0);
        glVertex2i(0+w, w);

        glVertex2i(0, ycent);
        glVertex2i(0+w, ycent-w);

        glVertex2i(xcent,ycent);
        glVertex2i(xcent-w, ycent-w);

        glVertex2i(xcent, 0);
        glVertex2i(xcent-w,w);

        glVertex2i(0,0);
        glVertex2i(0+w,w);
        glEnd();
        glDisable(GL_BLEND);


}


