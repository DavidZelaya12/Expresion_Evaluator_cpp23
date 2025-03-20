#include <Validator.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class ExpresionEvaluator {
public:
  std::stack<std::string> ExpresionPostfija;
  Validator val;

  ExpresionEvaluator() {
    std::cout << "Expresion Evaluator creado" << std::endl;
  }

  void setExpresion(const std::string &expresion) {
    std::stack<char> pilaOperadores;
    std::string resultado;

    for (int i = 0; i < expresion.length(); i++) {
      char token = expresion[i];

      if (token == ' ')
        continue;

      // Si es dígito, leer número completo
      if (isdigit(token)) {
        while (i < expresion.size() && isdigit(expresion[i])) {
          resultado += expresion[i];
          i++;
        }
        resultado += ' ';
        i--; // ajustar índice
      } else if (token == '(') {
        pilaOperadores.push(token);
      } else if (token == ')') {
        // Vaciar hasta encontrar '('
        while (!pilaOperadores.empty() && pilaOperadores.top() != '(') {
          resultado += pilaOperadores.top();
          resultado += ' ';
          pilaOperadores.pop();
        }
        if (!pilaOperadores.empty())
          pilaOperadores.pop(); // eliminar '('
      } else if (val.ValidarOperador(std::string(1, token))) {
        // Mientras haya operador en la pila (y no sea '(') con mayor o igual
        // precedencia, desapilar
        while (!pilaOperadores.empty() && pilaOperadores.top() != '(' &&
               val.MayorPrecedencia(token, pilaOperadores.top()) <= 0) {
          resultado += pilaOperadores.top();
          resultado += ' ';
          pilaOperadores.pop();
        }
        pilaOperadores.push(token);
      } else {
        // Cualquier otro carácter se agrega directo al resultado
        resultado += token;
        resultado += ' ';
      }
    }

    // Vaciar la pila de operadores restantes
    while (!pilaOperadores.empty()) {
      resultado += pilaOperadores.top();
      resultado += ' ';
      pilaOperadores.pop();
    }

    // Almacenar tokens en la pila de expresión postfija
    std::istringstream iss(resultado);
    std::string tokenStr;
    while (iss >> tokenStr) {
      ExpresionPostfija.push(tokenStr);
    }

    std::cout << "Expresion Infija: " << expresion << std::endl;
    std::cout << "Expresion Postfija: " << resultado << std::endl;
  }

  std::stack<std::string> getExpresion() { return ExpresionPostfija; }
};