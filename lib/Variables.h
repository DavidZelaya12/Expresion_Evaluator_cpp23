/*
En esta clase se leeran variables de un archivo txt y se almacenaran en
un map<string, double> para poder ser utilizado en el programa principal
y cargar cualquier variable que se necesite a futuros en el evaluador de
expresiones
*/
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Variables {
public:
  std::map<std::string, double> variables;

  Variables() {
    std::cout << "Variables creado" << std::endl;
    InitVariables();
  }

  void InitVariables() {
    std::ifstream archivo("variables.txt");
    std::string linea;
    while (std::getline(archivo, linea)) {
      std::string variable = linea.substr(0, linea.find("="));
      std::string valor = linea.substr(linea.find("=") + 1);
      variables[variable] = std::stod(valor);
    }
  }

  void MostrarVariables() {
    for (auto const &x : variables) {
      std::cout << x.first << " = " << x.second << std::endl;
    }
  }

  void AgregarVariable(std::string variable, double valor) {
    variables[variable] = valor;
  }

  bool ExisteVariable(std::string variable) {
    return variables.find(variable) != variables.end();
  }

  double ObtenerValor(std::string variable) { return variables[variable]; }
};