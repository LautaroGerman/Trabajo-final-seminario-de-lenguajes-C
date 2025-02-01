## Trabajo Final de Seminario de Lenguajes C: PPM image processor

La propuesta y especificaciones del trabajo pueden verse detalladamente en: [https://github.com/chrodriguez/ppm-ejercicio-c](https://github.com/chrodriguez/ppm-ejercicio-c).

Los detalles del trabajo realizado pueden verse en el archivo [Informe.pdf](Informe.pdf).

Este programa es un gestor de imágenes en formato [PPM de tipo P6](http://netpbm.sourceforge.net/doc/ppm.html)
mediante línea de comandos:

* `-i entrada.ppm`: archivo origen. Opción requerida
* `-o salida.ppm`: archivo salida. Opción requerida
* `-n`: calcula el negativo
* `-r`: rota a 90 grados
* `-h`: espejo horizontal
* `-v`: espejo vertical
* `-b NUM`: desenfoque con radio NUM
* `-?`: ayuda del programa

Los argumentos se procesan a medida que aparecen, siendo importante que
la opción -i sea la primer opción para poder realizar el posterior procesamiento.
Ejemplos de uso:

### Copia de una imagen

```
./images -i input.ppm -o output.ppm
```

###  Espejado horizontal y luego desenfoque

```
./images -i input.ppm -o output.ppm -h -b 2
```

### Rota una imagen, y luego calcula el negativo

```
./images -i input.ppm -n -o output.ppm -r
```

### Ejemplos de imágenes

El directorio `./samples` tiene ejemplo de PPMs

## Compilación

```
gcc -o ppm-processor.o main.c args-processor.c ppm-operations.c ppm.c utils.c -Wall
```

### Ejemplo

```
./ppm-processor.o -i samples/model.ppm -o model-out.ppm -n -r -b 2
```

### Tests
El archivo build/run_tests.sh corre todos los test realizados. Para poder ejecutarlo se necesitan las
dependencias valgrind y cmocka:

```
sudo apt-get install valgrind
sudo apt install libcmocka-dev
```
