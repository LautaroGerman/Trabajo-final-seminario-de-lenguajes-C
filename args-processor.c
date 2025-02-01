#include "args-processor.h"
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ppm-operations.h"
#include "ppm.h"

#define OPT_STRING ":i:o:b:nrhv?"
#define HELP_TEXT \
  "Usage: program_name [options]\n\n" \
  "Available options:\n" \
  "-i input.ppm     : Input file (required)\n" \
  "-o output.ppm    : Output file (required)\n" \
  "-n               : Compute the negative of the image\n" \
  "-r               : Rotate the image 90 degrees\n" \
  "-h               : Horizontal mirror of the image\n" \
  "-v               : Vertical mirror of the image\n" \
  "-b NUM           : Apply a blur with radius NUM\n" \
  "-?               : Show this help message"

void free_resources(FILE *in, FILE *out, t_ppm *img) {
  if (in != NULL) {
    fclose(in);
  }
  if (out != NULL) {
    fclose(out);
  }
  ppm_free(*img);
}

void handle_error(FILE *in, FILE *out, t_ppm *img, const char *format, ...) {
  va_list args;
  va_start(args, format);

  free_resources(in, out, img);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n%s\n", HELP_TEXT);

  va_end(args);
  exit(1);
}

void check_input_file(FILE *in, FILE *out, t_ppm *img) {
  if (in == NULL) {
    handle_error(in, out, img, "Must specify an input file");
  }
}

void check_output_file(FILE *out, FILE *in, t_ppm *img) {
  if (out == NULL) {
    handle_error(in, out, img, "Must specify an output file");
  }
}

/* Free img1 and assign img2 to it */
void free_and_assign_ppm(t_ppm *img1, t_ppm *img2) {
  ppm_free(*img1);
  *img1 = *img2;
}

void process_args(int argc, char **argv) {
  int opt;
  t_ppm img = {}, tmp = {};
  FILE *input_file = NULL, *output_file = NULL;

  while ((opt = getopt(argc, argv, OPT_STRING)) != -1) {
    switch (opt) {
      case 'i':
        if ((input_file = fopen(optarg, "rb")) == NULL) {
          handle_error(input_file, output_file, &img, "Error opening file %s", optarg);
        }
        img = ppm_from_file(input_file);
        break;
      case 'o':
        if ((output_file = fopen(optarg, "wb")) == NULL) {
          handle_error(input_file, output_file, &img, "Error opening file %s", optarg);
        }
        break;
      case 'n':
        check_input_file(input_file, output_file, &img);
        tmp = ppm_operation_negative(img);
        free_and_assign_ppm(&img, &tmp);
        break;
      case 'r':
        check_input_file(input_file, output_file, &img);
        tmp = ppm_operation_rotate90(img);
        free_and_assign_ppm(&img, &tmp);
        break;
      case 'h':
        check_input_file(input_file, output_file, &img);
        tmp = ppm_operation_flip_horizontal(img);
        free_and_assign_ppm(&img, &tmp);
        break;
      case 'v':
        check_input_file(input_file, output_file, &img);
        tmp = ppm_operation_flip_vertical(img);
        free_and_assign_ppm(&img, &tmp);
        break;
      case 'b':
        check_input_file(input_file, output_file, &img);
        tmp = ppm_operation_blur(img, atoi(optarg));
        free_and_assign_ppm(&img, &tmp);
        break;
      case ':':
        handle_error(input_file, output_file, &img, "Option -%c requires an argument", optopt);
        break;
      case '?':
        printf("%s\n", HELP_TEXT);
        exit(0);
        break;
      default:
        handle_error(input_file, output_file, &img, "Unknown option -%c", optopt);
    }
  }
  check_input_file(input_file, output_file, &img);
  check_output_file(output_file, input_file, &img);
  ppm_save(img, output_file);
  free_resources(input_file, output_file, &img);
}
