// Raul Verduzco
//  source file:
//  GAMEOVER screen and Weapon Feature
//
#include <cstdlib>
#include <cmath>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <ctime>
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
typedef float Vec[3];

class Global {
public:
       int weapon_display;
       Vec weapon_one;
       int max_bullets;
       
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
         ggprint10(&r2, 15, 0x000000 , "      Press Main Menu");
         ggprint10(&r2, 15, 0x000000 , "      Press \"R\" to restart the level!");
         ggprint10(&r2, 15, 0x000000 , "      Press \"Esc\" to Quit");

}

unsigned int manage_feature_weapons_state(unsigned int w ) {
    // generates weapons at random times for player
    w = w ^1;
    return w;
}


int show_feature_weapons(int xres, int yres, int weapon, int max_bullets, Vec ship_pos) {
     
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
    
    glColor3f(0.0f, 1.0f, 0.0f);
    Rect r;
    r.bot = 1;
    r.left = xres/2.0;
    r.center = 10;
    ggprint16(&r, 40, 0x0000ff00, "WEAPON FEATURE");

    int t_limit;
    int t_change =5;
    t_limit = time(NULL) + t_change;

    if (time(NULL) >= t_limit) {
          Rect r2;
       	  r2.bot = 200;
     	  r2.left = xres/2.0;
	  r2.center = 10;   
      	  ggprint16(&r2, 40, 0x0000ff00, "WEAPON FEATURE");
          return 0;
            // bullets = bullets +4;
            // manage_feature_weapons_state(1);
       }

    Gl.weapon_display = weapon;
    // first weapon
    if (Gl.weapon_display == 1) {
        Gl.weapon_one[0] = 40;// rand() % (xres - 20);
        Gl.weapon_one[1] =40; // rand() % (40);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

             glEnd();

       if ((ship_pos[0]+5) <= 40 && (ship_pos[0]-5) >= 40) {
	   if ((ship_pos[1]+5) <= 40 && (ship_pos[1]-5) >= 40) {
           Gl.weapon_one[0] = 40;// rand() % (xres - 20);
           Gl.weapon_one[1] =40; // rand() % (40);
           glColor3f(1.0, 1.0, 1.0);
           glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

             glEnd();
             Gl.max_bullets = max_bullets + 2;
	   }
       }
  
    }
    // Second weapon switch
    else if (Gl.weapon_display == 2) {
        Gl.weapon_one[0] = 280; //  rand() % (xres - 20);
        Gl.weapon_one[1] = 40; // rand() % (40);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

        glEnd();
    }
    // Third weapon switch
    else if(Gl.weapon_display == 3) {
        Gl.weapon_one[0] = 550; //  rand() % (xres - 20);
        Gl.weapon_one[1] = 40; // rand() % (40);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] -5);
             glVertex2i(Gl.weapon_one[0] - 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] +5);
             glVertex2i(Gl.weapon_one[0] + 5, Gl.weapon_one[1] -5);

        glEnd();
    }
    else {
	return 0;
    }

   return 0;
}






