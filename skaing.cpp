//author: Samuel Kaing
//
#include <stdio.h>
#include <GL/glx.h>
#include <cstring>
#include "fonts.h"
#include "skaing.h"
#include "image.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
//Fix mouse movement controls
//Import image to screen

class Boss {
    public:
        Texture boss_tex;
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

    w -= 2;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    	glVertex2f( xcent-w, ycent-w);
    	glVertex2f( xcent-w, ycent+w);
    	glVertex2f( xcent+w, ycent+w);
    	glVertex2f( xcent+w, ycent-w);
    glEnd();

    r2.left = (xres / 2) - (w / 3);
    r2.bot = (yres / 2) + (w - 25);

    ggprint16(&r2, 40, 0x2E281, "Controls");
    ggprint10(&r2, 40, 0x2e281, "Movement -- Arrow Keys");
    ggprint10(&r2, 40, 0x2e281, "Shoot -- Spacebar");
    ggprint10(&r2, 40, 0x2e281, "Pause -- p");
    ggprint10(&r2, 40, 0x2e281, "Credits -- c");
    ggprint10(&r2, 40, 0x2e281, "Collision Mode -- h");
    ggprint10(&r2, 40, 0x2e281, "Boss Mode -- b");
    ggprint10(&r2, 40, 0x2e281, "Jacob's Feature mode -- x");
}

void start_boss_rush(int xres, int yres, Texture boss_tex) 
{
    int w = 30;
    //int xcent = xres/2;
    //int ycent = yres/2;
    Rect r2;
    r2.left = (xres / 2) - (w / 4);
    r2.bot = 0 + (w / 5);
    r2.center = 0;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    //Drawing Mode Indicator
    glColor4f(1.0, 0.0, 0.0, 0.8);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0, 0);
        glVertex2i(0+w, w);
        glVertex2i(xres, 0);
        glVertex2i(xres-w, w);
    glEnd();
    glPopMatrix();

    w -= 2;
    glColor4f(0.0, 0.0, 0.0, 0.6);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0, 0);
        glVertex2i(0+w, w);
        glVertex2i(xres, 0);
        glVertex2i(xres-w, w);
    glEnd();
    glPopMatrix();

    glColor3f(1.0, 0.0, 1.0);
    ggprint16(&r2, 40, 0x2e281, "Boss Mode");

    //Boss hitbox
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 0.0);
    glTranslatef(boss.pos[0], boss.pos[1], 0.0f);
    glBegin(GL_QUADS);
        glVertex2f( -boss.w, -boss.w);
        glVertex2f( -boss.w, boss.w);
        glVertex2f( boss.w, boss.w);
        glVertex2f( boss.w, -boss.w);
    glEnd();

    
    // Make image; Bind it to hitbox position
    glGenTextures(1, &boss_tex.backText);
	int width = boss_tex.img->w;
	int height = boss_tex.img->h;
	glBindTexture(GL_TEXTURE_2D, boss_tex.backText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //Correctly aligns texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
						GL_RGB, GL_UNSIGNED_BYTE, boss_tex.img->data);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2i(-boss.w, -boss.w);
		glTexCoord2f(0, 0); glVertex2i(-boss.w, boss.w);
		glTexCoord2f(1, 0); glVertex2i(boss.w, boss.w);
		glTexCoord2f(1, 1); glVertex2i(boss.w, -boss.w);
	glEnd();
    glPopMatrix();


    //boss movement
    if (boss.pos[0] <= boss.w)
        boss.movement = 1;
    if (boss.pos[0] >= xres - boss.w)
        boss.movement = 0;

    if (boss.movement == 0)
        boss.pos[0] -= 3;
    if (boss.movement == 1)
        boss.pos[0] += 3;
}

void make_boss(int xres, int yres)
{
    boss.w = 40;
    boss.pos[0] = xres / 2;
    boss.pos[1] = yres - (yres / 4);
    boss.movement = 0;
}
