#include "ppm.h"

/*
t_ppm ppm_operation_rotate90(t_ppm p){
}

t_ppm ppm_operation_flip_horizontal(t_ppm p){
}

t_ppm ppm_operation_flip_vertical(t_ppm p){
}

t_ppm ppm_operation_blur(t_ppm p, unsigned char ratio){
}
*/

void ppm_invert_colours(t_ppm_pixel *p){
  p->red=255-p->red;
  p->green=255-p->green;
  p->blue=255-p->blue;
}

t_ppm ppm_operation_negative(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][col];
    ppm_invert_colours(&new.pixels[row][col]);
  }
  return new;
}

