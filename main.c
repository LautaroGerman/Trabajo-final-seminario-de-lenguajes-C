#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "args-processor.h"

extern int errno;

/* Sample main program */

int main(int argc, char *argv[]) {
  process_args(argc, argv);
  exit(EXIT_SUCCESS);
}
