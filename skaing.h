#include "image.h"

#ifndef _BULLET_H
#define _BULLET_H

typedef float Vec[3];
class Bullet {
public:
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
public:
	Bullet() { }
};

#endif

#ifndef _BOSS_H
#define _BOSS_H

class Enemy 
{
    public:
        Texture enemy_tex;
        Bullet *barr;
        float width;
        float pos[2];
        int movement;
        int health;
        Enemy() {}
        Enemy(float wid, float xpos, float ypos, int move);
};

#endif



extern unsigned int manage_help_state(unsigned int s);
extern void show_controls(int xres, int yres);
extern unsigned int boss_rush_state(unsigned int s);
extern void start_boss_rush(int xres);
extern void make_boss(int xres, int yres, Texture boss_tex);
extern void move_boss(int xres);
extern void behavior(struct timespec &boss_bulletTimer);
extern void boss_bulletPhysics();
extern void boss_drawBullets();
