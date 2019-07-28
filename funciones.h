#ifndef VRPTW
#define VRPTW

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>
#define INF 999999999

void print_matrix(std::vector< std::vector<int> >);
float dist_euclidian(int, int, int, int);
int dist_manhattan(int, int, int, int);
void time_matrix(std::vector< std::vector<int> > &, std::vector<int> , std::vector<int> , int );
int ruta_completa(std::vector<int>);
int elegir_metodo(int);
void split(std::string, std::string, std::vector<int> &);
int verificar_calidad(std::vector< std::vector<int> >, std::vector< std::vector<int> >);
void agregar_camion(std::vector< std::vector<int> > &);
void relocate(std::vector< std::vector<int> >&, std::vector<int>, std::vector<int>, std::vector<int>, std::vector< std::vector<int> >);
int factibilidad(std::vector<int>, std::vector< std::vector<int> >, std::vector<int>, std::vector<int>, std::vector<int>, int, int);

#endif 
