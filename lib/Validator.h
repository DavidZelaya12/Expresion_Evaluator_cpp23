#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <algorithm>
#include <iostream>
#include <string>

class Validator {
public:
  Validator() { std::cout << "Validator creado" << std::endl; }

  bool ValidarOperador(std::string hola) {
    char token = hola[0];
    return (token == '+')
               ?: ((token == '-')
                       ? true
                       : ((token == '*')
                              ? true
                              : ((token == '/') ? true
                                 : (token == '^')
                                     ? true
                                     : ((token == '%') ? true : false))));
  }

  int Precedencia(char token) {
    return (token == '^') ? 3
                          : ((token == '*' || token == '/')
                                 ? 2
                                 : ((token == '+' || token == '-') ? 1 : -1));
  }

  bool ValidarNumero(const std::string &str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
  }

  int MayorPrecedencia(char token1, char token2) {
    // -1 == <
    //  1 == >
    //  0 == ==
    return (Precedencia(token1) > Precedencia(token2))
               ? 1
               : ((Precedencia(token1) < Precedencia(token2)) ? -1 : 0);
  }
};

#endif
