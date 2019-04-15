default: main

main: VRPTW.cpp
	g++ -Wall VRPTW.cpp -o exe

clean:
	rm exe

run:
	./exe
