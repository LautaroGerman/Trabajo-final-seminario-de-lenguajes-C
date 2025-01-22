#ifndef __ARGS_PROCESSOR_H
#define __ARGS_PROCESSOR_H

#include <getopt.h> // The optarg var is global and defined in this header
#include <stdio.h>
#include <error.h>

#define OPT_STRING ":i:o:b:nrhv?"
#define HELP_TEXT \
    "Uso: program_name [opciones]\n\n" \
    "Opciones disponibles:\n" \
    "-i entrada.ppm    : Archivo de entrada (requerido)\n" \
    "-o salida.ppm     : Archivo de salida (requerido)\n" \
    "-n                : Calcula el negativo de la imagen\n" \
    "-r                : Rota la imagen 90 grados\n" \
    "-h                : Espejo horizontal de la imagen\n" \
    "-v                : Espejo vertical de la imagen\n" \
    "-b NUM            : Aplica un desenfoque con radio NUM\n" \
    "-?                : Muestra este mensaje de ayuda\n"

static void check_input(const char *input_filename) {
    if (input_filename == NULL) {
        error(1, 0, "Debe especificar un archivo de entrada");
    }
}

static void check_output(const char *output_filename) {
    if (output_filename == NULL) {
        error(1, 0, "Debe especificar un archivo de salida");
	}
}

void process_args(int argc, char **argv) {
    int opt;
    char *input_filename = NULL, *output_filename = NULL;

    while ((opt = getopt(argc, argv, OPT_STRING)) != -1) {
        switch (opt) {
            case 'i':
                input_filename = optarg;
                printf("option i with value '%s'\n", optarg);
                break;
            case 'o':
                output_filename = optarg;
                printf("option o with value '%s'\n", optarg);
                break;
            case 'b':
                check_input(input_filename);
                printf("option b with value '%s'\n", optarg);
                break;
            case 'n':
                check_input(input_filename);
                printf("option n\n");
                break;
            case 'r':
                check_input(input_filename);
                printf("option r\n");
                break;
            case 'h':
                check_input(input_filename);
                printf("option h\n");
                break;
            case 'v':
                check_input(input_filename);
                printf("option v\n");
                break;
            case ':':
                error(1, 0, "Opcion -%c requiere un argumento\n%s", optopt, HELP_TEXT);
                break;
            case '?':
                printf("%s", HELP_TEXT);
                break;
            default:
                printf("Error inesperado: getop retornó el caracter 0%o ??\n", opt);
        }
    }
}
#endif