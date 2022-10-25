//author: Samuel Kaing
//
#include <stdio.h>
#include <GL/glx.h>
#include "fonts.h"
#include "skaing.h"

//Fix mouse movement controls
//Create transparent hitboxes
//Import image to screen

class Boss {
    public:
        float w;
        float pos[2];
        int movement;
        Boss() {}
        Boss(float wid, float pos_x, float pos_y) {
            w = wid;
            pos[0] = pos_x;
            pos[1] = pos_y;
        }
} boss;

void show_sam()
{
    printf("skaing\n");
}

unsigned int manage_help_state(unsigned int s)
{
    s = !s;
    return s;
}

unsigned int boss_rush_state(unsigned int s)
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

void start_boss_rush(int xres, int yres) 
{
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 0.2);
    glTranslatef(boss.pos[0], boss.pos[1], 0.0f);
    glBegin(GL_QUADS);
        glVertex2f( -boss.w, -boss.w);
        glVertex2f( -boss.w, boss.w);
        glVertex2f( boss.w, boss.w);
        glVertex2f( boss.w, -boss.w);
    glEnd();
    glPopMatrix();

    if (boss.pos[0] <= 0)
        boss.movement = 1;
    if (boss.pos[0] >= xres)
        boss.movement = 0;

    //move to left edge
    if (boss.movement == 0) {
        boss.pos[0] -= 3;
    }
    if (boss.movement == 1) {
        boss.pos[0] += 3;
    }
}

void make_boss(int xres, int yres)
{
    boss.w = 20;
    boss.pos[0] = xres / 2;
    boss.pos[1] = yres - (yres / 4);
    boss.movement = 0;
}