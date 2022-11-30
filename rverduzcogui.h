// Raul Verduzco 
// Header file for gameover screen
//
//
extern unsigned int manage_gameover_state(unsigned int g);

extern void show_gameover_screen(int xres, int yres);

extern unsigned int manage_feature_weapons_state(unsigned int w);

extern void show_feature_weapons(int xres, int yres, int weapon, int max_bullets, Vec ship_pos);

extern int weapon_switch(Vec ship_pos);

extern int weapon_switch2(Vec ship_pos);

//extern int weapon_switch3(Vec ship_pos);
