#ifndef TGALOAD_H
#define TGALOAD_H

// Some macros to shorten things up.
typedef unsigned char uchar;
typedef short int sint;

/**
 * This structure holds info about the TGA image before we load it into OpenGL.
 *
 * @author Tom Arnold
 */
typedef struct
{
	uchar depth;
	sint w, h;
	uchar* data;
} tga_data_t;

tga_data_t* tga_data_load(const char* fn);

#endif
