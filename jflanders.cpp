//Jacob Flanders
//my source file
//
#include <stdio.h>
#include <GL/glx.h>
#include "fonts.h"
#include "jflanders.h"
#include "skaing.h"

typedef float Flt;
typedef float Vec[3];

#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0



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
        glDisable(GL_BLEND);

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


}



