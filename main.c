#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "ppm-operations.h"

extern int errno;

/* Sample main program */

int main(int argc, const char * argv[]) {
  FILE *f, * op;
  char output_filename[1024];
  t_ppm p, p_op;
  if (argc != 2) error(1, 0, "An image file must be specified as argument");
  if ((f = fopen(argv[1], "rb")) == NULL) {
    error(1,errno, "Error opening file %s", argv[1]);
  }
  p = ppm_from_file(f);

  /*
   * A file named as input file will be created with -negative.ppm as suffix
   */
  strcat(strcpy(output_filename,argv[1]),"-negative.ppm");
  if ((op = fopen(output_filename, "wb")) == NULL) {
    error(1,errno, "Error opening file %s", output_filename);
  }
  p_op = ppm_operation_negative(p);
  ppm_save(p_op, op);
  /* Output file closed and PPM struct must free its memory */
  fclose(op);
  ppm_free(p_op);

  /* Input file closed and PPM struct must free its memory */
  ppm_free(p);
  fclose(f);
  exit(EXIT_SUCCESS);
}
