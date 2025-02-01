#!/usr/bin/env bash

gcc -o build/test_ppm_operations.o test_ppm_operations.c ../ppm.c ../ppm-operations.c ../utils.c -I.. -Wall -lcmocka

./build/test_ppm_operations.o
./test_memory_leaks.sh