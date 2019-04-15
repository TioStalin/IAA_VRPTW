#include <iostream>
#include <vector>
#include <cmath>
#define INF 999999999

int dist_manhattan(int x_inicial, int y_inicial, int x_final, int y_final){
  return std::abs(x_inicial - x_final) + std::abs(y_inicial - y_final);
}

float dist_euclidian(int x_inicial, int y_inicial, int x_final, int y_final){
  return sqrt(pow(x_inicial - x_final, 2) + pow(y_inicial - y_final, 2));
}

//Funcion para calcular la matrix de tiempos (para facilitar el problema, la distancia es igual al tiempo)

void time_matrix(std::vector< std::vector<int> > &matrix, std::vector<int> x, std::vector<int> y, int cantidad){
  for (int i = 0; i < cantidad; i++) {
    std::vector<int> linea;
    for (int j = 0; j < cantidad; j++) {
      int distancia = dist_euclidian(x[i], y[i], x[j], y[j]);
      if(distancia == 0){
        linea.push_back(INF);
      }
      else{
        linea.push_back(distancia);
      }
    }
    matrix.push_back(linea);
  }
}

//Funcion para verificar si todos los nodos fueron visitados

int ruta_completa(std::vector<int> uso){
  int suma = 0;
  for (int i = 0; i < int(uso.size()); i++) {
    suma += uso[i];
  }
  return suma;
}

int main(){

  //Variables a usar

  int nodos, x, y, d, i, f, t;
  std::vector<int> coordenada_x;
  std::vector<int> coordenada_y;
  std::vector<int> tiempo_inicio;
  std::vector<int> tiempo_fin;
  std::vector<int> tiempo_servicio;

  //Pedir los datos y trabajar datos

  std::cin >> nodos;
  int maxTime = 0;
  for (int j = 0; j < nodos; j++){
    std::cin >> x >> y >> d >> i >> f >> t;
    coordenada_x.push_back(x);
    coordenada_y.push_back(y);
    tiempo_inicio.push_back(i);
    tiempo_fin.push_back(f);
    tiempo_servicio.push_back(t);
    if(maxTime < f){
      maxTime = f;
    }
  }
  std::vector< std::vector<int> > matrix_time;
  time_matrix(matrix_time, coordenada_x, coordenada_y, nodos);

  //Inicio del problema

  std::vector<int> uso(nodos, 0);
  float distancia = 0;
  std::vector< std::vector<int> > rutas;
  uso[0] = 1;
  int actual = 0;
  int vehiculos = 1;
  int tiempo = 0;
  while(ruta_completa(uso) != nodos){
    if(actual == 0 && distancia != 0){
      vehiculos++;
      tiempo = 0;
    }
    //Se busca el camino mas corto dentro de la ventana de tiempo factible
    int min = INF;
    int index = 0;
    for(int i = 0; i < nodos; i++){
      int tiempo_tramo = matrix_time[actual][i];
      if(uso[i] != 1 && min > tiempo_tramo && tiempo + tiempo_tramo >= tiempo_inicio[i] && tiempo + tiempo_tramo <= tiempo_fin[i]){
        min = tiempo_tramo;
        index = i;
      }
    }
    //Si no es posible cumplir con el recorrido, el vehiculo se devuelve
    if(tiempo > maxTime && index == 0){
      tiempo = matrix_time[actual][0] + tiempo_servicio[0];
      distancia += matrix_time[actual][0];
      actual = 0;
    }
    //Si es posible visitar un nodo factible, se espera a que su ventana de tiempo sea lograble
    else if(index == 0){
      tiempo += 1;
    }
    //El vehiculo se mueve al nuevo nodo
    else{
      uso[index] = 1;
      tiempo = matrix_time[actual][index] + tiempo_servicio[index];
      distancia += matrix_time[actual][index];
      actual = index;
    }
  }
  std::cout << "Distancia recorrida: " << distancia + matrix_time[actual][0] << "\n" << "Cantidad de vehiculos usados: "<< vehiculos << "\n";
  return 0;
}
