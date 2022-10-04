//author: Samuel Kaing
//
#include <stdio.h>
#include <GL/glx.h>
#include "fonts.h"

void show_sam()
{
	printf("skaing\n");
}

unsigned int manage_help_state(unsigned int s)
{
	s = !s;
	return s;
}

void show_controls(int xres, int yres)
{
    Rect r2;
    r2.left = (xres / 2);
   	r2.bot = yres / 1.8;
    r2.center = 0;

	//Outline box
	int xcent = xres / 2;
    int ycent = yres / 2;
    int w = 180;
    glColor3f(0.9f, 1.0f, 1.07f);
    glBegin(GL_QUADS);
    	glVertex2f( xcent-w, ycent-w);
    	glVertex2f( xcent-w, ycent+w);
    	glVertex2f( xcent+w, ycent+w);
    	glVertex2f( xcent+w, ycent-w);
	glEnd();

    w = w - 2;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    	glVertex2f( xcent-w, ycent-w);
    	glVertex2f( xcent-w, ycent+w);
    	glVertex2f( xcent+w, ycent+w);
    	glVertex2f( xcent+w, ycent-w);
	glEnd();

	r2.left = (xres / 2) - (w / 4);
	r2.bot = (yres / 2) + (w / 3);

	ggprint16(&r2, 40, 0x2E281, "Controls");
	ggprint10(&r2, 40, 0x2e281, "Movement -- Arrow Keys");
	ggprint10(&r2, 40, 0x2e281, "Shoot -- Spacebar");
	ggprint10(&r2, 40, 0x2e281, "Pause -- p");
	ggprint10(&r2, 40, 0x2e281, "Credits -- c");
}
