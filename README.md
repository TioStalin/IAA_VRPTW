# Vehicle Routing Problem with Time Windows

## **Greedy**

### ¿Cómo ejecutar?
1. Clonar el repositorio.
2. Abrir una terminal en la carpeta clonada.
3. Ejecutar el comando `make`, del cual se creará un 'exe'.
4. Ejecutar el comando `make run` en el cual se le pedirán datos.

### ¿Cómo probar las instancias?
Una vez obtenido el 'exe' se debe usar el comando `make run < Instancias/{instancia a usar}.txt`. Las instancias presentadas fueron **modificadas** para que se corriera en este programa, si usa una instancia conocida de este problema, asegurese de ordenar los datos a antes de ejecutar.

## **Hill Climbing**

### ¿Cómo ejecutar?
1. Ejecutar **Greedy** para tener un archivo de texto de solución inicial.
2. Ejecutar el comando `make HC` del cual se creará un 'HC'
3. Ejecutar el comando `make iter={} prob={} runHC` en el cual se le pedirán datos.

### ¿Cómo probar las instancias?
Una vez obtenido el 'HC' se debe usar el comando `make iter={número de iteraciones} prob={probabilidad de los movimientos} runHC < Instancias/{instancia a usar}.txt`. El número de iteraciones debe ser positivo y mayor a 0. La probabilidad no puede superar el 100 y se debe escribir como entero.

### Para tener en cuenta
Hill Climbing al necesitar una solución inicial (para este problema la solución debe ser factible), el archivo 'Instancias/{instancia a usar}.txt' tiene que contener los datos que modelan esa solución. Es decir, debe contener toda la información necesaria para realizar la heurística (Véase 'Instancias' para ver ejemplos).


## Instancias disponibles
* C101-25
* C101-50
* C101-100
* C102-25
* C201-25
* R201-50
* RC101-50
* RC201-25

Además se incluyó el comando `make clean` que borra el ejecutable de la carpeta.
* Código realizado por Daniel Tapia R.

* Las instancias usadas son las conocidas instancias para VRPTW de [Solomon](http://web.cba.neu.edu/~msolomon/problems.htm).
