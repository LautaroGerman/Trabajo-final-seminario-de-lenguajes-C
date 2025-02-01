#!/usr/bin/env bash

# This script is used to check for memory leaks in the program.
LOG_FILE="build/valgrind-out.txt"

gcc -g -o build/test_valgrind.o ../args-processor.c ../main.c ../ppm.c ../ppm-operations.c ../utils.c -I.. -Wall

# clean file
> "$LOG_FILE"

# Lista de opciones a probar
COMMANDS=(
    "-i ../samples/model.ppm -o build/output.ppm"
    "-i ../samples/model.ppm -o build/output.ppm -n"
    "-i ../samples/model.ppm -h -o build/output.ppm -b 2"
    "-i ../samples/model.ppm -h -o build/output.ppm -r -v -h -b 2"
)

# Ejecutar cada comando con Valgrind
for CMD in "${COMMANDS[@]}"; do
    echo "Ejecutando: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_valgrind $CMD"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/test_valgrind $CMD &>> "$LOG_FILE"
done

# Buscar "lost" en el archivo de log
if grep "lost" "$LOG_FILE"; then
    echo "Se encontraron errores de memoria en el archivo revise el archivo $LOG_FILE"
    exit 1
else
    echo "No se encontraron errores de memoria"
    exit 0
fi

