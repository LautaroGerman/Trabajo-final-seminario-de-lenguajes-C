Este trabajo está basado en la propuesta presentada en [https://github.com/chrodriguez/ppm-ejercicio-c](https://github.com/chrodriguez/ppm-ejercicio-c).


## Trabajo Final de Seminario de Lenguajes C: PPM image processor

El trabajo final consiste en implementar la funcionalidad faltante del programa
que provee el presente repositorio.

Este programa es un gestor de imágenes en formato [PPM de tipo P6](http://netpbm.sourceforge.net/doc/ppm.html).
Para poder operar con estas imágenes se implementó una versión simplificada y
básica de **ppm** que básicamente permite crear nuevas imágenes, leerlas desde
el disco o guardarlas en el disco. 

La implementación de ppm, puede verse en los archivos `ppm.c` y `ppm.h`. Para
poder realizar operaciones sobre las imágenes, existe otra librería llamada
**ppm-operations**. Esta librería ofrece funciones de transformación de imágenes
respetando siempre la idea de devolver una nueva imagen transformada a partir de
la imagen original.

A modo de ejemplo, se ofrece un programa principal que muestra el uso de las
librerías provistas en este repositorio.

### Objetivo del trabajo

Completar la funcionalidad de la librería **ppm-operations** con las siguientes
funciones:

* **Negativo:** cada pixel de la imagen resultado se calcula como el valor de
  depth (profundidad de color) correspondiente a la imagen original, menos el
  valor actual del pixel (cuando el resultado es negativo, como son valores
  unsigned funciona como se espera).
* **Rotar a 90 grados:** una imagen de **x** ancho por **y** alto será rotada a 90
  grados, siendo la nueva imagen de **y** ancho por **x** alto. Luego, cada pixel
  en la posición original `[i,j]` será colocado en la posición `[x-j-1,i]` del
  destino.
* **Espejado horizontal:** cada pixel de la imagen resultado en la posición 
  `[i,j]` se calcula como el correspondiente `[i,width-j-1]`
* **Espejado vertical:** cada pixel de la imagen resultado en la posición 
  `[i,j]` se calcula como el correspondiente `[height-i-1,j]`
* **Desenfoque:** cada pixel en la posición `[i,j]` con un radio **r**
  especificado como argumento se calcula como el promedio de los pixeles en las
  posiciones que van desde `[max(i-r,0),max(j-r,0)]` hasta `[min(i+r,height-1),min(j+r,width-1)]`

El programa principal deberá recibir opciones y a partir de ellas operar con las
funciones antes mencionadas según se vayan procesando las opciones:

* `-i entrada.ppm`: archivo origen. Opción requerida
* `-o salida.ppm`: archivo salida. Opción requerida
* `-n`: calcula el negativo
* `-r`: rota a 90 grados
* `-h`: espejo horizontal
* `-v`: espejo vertical
* `-b NUM`: desenfoque con radio NUM
* `-?`: ayuda del programa

Los argumentos se irán procesando a medida que aparecen, siendo fundamental que
la opción -i sea la primer opción para poder así procesar lo que demanda el
usuario. Ejemplos de uso:

### Copia de una imagen

```
./images -i input.ppm -o output.ppm
```

### Calcula el negativo del origen

```
./images -i input.ppm -o output.ppm -n
```

### Rota una imagen, luego hace el espejo horizontal y luego el desenfoque

```
./images -i input.ppm -h -o output.ppm -b 2
```

### Ejemplos de imagenes

El directorio `./samples` tiene ejemplo de PPMs

## Ejemplo provisto

Se entrega código que implementa la funcionalidad básica de lectura y creación
de PPMs. Además, se entrega un ejemplo de programa principal y la función que
devuelve el negativo de una imagen. 

Para compilar el código entregado:

```
gcc -o ppm-processor-sample *c -Wall
```

Y es posible probarlo de la siguiente forma:

```
./ppm-processor-sample samples/couple.ppm
```
