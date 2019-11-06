#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

t_ppm ppm_create(unsigned long height, unsigned long width, unsigned short depth) {
  t_ppm new;
  unsigned int row, col;
  new.height = height;
  new.width = width;
  new.depth = depth;
  new.pixels = malloc(sizeof(t_ppm_pixel *) * new.height);
  for(row=0; row < new.height; row++){
    new.pixels[row] = malloc(sizeof(t_ppm_pixel) * new.width);
    for(col=0; col < new.width ; col++) {
      new.pixels[row][col].red = new.pixels[row][col].green = new.pixels[row][col].blue = 0;
    }
  }
  return new;
}

void ppm_read_whitespaces_or_comment(FILE *f) {
  int c;
  int finish=0;
  while (!finish && (c=fgetc(f)) != EOF){
    while ((c=fgetc(f)) != EOF && (c ==32 || c == 9 || c == 10 || c == 13));
    if ( c != EOF  && c == '#') {
      while ( (c=fgetc(f)) != EOF && ( c != 13 && c != 10 ));
      ungetc(c, f);
    }
    else finish = 1;
  }
  if (c!=EOF) ungetc(c, f);
}

void ppm_validate_header(t_ppm p) {
  if ( p.depth >= 256 ) error(1, 0, "Error in header: depth can be %d. Maximum allowed is 256", p.depth);
}


t_ppm ppm_from_file(FILE * f) {
  t_ppm new;
  unsigned int row, col;
  char ppm_type[]= {0,0,0};
  if ( fread(ppm_type, sizeof(char), strlen(PPM_TYPE), f) != strlen(PPM_TYPE) ) error(1,0,"Error reading file magic number");
  if ( strcasecmp(ppm_type, PPM_TYPE) ) error(1, 0, "Error reading file: expected magic %s was %s", PPM_TYPE, ppm_type);
  ppm_read_whitespaces_or_comment(f);
  if ( fscanf(f, "%d", &new.width) != 1 ) error(1, 0, "Error reading file: image width can't be read");
  ppm_read_whitespaces_or_comment(f);
  if ( fscanf(f, "%d", &new.height) != 1 ) error(1, 0, "Error reading file: image height can't be read");
  ppm_read_whitespaces_or_comment(f);
  if ( fscanf(f, "%hd", &new.depth) != 1 ) error(1, 0, "Error reading file: image depth can't be read");
  ppm_read_whitespaces_or_comment(f);
  ppm_validate_header(new);
  new.pixels = malloc(sizeof(t_ppm_pixel *) * new.height);
  for(row=0; row < new.height; row++) {
    new.pixels[row] = malloc(sizeof(t_ppm_pixel) * new.width);
    for(col=0; col < new.width ; col++){
      fread(&new.pixels[row][col].red, sizeof(char), 1, f);
      fread(&new.pixels[row][col].green, sizeof(char), 1, f);
      fread(&new.pixels[row][col].blue, sizeof(char), 1, f);
    }
  }
  return new;
}

void ppm_save(t_ppm p, FILE * f) {
  unsigned int row,col; 
  if ( fprintf(f, "%s\n%d %d\n%d\n",
        PPM_TYPE, 
        p.width,
        p.height,
        p.depth) <=0 ) error(1, 0, "Error writing PPM header");
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    fwrite(&p.pixels[row][col].red, sizeof(char), 1, f);
    fwrite(&p.pixels[row][col].green, sizeof(char), 1, f);
    fwrite(&p.pixels[row][col].blue, sizeof(char), 1, f);
  }
}

void ppm_free(t_ppm p) {
  unsigned int row; 
  for(row=0; row < p.height; row++) free(p.pixels[row]);
  free(p.pixels);
}

void ppm_print_header(t_ppm p) {
  printf("Width  : %d\n", p.width);
  printf("Height : %d\n", p.height);
  printf("Depth  : %d\n", p.depth);
}
