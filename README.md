# T1 Algoritmos-Dividir-Y-Conquistar

* Nombre: Camilo Díaz                
* Rol: 202004543-7

# Descripción:

- En el actual repositorio usted encontrará diversos algoritmos tanto los cuales realizarán las labores de `ordenamiento` además de `multiplicación de matrices` empleando datasets de distintos tamaños para así comparar la eficiencia de estos mediante su `tiempo de ejecución`.

- Usted dispone de una carpeta para cada labor, dentro de ellas encontrará los códigos utilizados junto a la carpeta `resultados` en el cuál se encuentran los `tiempos de ejecución` de cada uno de los algoritmos estudiados, además de la carpeta `salida` con el resultado final tras la ejecución de los algoritmos.

# Ejecución de los Archivos:

### Paso Previo: Usted deberá eliminar tanto las carpetas Resultados como Salida con todos los archivos en su interior, además del archivo database.txt, esto para evitar la duplicación de archivos.

- Primero usted deberá decidir si desea ejecutar los algoritmos de ordenamiento o de multiplicación de matrices, para ello debe seleccionar el directorio correspondiente empleando el respectivo comando:

### Ordenamiento:
```
cd T1Algoritmos-Dividir-Y-Conquistar/Algoritmos_Y_Resultados_Ordenamiento
```
 
### Multiplicación de Matrices:
```
cd T1Algoritmos-Dividir-Y-Conquistar/Algoritmos_Y_Resultados_Matriz
```

- Si desea trabajar con los algoritmos de ordenamiento usted deberá compilar el archivo `Generador_Dataset.cpp` empleando el comando ```g++ Generador_Dataset.cpp -o Generador_Dataset``` y posteriormente ejecutarlo utilizando ```./Generador_Dataset```, una vez realizado esto usted deberá compilar el archivo `main.cpp` empleando el comando ```g++ main.cpp -o main``` y posteriormente ejecutarlo utilizando ```./main.cpp```. Si desea modificar la cantidad de vectores de cada grado de orden usted deberá cambiar el valor de las variables `cantidadAleatorio`,`cantidadSemiordenado `,`cantidadParcialmenteOrdenado` y `cantidadInvertido `, si desea cambiar la cantidad de elementos que posee cada uno de estos vectores usted deberá cambiar la variable `tamano` asociada a cada bucle for que creará el archivo y pot último usted modificando la función `generarVectorAleatorio` podrá modificar el rango de valores que podrá tomar cada elemento perteneciente a cada vector.

- Si desea trabajar con los algoritmos de multiplicación de matrices usted deberá compilar el archivo `Generador_Dataset_Matriz.cpp` empleando el comando ```g++ Generador_Dataset_Matriz.cpp -o Generador_Dataset_Matriz``` y posteriormente ejecutarlo utilizando ```./Generador_Dataset_Matriz```, una vez realizado esto usted deberá compilar el archivo ```main.cpp``` empleando el comando ```g++ main.cpp -o main``` y posteriormente ejecutarlo utilizando ```./main.cpp```. Si desea modificar tanto el valor mínimo como máximo para n, como el valor mínimo y máximo de cada elemento de la matriz además de la cantidad de pares de matrices a generar usted deberá modificar los valores de las constantes `MIN_N` `MAX_N` `MIN_VAL` `MAX_VA` `CANTIDAD_PARES` presentes en el archivo `Generador_Dataset_Matriz.cpp`.

### Consideración:

- Las carpetas Salida y Resultados dentro de  `Algoritmos_Y_Resultados_Matrices` cuentan con únicamente 4 pares de matrices esto con el fin de que la carga de los archivos al Github no fuese tan tardío pero para el análisis se emplearon 100 pares de matrices.
