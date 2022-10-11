//Nathan Rodriguez
//
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
	
	glColor3f(1.0f, 1.0f, 0.0f);
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

