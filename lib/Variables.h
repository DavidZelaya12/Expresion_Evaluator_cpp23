/*
En esta clase se leeran variables de un archivo txt y se almacenaran en
un map<string, double> para poder ser utilizado en el programa principal
y cargar cualquier variable que se necesite a futuros en el evaluador de
expresiones
*/
#ifndef VARIABLES_H
#define VARIABLES_H
#include <fstream>
#include <iostream>
#include <map>
#include <stdfloat>
#include <string>

class Variables {
public:
  std::map<std::string, std::float64_t> variableMap;

  Variables() { InitVariables(); }

  void InitVariables() {
    std::ifstream archivo("C:\\Users\\HP\\Desktop\\Github\\Expresion_Evaluator_"
                          "cpp23\\variables.txt");
    std::string linea;

    if (!archivo.is_open()) {
      std::cout << "No se pudo abrir el archivo" << std::endl;
      return;
    }

    while (std::getline(archivo, linea)) {
      if (linea.empty()) {
        continue;
      }
      linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
      std::string variable = linea.substr(0, linea.find("="));
      std::string valor = linea.substr(linea.find("=") + 1);
      variableMap[variable] = std::stod(valor);
    }
    std::cout << "--Variables cargadas--" << std::endl;
    MostrarVariables();
  }

  void MostrarVariables() {
    for (auto const &x : variableMap) {
      std::cout << x.first << "=" << x.second << std::endl;
    }
  }

  bool ExisteVariable(std::string variable) {
    return variableMap.find(variable) != variableMap.end();
  }

  double ObtenerValor(std::string variable) { return variableMap[variable]; }
};

#endif