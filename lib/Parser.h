#include "Validator.h"
#include <iostream>
#include <stack>
#include <string>

/*
Este parser se utilizara para separar los tokens de la expresion
y evaluar si son validos o no para la expresion y en caso que no hacer
un throw con un mensaje de error
*/

class Parser {
public:
  Validator val;
  Parser() { std::cout << "Parser creado" << std::endl; }

  void tockenizado(std::string expresion) {
    // Aqui se convierten en tokens los caracteres de la expresion
    std::stack<std::string> Tokens;
    std::string token = "";

    std::cout << "Expresion: " << expresion << std::endl;
    for (int i = 0; i <= expresion.length(); i++) {
      if (expresion[i] == ' ') {
        continue;
      }
      if (expresion[i] == '(' || expresion[i] == ')' ||
          val.ValidarOperador(std::string(1, expresion[i]))) {
        if (!token.empty()) {
          Tokens.push(token);
          token = "";
        }
        Tokens.push(std::string(1, expresion[i]));
      } else {
        token += expresion[i];
      }
    }
    if (!token.empty()) {
      Tokens.push(token);
    }
    Validarparentesis(expresion);
    MostrarTokens(Tokens);
    ValidarExpresion(Tokens);
  }

  void Validarparentesis(std::string expresion) {
    // Aqui se valida que los parentesis esten balanceados
    std::stack<char> pila;
    for (int i = 0; i < expresion.length(); i++) {
      if (expresion[i] == '(') {
        pila.push(expresion[i]);
      } else if (expresion[i] == ')') {
        if (pila.empty()) {
          throw std::invalid_argument(
              "Error de sintaxis: parentesis no balanceados");
        }
        pila.pop();
      }
    }
    if (!pila.empty()) {
      throw std::invalid_argument(
          "Error de sintaxis: parentesis no balanceados");
    }
  }

  void ValidarExpresion(std::stack<std::string> tokens) {
    // Aqui se valida la expresion sintacticamente, no se evalua si los valores
    // son correctos
    std::string tokenActual = "";
    std::string tokenAnterior = "";

    while (!tokens.empty()) {
      if (tokenActual.empty()) {
        tokenActual = tokens.top();
        tokens.pop();
        continue;
      }

      // Caso ++, --, +-, -+ de doble operador seguido
      if (val.ValidarOperador(tokenActual) &&
          val.ValidarOperador(tokenAnterior)) {
        throw std::invalid_argument(
            "Error de sintaxis: Operadores consecutivos");
      }
      // caso conde el token actual no es un operador y le sigue un ( -> 10(1+1)
      if (!val.ValidarOperador(tokenAnterior) && tokenActual == "(") {
        throw std::invalid_argument(
            "Error de sintaxis: se espera un operador antes de un (");
      }
      // caso donde el token actual es un operador y le sigue un ) -> 10+1)
      if (val.ValidarOperador(tokenActual) && tokenAnterior == ")") {
        throw std::invalid_argument(
            "Error de sintaxis: se espera un operador despues de un )");
      }

      // caso donde a un numero no le sigue un operador -> 10 1
      if (val.ValidarNumero(tokenActual) && val.ValidarNumero(tokenAnterior)) {
        throw std::invalid_argument(
            "Error de sintaxis: se espera un operador entre numeros");
      }

      // caso donde a un operador no le sigue un numero -> 10 + )
      if (val.ValidarOperador(tokenActual) && tokenAnterior == "(") {
        throw std::invalid_argument(
            "Error de sintaxis: se espera un numero despues de un operador");
      }

      // caso donde aparece un ) sin un ( -> 10 + 1)
      if (tokenActual == ")" && tokenAnterior != "(") {
        throw std::invalid_argument(
            "Error de sintaxis: se espera un ( antes de un )");
      }

      tokenAnterior = tokenActual;
      tokenActual = tokens.top();
      tokens.pop();
    }
  }

  void MostrarTokens(std::stack<std::string> tokens) {
    while (!tokens.empty()) {
      std::cout << tokens.top() << std::endl;
      tokens.pop();
    }
  }
};