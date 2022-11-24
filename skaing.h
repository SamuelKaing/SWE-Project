#include "image.h"

#ifndef _BOSS_H
#define _BOSS_H

class Enemy 
{
    public:
        Texture enemy_tex;
        float w;
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
extern void make_boss(int xres, int yres, Texture boss_tex);
extern void behavior(struct timespec &boss_bulletTimer);
