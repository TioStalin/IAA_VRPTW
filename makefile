default: main

main: VRPTW.cpp
	g++ -Wall VRPTW.cpp funciones.cpp -o exe

HC:	HC-VRPTW.cpp
	g++ -Wall HC-VRPTW.cpp funciones.cpp -o HC

clean:
	rm exe solucion.txt HC

run:
	./exe

runHC:
	./HC ${iter} ${prob}
