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

// Timer setup
extern double timeDiff(struct timespec *start, struct timespec *end);
void clean_bullets();

const int MAX_BULLETS = 6;
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
        clean_bullets();
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
    int w = 200;
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
    ggprint8b(&r2, 30, 0x2e281, "Movement -- Arrow Keys");
    ggprint8b(&r2, 30, 0x2e281, "Shoot -- Spacebar");
    ggprint8b(&r2, 30, 0x2e281, "Pause -- p");
    ggprint8b(&r2, 30, 0x2e281, "Credits -- c");
    ggprint8b(&r2, 30, 0x2e281, "Restart Level -- r");
    ggprint8b(&r2, 30, 0x2e281, "Menu -- m");
    ggprint8b(&r2, 30, 0x2e281, "Collision Mode -- h");
    ggprint8b(&r2, 30, 0x2e281, "Boss Mode -- b");
    ggprint8b(&r2, 30, 0x2e281, "Jacob's Feature mode -- x");
    ggprint8b(&r2, 30, 0x2e281, "Level Cycle -- l");
    ggprint8b(&r2, 30, 0x2e281, "Weapon feature -- w");
 
}

void start_boss_rush(int xres) 
{
    int w = 30;
    Rect r2;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

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

    glDisable(GL_BLEND);
}

void spawn_boss() {
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

void init_boss(int xres, int yres, Texture boss_tex, int level) //need level
{
    boss.enemy_tex = boss_tex;
    boss.width = 40;
    boss.pos[0] = xres / 2;
    boss.pos[1] = yres - (yres / 4);
    boss.health = 20 + (10 * level);
    boss.movement = 0;
}

void boss_movement(int xres, int level) { //need level
    if (boss.pos[0] <= boss.width)
        boss.movement = 1;
    if (boss.pos[0] >= xres - boss.width)
        boss.movement = 0;

    if (boss.movement == 0)
        boss.pos[0] = boss.pos[0] - (2 + (0.6 * level));
    if (boss.movement == 1)
        boss.pos[0] = boss.pos[0] + (2 + (0.6 * level));
}

void boss_behavior(struct timespec &boss_bulletTimer, int level) { //need level
    //Every couple seconds, shoot bullet at player
    struct timespec bt;
    clock_gettime(CLOCK_REALTIME, &bt);
    double ts = timeDiff(&boss_bulletTimer, &bt);
    float velocity = -0.8 - (0.2 * level);

    //Copying method of bullet creation from asteroids.cpp
    //a little time between each bullet
    if (ts > (2.0 - (0.5 * level))) {
        clock_gettime(CLOCK_REALTIME, &boss_bulletTimer);
        if (nbullets < MAX_BULLETS) {
            Bullet *b = &barr[nbullets];
            b->pos[0] = boss.pos[0];
            b->pos[1] = boss.pos[1];
            //how fast bullet will move down
            b->vel[1] = velocity;
            ++nbullets;
        }
    }
}

void boss_bulletPhysics() {
    int i = 0;
	while (i < nbullets) {
        Bullet *b = &barr[i];
        b->pos[1] += b->vel[1];
        
        if (b->pos[1] < 0.0) {
			memcpy(&barr[i], &barr[nbullets-1], 
                                    sizeof(Bullet));
			nbullets--;
		}
        ++i;
    }
}

int boss_hit(Bullet *b) {
    //define range between x and y boss positions
    float xrange1 = boss.pos[0] - boss.width;
    float xrange2 = boss.pos[0] + boss.width;
    float yrange1 = boss.pos[1] - boss.width;
    float yrange2 = boss.pos[1] + boss.width;
    bool was_hit = false;

    if (b->pos[1] >= yrange1 && b->pos[1] <= yrange2)
        if (b->pos[0] >= xrange1 && b->pos[0] <= xrange2) {
            boss.health--;
            was_hit = true;
        }
    return was_hit;
}

int player_hit(Vec ship_pos) {
    float xrange1 = ship_pos[0] - 8;
    float xrange2 = ship_pos[0] + 8;
    float yrange1 = ship_pos[1] - 12;
    float yrange2 = ship_pos[1] + 12;
    int i = 0;
    
    while (i < nbullets) {
        Bullet *b = &barr[i];
        if (b->pos[1] >= yrange1 && b->pos[1] <= yrange2)
            if (b->pos[0] >= xrange1 && b->pos[0] <= xrange2) {
                memcpy(&barr[i], &barr[nbullets-1], 
                                    sizeof(Bullet));
			    nbullets--;
                return 1;
            }
        i++;
    }
    return 0;
}

void boss_drawBullets() {
    glDisable(GL_TEXTURE_2D);
    for (int i = 0; i < nbullets; i++) {
	Bullet *b = &barr[i];
	glColor3f(1.0, 0.4, 0.4);
	glBegin(GL_POINTS);
            glVertex2f(b->pos[0],      b->pos[1]);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]);
            glVertex2f(b->pos[0],      b->pos[1]-1.0f);
            glVertex2f(b->pos[0],      b->pos[1]+1.0f);
            glColor3f(1.0, 0.4, 0.4);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
            glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
            glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
	glEnd();
	}
    glEnable(GL_TEXTURE_2D);
}

int boss_isAlive() {
    if (boss.health > 0)
        return 1;
    else {
        clean_bullets();
        return 0;
    }
}

void clean_bullets() {
    int i = 0;
    while (nbullets > 0) {
        memcpy(&barr[i], &barr[nbullets-1], 
                                sizeof(Bullet));
        nbullets--;
        ++i;
    }
}
