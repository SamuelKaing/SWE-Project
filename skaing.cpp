//author: Samuel Kaing
//
#include <stdio.h>
#include <GL/glx.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string> 
#include "fonts.h"
#include "skaing.h"
#include "image.h"

//-----------------------------------------------------------------------------
// Timer setup
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------
const int MAX_BULLETS = 5;

Bullet *barr = new Bullet[MAX_BULLETS];
int nbullets = 0;
Enemy boss;

Enemy::Enemy(float wid, float xpos, float ypos, int move) {
    width = wid;
    pos[0] = xpos;
    pos[1] = ypos;
    movement = move;
}

unsigned int manage_help_state(unsigned int s)
{
    s = !s;
    return s;
}

unsigned int boss_rush_state(unsigned int s)
{
    s = !s;
    //Delete bullets when toggled off
    if (s == 0) {
        int i = 0;
        while (nbullets > 0) {
			memcpy(&barr[i], &barr[nbullets-1], 
                                    sizeof(Bullet));
            std::cout << "bullet deleted" << std::endl;
			nbullets--;
            ++i;
        }
    }
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

void start_boss_rush(int xres) 
{
    int w = 30;
    Rect r2;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    //Draws Mode Indicator
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

    r2.left = (xres / 2) - (w / 4);
    r2.bot = 0 + (w / 5);
    r2.center = 0;
    glColor3f(1.0, 0.0, 1.0);
    ggprint16(&r2, 40, 0x2e281, "Boss Mode");

    //Boss hitbox
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 0.0);
    glTranslatef(boss.pos[0], boss.pos[1], 0.0f);
    glBegin(GL_QUADS);
        glVertex2f( -boss.width, -boss.width);
        glVertex2f( -boss.width, boss.width);
        glVertex2f( boss.width, boss.width);
        glVertex2f( boss.width, -boss.width);
    glEnd();
    
    // Bind image to hitbox position
    glGenTextures(1, &boss.enemy_tex.backText);
	int width = boss.enemy_tex.img->w;
	int height = boss.enemy_tex.img->h;
	glBindTexture(GL_TEXTURE_2D, boss.enemy_tex.backText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //Correctly aligns texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
						GL_RGB, GL_UNSIGNED_BYTE, boss.enemy_tex.img->data);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2i(-boss.width, -boss.width);
		glTexCoord2f(0, 0); glVertex2i(-boss.width, boss.width);
		glTexCoord2f(1, 0); glVertex2i(boss.width, boss.width);
		glTexCoord2f(1, 1); glVertex2i(boss.width, -boss.width);
	glEnd();
    glPopMatrix();
}

void make_boss(int xres, int yres, Texture boss_tex)
{
    boss.enemy_tex = boss_tex;
    boss.width = 40;
    boss.pos[0] = xres / 2;
    boss.pos[1] = yres - (yres / 4);
    boss.movement = 0;
}

void move_boss(int xres) {
    if (boss.pos[0] <= boss.width)
        boss.movement = 1;
    if (boss.pos[0] >= xres - boss.width)
        boss.movement = 0;

    if (boss.movement == 0)
        boss.pos[0] -= 3;
    if (boss.movement == 1)
        boss.pos[0] += 3;
}

void behavior(struct timespec &boss_bulletTimer) {
    //Every couple seconds, shoot bullet at player
    struct timespec bt;
    clock_gettime(CLOCK_REALTIME, &bt);
    double ts = timeDiff(&boss_bulletTimer, &bt);
    //std::cout << ts << std::endl;

    //Copying method of bullet creation from asteroids.cpp
    //a little time between each bullet
    if (ts > 2.0) {
        clock_gettime(CLOCK_REALTIME, &boss_bulletTimer);
        if (nbullets < MAX_BULLETS) {
            Bullet *b = &barr[nbullets];
            b->pos[0] = boss.pos[0];
            b->pos[1] = boss.pos[1];
            //how fast bullet will move down
            b->vel[1] = -0.8;
            b->color[0] = 1.0f;
            b->color[1] = 1.0f;
            b->color[2] = 1.0f;
            ++nbullets;
        }
    }
}

void boss_bulletPhysics() {
    int i = 0;
	while (i < nbullets) {
        Bullet *b = &barr[i];
        b->pos[1] += b->vel[1];
        //std::cout << "Bullet: " << std::to_string(i) << std::endl;
        //std::cout << b->pos[1] << std::endl;
        
        if (b->pos[1] < 0.0) {
            std::cout << "bullet deleted" << std::endl;
			memcpy(&barr[i], &barr[nbullets-1], 
                                    sizeof(Bullet));
			nbullets--;
		}
        ++i;
    }
}

void boss_drawBullets() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    for (int i=0; i < nbullets; i++) {
		Bullet *b = &barr[i];
		//bglColor3f(1.0, 1.0, 1.0);
        glColor3fv(b->color);
		glBegin(GL_POINTS);
            glVertex2f(b->pos[0],      b->pos[1]);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]);
            glVertex2f(b->pos[0],      b->pos[1]-1.0f);
            glVertex2f(b->pos[0],      b->pos[1]+1.0f);
            glColor3f(0.8, 0.8, 0.8);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
		glEnd();
	}
}