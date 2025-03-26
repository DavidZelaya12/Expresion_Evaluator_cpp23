#include "Validator.h"
#include <Variables.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <expected> // Feature C++23
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
// Clase Parser: analiza la sintaxis de evaluaciones matemáticas
// Se valida que cada paréntesis de apertura esté precedido por un operador,
// salvo al inicio
class Parser {
public:
  Validator val;
  Variables var;
  std::vector<std::string> tokens;

  Parser() {}

  // Se tiene que poder tokenizar variables
  std::expected<void, std::string> Validar(const std::string &expresion) {
    tokens.clear();
    std::string token;

    if (expresion.empty()) {
      return std::unexpected("Error: Expresion vacia");
    }

    for (int i = 0; i < expresion.length(); i++) {
      char c = expresion[i];
      if (c == ' ') {

        continue;
      }

      // ingresar tokens numericos (incluidos decimales)
      if (isdigit(c)) {
        while (i < expresion.size() &&
               (isdigit(expresion[i]) || expresion[i] == '.')) {
          token += expresion[i];
          i++;
        }
        tokens.push_back(token);
        token.clear();
        i--; // ajustar índice
      } else if (c == '(' || c == ')' ||
                 val.ValidarOperador(std::string(1, c))) {
        tokens.push_back(std::string(1, c));
      } else {
        // tokenizar variables
        while (i < expresion.size() && isalpha(expresion[i])) {
          token += expresion[i];
          i++;
        }
        tokens.push_back(token);
        token.clear();
        i--; // ajustar índice
      }
    }
    AgregarValores();
    return ValidarParentesis();
  }

  void AgregarValores() {
    for (int i = 0; i < tokens.size(); i++) {
      if (val.ValidarOperador(tokens[i]) || tokens[i] == "(" ||
          tokens[i] == ")" || isdigit(tokens[i][0])) {
        continue;
      }

      if (var.ExisteVariable(tokens[i])) {
        tokens[i] = std::to_string(var.ObtenerValor(tokens[i]));
        std::cout << "Variable encontrada: " << tokens[i] << std::endl;
        continue;
      }
      std::cout << "Ingrese el valor para la variable: " << tokens[i]
                << std::endl;
      double valor;
      std::cin >> valor;
      tokens[i] = std::to_string(round(valor * 100) / 100);
    }
    MostrarTokens();
  }

  void MostrarTokens() {
    std::cout << "Tokens: ";
    for (std::string t : tokens) {
      std::cout << t << " ";
    }
    std::cout << std::endl;
  }

  std::expected<void, std::string> ValidarParentesis() {
    // Valida que para cada parentesis "(" hay un ")"
    int parentesis = 0;
    for (std::string t : tokens) {
      if (t == "(") {
        parentesis++;
      } else if (t == ")") {
        parentesis--;
      }
    }

    if (parentesis != 0) {
      return std::unexpected("Error: Parentesis no balanceados");
    }

    return validarSintaxis();
  }

  std::expected<void, std::string> validarSintaxis() {
    // Validar que las expresiones sean correctas
    std::string Evaluacion;
    for (int i = 0; i < tokens.size(); i++) {
      std::string token = tokens[i];
      Evaluacion += token;
      // Casos en los que la sintaxis no se cumplira

      if (val.ValidarOperador(token)) {
        // Valida que la operacion no empieza ni termine con operadores
        if (i == 0 || i == tokens.size() - 1) {
          return std::unexpected("Error: Operador en posicion incorrecta en: " +
                                 Evaluacion);
        }

        if (tokens[i + 1] == ")") {
          return std::unexpected("Error: Operador en posicion incorrecta en: " +
                                 Evaluacion);
        }
      }

      // Valida que antes de un parentesis haya un operador
      if (token == "(") {
        if (i != 0 && !val.ValidarOperador(tokens[i - 1]) &&
            tokens[i - 1] != "(") {
          return std::unexpected(
              "Error: Parentesis no precedido por operador en: " + Evaluacion);
        }
        // validar que no termine con un (
        if (i == tokens.size() - 1) {
          return std::unexpected("Error: Parentesis no cerrado en: " +
                                 Evaluacion);
        }
      }

      // Valida que despues de un parentesis haya un operador
      if (token == ")") {
        if (i != tokens.size() - 1 &&
            !(val.ValidarOperador(tokens[i + 1]) || tokens[i + 1] == ")")) {
          return std::unexpected(
              "Error: Parentesis no seguido por operador en: " + Evaluacion);
        }
      }

      // Valida que no haya dos operadores seguidos
      if (val.ValidarOperador(token)) {
        if (i != tokens.size() - 1 && val.ValidarOperador(tokens[i + 1])) {
          return std::unexpected("Error: Operadores seguidos en: " +
                                 Evaluacion);
        }
      }

      // Valida que no haya dos numeros seguidos
      if (isdigit(token[0])) {
        if (i != tokens.size() - 1 && isdigit(tokens[i + 1][0])) {
          return std::unexpected("Error: Numeros seguidos en " + Evaluacion);
        }
      }
    }

    return {};
  }

  void setExpresion(std::string &expresion) {
    std::string localExpresion;
    for (std::string t : tokens) {
      localExpresion += t;
    }
    expresion = localExpresion;
  }
};
;
