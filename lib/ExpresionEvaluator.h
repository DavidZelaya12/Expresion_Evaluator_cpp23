#ifndef EXPRESIONEVALUATOR_H
#define EXPRESIONEVALUATOR_H
#include <Validator.h>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdfloat>
#include <string>
#include <utility>
#include <vector>
class ExpresionEvaluator {
public:
  std::stack<std::string> ExpresionPostfija;
  std::stack<std::float64_t> EvaluationStack;
  std::float64_t resultado = 0;
  Validator val;

  ExpresionEvaluator() {}

  void setExpresion(const std::string &expresion) {
    std::stack<char> pilaOperadores;
    std::string resultado;

    for (int i = 0; i < expresion.length(); i++) {
      char token = expresion[i];

      if (token == ' ')
        continue;

      // ingresar tokens numericos (incluidos decimales)
      if (isdigit(token)) {
        while (i < expresion.size() &&
               (isdigit(expresion[i]) || expresion[i] == '.')) {
          resultado += expresion[i];
          i++;
        }
        resultado += ' ';
        i--; // ajustar índice
      } else if (token == '(') {
        // Si es '(' se agrega directo a la pila
        pilaOperadores.push(token);
      } else if (token == ')') {
        // Vaciar hasta encontrar '('
        while (!pilaOperadores.empty() && pilaOperadores.top() != '(') {
          resultado += pilaOperadores.top();
          resultado += ' ';
          pilaOperadores.pop();
        }
        // Eliminar '('
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
        // Cualquier otro caracter se agrega directo al resultado
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

    // Almacenar tokens en la pila de expresion postfija
    // Desde el string que se concateno
    std::istringstream iss(resultado);
    std::string tokenStr;
    while (iss >> tokenStr) {
      ExpresionPostfija.push(tokenStr);
    }

    std::cout << "Expresion infija: " << expresion << std::endl;
    std::cout << "Expresion postfija: " << resultado << std::endl;
  }

  void StackToVector(std::stack<std::string> &stack,
                     std::vector<std::string> &outputVector) {
    while (!stack.empty()) {
      outputVector.push_back(stack.top());
      stack.pop();
    }
    std::reverse(outputVector.begin(), outputVector.end());
  }

  void EvaluarExpresion() {
    // C++ 23 Feature: deduccion automatica de tipos en funciones locales
    auto Apply = [](std::float64_t a, std::float64_t b,
                    std::string op) -> std::float64_t {
      if (op == "+")
        return a + b;
      if (op == "-")
        return a - b;
      if (op == "*")
        return a * b;
      if (op == "%")
        return (int)a % (int)b;
      if (op == "/") {
        if (b == 0)
          throw std::invalid_argument(
              "Error: Division por cero no es permitida");
        return a / b;
      }
      if (op == "^") {

        return pow(a, b);
      }

      // C++23 Feature: std::unreachable
      std::unreachable();
    };

    auto ConsumeOperator = [&Apply](std::stack<std::float64_t> &stack,
                                    std::string op) -> std::float64_t {
      std::float64_t a = stack.top();
      stack.pop();
      std::float64_t b = stack.top();
      stack.pop();

      return Apply(b, a, op);
    };

    std::vector<std::string> outputVector;
    StackToVector(ExpresionPostfija, outputVector);

    for (int i = 0; i < outputVector.size(); i++) {
      std::string token = outputVector[i];

      if (val.ValidarOperador(token)) {
        std::float64_t resultado;
        resultado = ConsumeOperator(EvaluationStack, token);
        EvaluationStack.push(resultado);
      } else {
        try {
          EvaluationStack.push(std::stod(token));
        } catch (std::invalid_argument &e) {
          throw std::invalid_argument("Error: Token invalido en la expresion " +
                                      token);
          break;
        };
      }

      this->resultado = EvaluationStack.top();
      std::cout << "Resultado: " << EvaluationStack.top() << std::endl;
    }
  }

  std::float64_t GetResultado(std::stack<std::float64_t> &EvaluationStack) {
    return EvaluationStack.top();
  }

  std::float64_t EvaluarExpresion(const std::string &expresion) {

    auto VaciarStack = [](auto &stack) {
      while (!stack.empty())
        stack.pop();
    };

    VaciarStack(EvaluationStack);
    VaciarStack(ExpresionPostfija);
    resultado = 0;

    setExpresion(expresion);
    EvaluarExpresion();
    return resultado;
  }
};

#endif