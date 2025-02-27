#include <iostream>
#include <string>

class Validator {
public:
  Validator() { std::cout << "Validator creado" << std::endl; }

  bool Is_validOperator(std::string hola) {
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
};
