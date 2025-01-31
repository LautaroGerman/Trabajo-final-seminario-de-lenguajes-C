#include "ppm.h"
#include "utils.h"

t_ppm ppm_operation_rotate90(t_ppm p){
  unsigned int new_width = p.height;
  unsigned int new_height = p.width;
  unsigned int new_depth = p.depth;
  t_ppm rotate_ppm = ppm_create(new_height, new_width, new_depth);

  for (int i = 0; i < p.height; i++) {
    for (int j = 0; j < p.width; j++) {
      rotate_ppm.pixels[p.width-j-1][i] = p.pixels[i][j];
    }
  }

  return rotate_ppm;
}

t_ppm ppm_operation_flip_horizontal(t_ppm p){
  t_ppm flip_ppm = ppm_create(p.height, p.width, p.depth);
  for (int i = 0; i < p.height; i++) {
    for (int j = 0; j < p.width; j++) {
      flip_ppm.pixels[i][j] = p.pixels[i][p.width-j-1];
    }
  }
  return flip_ppm;
}

t_ppm ppm_operation_flip_vertical(t_ppm p){
  t_ppm flip_ppm = ppm_create(p.height, p.width, p.depth);
  for (int i = 0; i < p.height; i++) {
    for (int j = 0; j < p.width; j++) {
      flip_ppm.pixels[i][j] = p.pixels[p.height-i-1][j];
    }
  }
  return flip_ppm;
}


t_ppm_pixel blur_pixel(t_ppm p, int row, int col, unsigned char ratio){
  t_ppm_pixel new_pixel = {0, 0, 0};
  int count = 0;
  for (int i = max(row-ratio, 0); i <= min(row+ratio, (int) p.height-1); i++) {
    for (int j = max(col-ratio, 0); j <= min(col+ratio, (int) p.width-1); j++) {
      new_pixel.red += p.pixels[i][j].red;
      new_pixel.green += p.pixels[i][j].green;
      new_pixel.blue += p.pixels[i][j].blue;
      count++;
    }
  }

  new_pixel.red /= count;
  new_pixel.green /= count;
  new_pixel.blue /= count;

  return new_pixel;
}

t_ppm ppm_operation_blur(t_ppm p, unsigned char ratio){
  t_ppm blur_ppm = ppm_create(p.height, p.width, p.depth);
  for (int i = 0; i < p.height; i++) {
    for (int j = 0; j < p.width; j++) {
      blur_ppm.pixels[i][j] = blur_pixel(p, i, j, ratio);
    }
  }
  return blur_ppm;
}

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

