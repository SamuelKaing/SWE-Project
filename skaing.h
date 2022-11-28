#include "image.h"

typedef float Vec[3];

#ifndef _BULLET_H
#define _BULLET_H

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
extern void spawn_boss();
extern void init_boss(int xres, int yres, Texture boss_tex);
extern void boss_movement(int xres);
extern void boss_behavior(struct timespec &boss_bulletTimer);
extern void boss_bulletPhysics();
extern void boss_drawBullets();
extern int boss_hit(Bullet *b);
extern int boss_isAlive();
extern int player_hit(Vec ship_pos);
