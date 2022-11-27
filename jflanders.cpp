//Jacob Flanders
//my source file
//
#include <stdio.h>
#include <GL/glx.h>
#include "fonts.h"
#include "jflanders.h"
#include "skaing.h"
#include "image.h"
#include <stdlib.h>

typedef float Flt;
typedef float Vec[3];

#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0

Enemy se;

class Eship {
public:
	Vec pos;
	Vec dir;
	Vec vel;
	Vec acc;
	float angle;
	float color[3];
public:
	Eship() {
	    pos[0] = 0.0f;
	    pos[1] = 1.0f;
	    pos[2] = 0.0f;
	    VecZero(dir);
	    VecZero(vel);
	    VecZero(acc);
	    angle = 0.0;
	    color[0] = color[1] = color[2] = 1.0;
	}

};



class mode {
public:
    Eship eship;
} m;

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
    //Rect r3;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 0.0);
    glColor4f(1.0, 1.0, 0.0, 0.5);
    int w = 20;
    glPushMatrix();
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
        glPopMatrix();
        //glDisable(GL_BLEND);
    /*
	//Drawing the enemy ship
	glColor3fv(m.eship.color);
	glPushMatrix();
	glTranslatef(m.eship.pos[0], m.eship.pos[1], m.eship.pos[2]);
	glRotatef(m.eship.angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-12.0f, -10.0f);
	glVertex2f(  0.0f,  10.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  20.0f);
	glVertex2f( 12.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glPopMatrix();
    */
    //============================================
    
    glColor4f(1.0, 0.0, 0.0, 0.0);
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

    
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 0.0);
    glTranslatef(se.pos[0], se.pos[1], 0.0f);
    glBegin(GL_QUADS);
        glVertex2f( -se.width, -se.width);
        glVertex2f( -se.width, se.width);
        glVertex2f( se.width, se.width);
        glVertex2f( se.width, -se.width);
    glEnd();

    // Bind image to hitbox position
    glGenTextures(1, &se.enemy_tex.backText);
	int width = se.enemy_tex.img->w;
	int height = se.enemy_tex.img->h;
	glBindTexture(GL_TEXTURE_2D, se.enemy_tex.backText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //Correctly aligns texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
						GL_RGB, GL_UNSIGNED_BYTE, se.enemy_tex.img->data);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2i(-se.width, -se.width);
		glTexCoord2f(0, 0); glVertex2i(-se.width, se.width);
		glTexCoord2f(1, 0); glVertex2i(se.width, se.width);
		glTexCoord2f(1, 1); glVertex2i(se.width, -se.width);
	glEnd();
    glPopMatrix();
    
}

void make_enemy(int xres, int yres, Texture enemy_tex)
{
    se.enemy_tex = enemy_tex;
    se.width = 20;
    se.pos[0] = xres / 2;
    se.pos[1] = yres - (yres / 4);
    se.health = 5;
    se.movement = 0;
}

void enemy_movement(int xres) {
    if (se.pos[0] <= se.width)
        se.movement = 1;
    if (se.pos[0] >= xres - se.width)
        se.movement = 0;
    if (se.movement == 0)
        se.pos[0] -= 3;
    if (se.movement == 1)
        se.pos[0] += 3;
}

int enemy_hit(Bullet *b) {
    float xrange1 = se.pos[0] - se.width;
    float xrange2 = se.pos[0] + se.width;
    float yrange1 = se.pos[1] - se.width;
    float yrange2 = se.pos[1] + se.width;
    bool was_hit = false;

    if (b->pos[1] >= yrange1 && b->pos[1] <= yrange2)
        if (b->pos[0] >= xrange1 && b->pos[0] <= xrange2) {
            se.health--;
            was_hit = true;
        }
    return was_hit;
}

int enemy_isAlive() {
    if (se.health > 0)
        return 1;
    else
        return 0;
}
