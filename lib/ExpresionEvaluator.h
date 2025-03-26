#ifndef EXPRESIONEVALUATOR_H
#define EXPRESIONEVALUATOR_H
#include <Validator.h>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
class ExpresionEvaluator {
public:
  std::stack<std::string> ExpresionPostfija;
  std::stack<double> EvaluationStack;
  double resultado = 0;
  Validator val;

  ExpresionEvaluator() {
    std::cout << "ExpresionEvaluator creado" << std::endl;
  }

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
    auto Apply = [](double a, double b, std::string op) -> double {
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
      return 0;
    };

    auto ConsumeOperator = [&Apply](std::stack<double> &stack,
                                    std::string op) -> double {
      double a = stack.top();
      stack.pop();
      double b = stack.top();
      stack.pop();

      return Apply(b, a, op);
    };

    std::vector<std::string> outputVector;
    StackToVector(ExpresionPostfija, outputVector);

    for (int i = 0; i < outputVector.size(); i++) {
      std::string token = outputVector[i];

      if (val.ValidarOperador(token)) {
        double resultado;
        resultado = ConsumeOperator(EvaluationStack, token);
        EvaluationStack.push(resultado);
      } else {
        EvaluationStack.push(std::stod(token));
      }
    }

    this->resultado = EvaluationStack.top();
    std::cout << "Resultado: " << EvaluationStack.top() << std::endl;
  }

  double GetResultado(std::stack<double> &EvaluationStack) {
    return EvaluationStack.top();
  }

  double EvaluarExpresion(const std::string &expresion) {

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