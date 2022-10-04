//Author: Nathan Rodriguez
//
#include <GL/glx.h>

#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image{
public: 
    int w, h;
    unsigned char *data;
    ~Image();
    Image(const char *fname);
};

class Texture{
    public:
	Image *img;
	GLuint backText;
	~Texture();
	Texture();

};
#endif
