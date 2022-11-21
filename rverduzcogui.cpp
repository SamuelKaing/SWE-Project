// Raul Verduzco
//  source file:
//  GAMEOVER screen
//
#include <cstdlib>
#include <cmath>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                        (c)[1]=(a)[1]-(b)[1]; \

typedef float Vec[3];

class Global {
public:
       int weapon_display;
       Vec weapon_one;
       
} Gl;

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

unsigned int manage_feature_weapons_state(unsigned int w ) {
    // generates weapons at random times for player
    //
    w = w ^1;
    return w;
}


void show_feature_weapons(int xres, int yres, int weapon) {
     
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glEnable(GL_BLEND);
           // draw a border using a triangle strip
       glColor3f(0.0, 1.0, 0.0);
       glColor4f(0.0, 1.0, 0.0, 0.5);
       glBegin(GL_TRIANGLE_STRIP);
       int width2 = 20;
              glVertex2i(0, 0 );
              glVertex2i(0+width2, width2 );

              glVertex2i(0, yres);
              glVertex2i(0+width2, yres-width2 );

              glVertex2i(xres, yres );
              glVertex2i(xres - width2, yres -  width2 );

              glVertex2i(xres, 0);
              glVertex2i(xres-width2, width2 );

              glVertex2i( 0,0) ;
              glVertex2i(0 + width2, width2);

      glEnd();
      glDisable(GL_BLEND);
      
      Gl.weapon_display = weapon;

    if (Gl.weapon_display == 1) {
        Gl.weapon_one[0] = 40;// rand() % (xres - 20);
        Gl.weapon_one[1] =20; // rand() % (40);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

             glEnd();
    }
    else if (Gl.weapon_display == 2) {
        Gl.weapon_one[0] = 280; //  rand() % (xres - 20);
        Gl.weapon_one[1] = 20; // rand() % (40);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

             glEnd();
    }

     else { //(weapon_display == 3) {
        Gl.weapon_one[0] = 550; //  rand() % (xres - 20);
        Gl.weapon_one[1] = 20; // rand() % (40);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

             glEnd();
    }

}







