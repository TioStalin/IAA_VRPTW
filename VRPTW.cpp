#include "funciones.h"

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
  std::ofstream file;
  file.open("solucion.txt");
  file << actual << " ";
  while(ruta_completa(uso) != nodos){
    if(actual == 0 && distancia != 0){
      vehiculos++;
      tiempo = 0;
      file << "\n" << "0 ";
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
      file << actual << " ";
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
      file << actual << " ";
    }
  }
  std::cout << "Distancia recorrida: " << distancia + matrix_time[actual][0] << "\n" << "Cantidad de vehiculos usados: "<< vehiculos << "\n";
  file << "0";
  file.close();
  return 0;
}
