//Nathan Rodriguez
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include "image.h"

Texture::~Texture() { }
Texture::Texture() { }


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




