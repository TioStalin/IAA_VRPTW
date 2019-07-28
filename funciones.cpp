#include "funciones.h"

void print_matrix(std::vector< std::vector<int> > matrix){
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

float dist_euclidian(int x_inicial, int y_inicial, int x_final, int y_final){
  return sqrt(pow(x_inicial - x_final, 2) + pow(y_inicial - y_final, 2));
}

int dist_manhattan(int x_inicial, int y_inicial, int x_final, int y_final){
  return std::abs(x_inicial - x_final) + std::abs(y_inicial - y_final);
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

int elegir_metodo(int probabilidad){
  srand(time(NULL));
  int resultado = rand() % 100;
  if (resultado <= probabilidad) {
    return 0;
  }
  return 1;
}

void split(std::string line, std::string delim, std::vector<int> &camino){
  std::string s = line;
  std::string delimiter = delim;

  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      camino.push_back(stoi(token));
      s.erase(0, pos + delimiter.length());
  }
}

int verificar_calidad(std::vector< std::vector<int> > caminos, std::vector< std::vector<int> > tiempos){
  int calidad = 0;
  for (size_t i = 0; i < caminos.size(); i++) {
    for (size_t j = 0; j < caminos[i].size(); j++) {
      calidad += tiempos[caminos[i][j]][caminos[i][j+1]];
      if(caminos[i][j+1] == 0){
        break;
      }
    }
  }
  return calidad;
}

void agregar_camion(std::vector< std::vector<int> > &test){
  int max, aux;
  max = aux = 0;
  for (size_t i = 0; i < test.size(); i++) {
    if(test[i].size() > aux){
      max = i;
      aux = test[i].size();
    }
  }
  std::vector<int> vect;
  int size = test[max].size();
  for (int i = size; i > size/2; i--) {
    vect.push_back(test[max].back());
    test[max].pop_back();
  }
  vect.push_back(0);
  test[max].push_back(0);
  std::reverse(vect.begin(), vect.end());
  test.push_back(vect);
}

void insertar(std::vector<int> &objetivo, int posicion, int agregar){
  std::vector<int> aux = objetivo;
  objetivo.clear();
  int i = 0;
  bool flag = false;
  while (i != aux.size()+1){
    if(i == posicion){
      objetivo.push_back(agregar);
      flag = true;
    }
    else{
      if(flag){
        objetivo.push_back(aux[i-1]);
      }
      else{
        objetivo.push_back(aux[i]);
      }
    }
    i++;
  }

}

void relocate(std::vector< std::vector<int> > &test, std::vector<int> tiempo_inicio, std::vector<int> tiempo_fin, std::vector<int> tiempo_servicio, std::vector< std::vector<int> > tiempos){
  int max, aux;
  srand(time(NULL));
  std::vector< std::vector<int> > vect;
  max = aux = 0;
  for (size_t i = 0; i < test.size(); i++) {
    if(test[i].size() > aux){
      max = i;
      aux = test[i].size();
    }
  }

  //TODO: seleccionar un nodo random
  int nodo = rand() % aux;
  while(nodo == 0 or nodo == aux-1){
    nodo = rand() % aux;
  }
  int objetivo = rand() % test.size();
  while(objetivo == max){
    objetivo = rand() % test.size();
  }

  int inicio = tiempo_inicio[test[max][nodo]];
  int fin = tiempo_fin[test[max][nodo]];
  int servicio = tiempo_servicio[test[max][nodo]];
  
  int posicion = factibilidad(test[objetivo], tiempos, tiempo_inicio, tiempo_fin, tiempo_servicio, nodo, max);

  if(posicion == -1){
    return;
  }
  insertar(test[objetivo], posicion, test[max][nodo]);
  test[max].erase(test[max].begin()+nodo);
}


//TODO: hacer funcion de factibilidad
int factibilidad(std::vector<int> objetivo, std::vector< std::vector<int> > tiempos, std::vector<int> tiempo_inicio, std::vector<int> tiempo_fin, std::vector<int> tiempo_servicio, int nodo, int max){
  bool insercion = false;
  for (size_t i = 1; i < objetivo.size()-1; i++){
    int tiempo = 0;
    int j = 0;
    bool flag = false;
    while (j != objetivo.size()-1){
      if(i == j+1){
        if(tiempo + tiempos[objetivo[j]][nodo] >= tiempo_inicio[nodo] && tiempo + tiempos[objetivo[j]][nodo] <= tiempo_fin[nodo]){
          tiempo += tiempos[objetivo[j]][nodo];
          flag = true;
          insercion = true;
        }
        else{
          insercion = false;
          break;
        }
      }
      if(flag){
        if(tiempo + tiempos[nodo][objetivo[j+1]] >= tiempo_inicio[objetivo[j+1]] && tiempo + tiempos[nodo][objetivo[j+1]] <= tiempo_fin[objetivo[j+1]]){
          tiempo += tiempos[nodo][objetivo[j+1]];
          flag = false;
        }
        else{
          insercion = false;
          break;
        }
      }
      if(tiempo + tiempos[objetivo[j]][objetivo[j+1]] >= tiempo_inicio[objetivo[j+1]] && tiempo + tiempos[objetivo[j]][objetivo[j+1]] <= tiempo_fin[objetivo[j+1]]){
        tiempo += tiempos[objetivo[j]][objetivo[j+1]];
        j++;
      }
      else{
        insercion = false;
        break;
      }
      
    }
    if (insercion){
      return i;
    }
  }
  return -1;
}