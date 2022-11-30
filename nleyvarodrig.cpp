//Nathan Rodriguez

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include "fonts.h"
#include "image.h"


Texture::~Texture() { }
Texture::Texture() { }

void show_credits(Texture t, int xres, int yres);

extern class Image image;

Image::~Image() { delete [] data;}

Image::Image(const char *fname){
    if (strlen(fname) == 0)
	return;
    char name[40];
    strcpy(name, fname);
    int slen = strlen(name);
    name[slen-4] = '\0';
    char ppmname[80];
    sprintf(ppmname, "%s.ppm", name);
    char ts[100];
    sprintf(ts, "convert %s %s", fname, ppmname);
    system(ts);
    FILE *fpi = fopen(ppmname, "r");
    if (fpi) {
	char line[200];
	fgets(line, 200, fpi);
	fgets(line, 200, fpi);
	while (line[0] == '#' || strlen(line) < 2)
	    fgets(line, 200, fpi);
	sscanf(line, "%i %i", &w, &h);
	fgets(line, 200, fpi);
	int n = w * h * 3;
	data = new unsigned char[n];
	for (int i=0; i<n; i++)
	    data[i] = fgetc(fpi);
	fclose(fpi);
    } else {
	printf("ERROR opening image: %s\n", ppmname);
	exit(0);
    }
    unlink(ppmname);
}

void show_credits(Texture t, int xres, int yres) 
{
	int imgw = 50;
    Rect r2;
	r2.left = xres /2 - imgw;
    r2.bot = yres/2;
	r2.center = 0;	
    	int xcent = xres / 2;
	int ycent = yres / 2;
	int w = 200;
	int iycent = ycent + 2*imgw;
	
	glColor3f(.5f, .58f, .20f);
	glBegin(GL_QUADS);
		glVertex2f( xcent-w, ycent-w);
		glVertex2f( xcent-w, ycent+w);
		glVertex2f( xcent+w, ycent+w);
		glVertex2f( xcent+w, ycent-w);	
	glEnd();	
	
	//t.img = &image[0];
	glGenTextures(1, &t.backText);
	int width = t.img->w;
	int height = t.img->h;
	glBindTexture(GL_TEXTURE_2D, t.backText);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
						GL_RGB, GL_UNSIGNED_BYTE, t.img->data);
	
	glColor3f(255.0, 255.0, 0);
	//glBindTexture(GL_TEXTURE_2D, gl.t.backText);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2i(xcent-imgw, iycent-imgw);
		glTexCoord2f(0.0, 0.0); glVertex2i(xcent-imgw, iycent+imgw);
		glTexCoord2f(1.0, 0.0); glVertex2i(xcent+imgw,iycent+imgw);
		glTexCoord2f(1.0, 1.0); glVertex2i(xcent+imgw,iycent-imgw);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	ggprint8b(&r2, 40, 0x000000 , "Made by: ");
	ggprint8b(&r2, 15, 0x000000 , "Nathan Rodriguez");
	ggprint8b(&r2, 15, 0x000000 , "Jacob Flanders");
	ggprint8b(&r2, 15, 0x000000 , "Samuel Kaing");
	ggprint8b(&r2, 15, 0x000000 , "Juan Sanchez");
	ggprint8b(&r2, 15, 0x000000 , "Raul Verduzco");
}


void menu(int xres, int yres){ 
    Rect resume, quit, help;
	
	int w = 200;
	int heightW = 35;
	int widthW = 100;
   	int xcent = xres / 2;
    int ycent = yres / 2;

	int quityCent = ycent / 2;
	int resyCent =  ycent * 1.35;
	int helpyCent = ycent / 1.1;

	resume.left = xcent;
	resume.bot = resyCent;
	resume.center = 1;

	help.left = xcent;
	help.bot = helpyCent;
	help.center = 1;

	quit.left = xcent;
	quit.bot = quityCent;
	quit.center = 1;

	glColor3f(.240f, .190f, .74f);
	glBegin(GL_QUADS);
		glVertex2f( xcent-w, ycent-w);
		glVertex2f( xcent-w, ycent+w);
		glVertex2f( xcent+w, ycent+w);
		glVertex2f( xcent+w, ycent-w);	
	glEnd();	

	glColor3f(.64f, .55f, .55f);
	glBegin(GL_QUADS);
		glVertex2f( xcent-widthW, resyCent-heightW);
		glVertex2f( xcent-widthW, resyCent+heightW);
		glVertex2f( xcent+widthW, resyCent+heightW);
		glVertex2f( xcent+widthW, resyCent-heightW);
	glEnd();	
	glColor3i(1, 1, 1);
	ggprint16(&resume, 10, 0x000000, "Resume");	
	
	glColor3f(.64f, .55f, .55f);
	glBegin(GL_QUADS);
		glVertex2f( xcent-widthW, helpyCent-heightW);
		glVertex2f( xcent-widthW, helpyCent+heightW);
		glVertex2f( xcent+widthW, helpyCent+heightW);
		glVertex2f( xcent+widthW, helpyCent-heightW);
	glEnd();	
	glColor3i(1, 1, 1);
	ggprint16(&help, 20, 0x000000, "Controls");	
	
	glColor3f(.64f, .55f, .55f);
	glBegin(GL_QUADS);
		glVertex2f( xcent-widthW, quityCent-heightW);
		glVertex2f( xcent-widthW, quityCent+heightW);
		glVertex2f( xcent+widthW, quityCent+heightW);
		glVertex2f( xcent+widthW, quityCent-heightW);
	glEnd();	
	glColor3i(1, 1 , 1);
	ggprint16(&quit, 0, 0x000000, "Quit");	
		
}

void ship_movement(int xres, int yres){
    	glColor3f(0.0f, 0.0f, 1.0f);
    	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, yres);
		glVertex2f(xres, yres);
		glVertex2f(xres, 0);
    	glEnd();
}
/*
void replenishAsteroids(Game *g, int nasteroids, int level){	
    for (int j=0; j<ceil(level * 1.25) + 10; j++) {
	Asteroid *a = new Asteroid;
	a->nverts = 8;
	a->radius = rnd()*80.0 + 40.0;
	Flt r2 = a->radius / 2.0;
	Flt angle = 0.0f;
	Flt inc = (PI * 2.0) / (Flt)a->nverts;
	for (int i=0; i<a->nverts; i++) {
	    a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
	    a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
	    angle += inc;
	}
	a->pos[0] = (Flt)(rand() % gl.xres);
	a->pos[1] = (Flt)(rand() % gl.yres);
	a->pos[2] = 0.0f;
	a->angle = 0.0;
	a->rotate = rnd() * 4.0 - 2.0;
	a->color[0] = 0.8;
	a->color[1] = 0.8;
	a->color[2] = 0.7;
	a->vel[0] = (Flt)(rnd()*2.0-1.0); //(Flt)(rnd()*2.0-1.0
	a->vel[1] = (Flt)(rnd()*2.0-1.0);
	//std::cout << "asteroid" << std::endl;
	//add to front of linked list
	a->next = ahead;
	if (ahead != NULL)
	    ahead->prev = a;
	ahead = a;
	++nasteroids;
    }
    clock_gettime(CLOCK_REALTIME, &bulletTimer);
}*/
