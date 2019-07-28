#include "funciones.h"

int main(int argc, char *argv[]){

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

  //Se obtienen las soluciones iniciales

  std::string line;
  std::ifstream solucion("solucion.txt");
  std::vector< std::vector<int> > caminos;
  if(solucion.is_open()){
    while(getline(solucion, line)){
      std::vector<int> camino;
      split(line, " ", camino);
      caminos.push_back(camino);
    }
    solucion.close();
    caminos[caminos.size()-1].push_back(0);
  }

  int oportunidades = 0;
  int actual = verificar_calidad(caminos, matrix_time);
  std::vector< std::vector<int> > mejor;
  std::vector< std::vector<int> > test;
  mejor = test = caminos;

  int probabilidad = atoi(argv[2]);
  int veces = atoi(argv[1]);
  std::ofstream file;
  file.open("solucionHC.txt");

  while(oportunidades < veces){
    int eleccion = elegir_metodo(probabilidad);
    if(test.size() >= 25){
      eleccion = 0;
    }
    if(eleccion == 0){
      relocate(test, tiempo_inicio, tiempo_fin, tiempo_servicio, matrix_time);
      int distancia = verificar_calidad(test, matrix_time);
      if(distancia <= actual){
        mejor = test;
        actual = distancia;
      }
    }
    else{
      agregar_camion(test);
      int distancia = verificar_calidad(test, matrix_time);
      if(distancia <= actual){
        mejor = test;
        actual = distancia;
      }
    }
    oportunidades++;
  }

  for (size_t i = 0; i < mejor.size(); i++){
    for (size_t j = 0; j < mejor[i].size(); j++){
      file << mejor[i][j] << " ";
    }
    file << '\n';
  }
  
  print_matrix(mejor);
  std::cout << "Con calidad: " << actual << '\n';
  return 0;
}
