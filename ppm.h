#ifndef _PPM_H
#define _PPM_H

#include <stdio.h>

#define PPM_TYPE "P6"

/* RGB pixel */
typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} t_ppm_pixel;

/* A PPM type: has height, width, depth and pixels */
typedef struct {
  unsigned int height;
  unsigned int width;
  unsigned short depth;
  t_ppm_pixel * * pixels;
} t_ppm;

/* initializes a new PPM of height * width pixels and depth. Its 
 * pixels are all zeros (black)
 */
t_ppm ppm_create(unsigned long height, unsigned long width, unsigned short depth);

/* Reads a PPM from an existing file. Not all stabdard formats are supported*/
t_ppm ppm_from_file(FILE *);

/* Saves to file a PPM type object */
void ppm_save(t_ppm, FILE *);

/* Prints PPM header fileds */
void ppm_print_header(t_ppm p);

/* This function must be called after destroying a PPM object.
 * It frees all memory allocated for pixels \
 */
void ppm_free(t_ppm p);
#endif
