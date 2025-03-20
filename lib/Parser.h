#include "Validator.h"
#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

/*
Este parser se dedicara a seguir una gramatica bnf para
validar la sintaxis de una expresion matematica, no para
su evaluacion
*/

/*
BNF:
<expr> ::= <term> { ("+" | "-") <term> }
<term> ::= <factor> { ("*" | "/") <factor> }
<factor> ::= <number> | "(" <expr> ")"
<number> ::= <digit> { <digit> }
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
*/

class Parser {
public:
  Validator val;
  std::vector<std::string> tokens;
  int pos;

  Parser() : pos(0) { std::cout << "Parser creado" << std::endl; }

  // Tokeniza la expresión y valida los paréntesis
  void tokenizar(const std::string &expresion) {
    tokens.clear();
    pos = 0;
    std::string token = "";

    for (int i = 0; i < expresion.length(); i++) {
      char c = expresion[i];
      if (c == ' ')
        continue;
      if (c == '(' || c == ')' || val.ValidarOperador(std::string(1, c))) {
        if (!token.empty()) {
          tokens.push_back(token);
          token = "";
        }
        if (!tokens.empty() && std::isdigit(tokens.back().back()) && c == '(') {
          tokens.push_back("*");
        }
        tokens.push_back(std::string(1, c));
      } else {
        token += c;
      }
    }
    if (!token.empty())
      tokens.push_back(token);

    ValidarParentesis(expresion);
  }

  // Verifica que los parentesis esten balanceados
  void ValidarParentesis(const std::string &expresion) {
    std::stack<char> pila;
    for (char c : expresion) {
      if (c == '(')
        pila.push(c);
      else if (c == ')') {
        if (pila.empty())
          throw std::invalid_argument(
              "Error de sintaxis: parentesis no balanceados");
        pila.pop();
      }
    }
    if (!pila.empty())
      throw std::invalid_argument(
          "Error de sintaxis: parentesis no balanceados");
  }

  // <expr> ::= <term> { ("+" | "-") <term> }
  void parseExpression() {
    parseTerm();
    while (pos < tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-")) {
      pos++; // Consume el operador
      parseTerm();
    }
  }

  // <term> ::= <factor> { ("*" | "/") <factor> }
  void parseTerm() {
    parseFactor();
    while (pos < tokens.size() && (tokens[pos] == "*" || tokens[pos] == "/")) {
      pos++; // Consume el operador
      parseFactor();
    }
  }

  // <factor> ::= <number> | "(" <expr> ")"
  void parseFactor() {
    if (pos >= tokens.size())
      throw std::invalid_argument("Error de sintaxis: token inesperado");

    std::string token = tokens[pos];
    if (token == "(") {
      pos++; // Consume "("
      parseExpression();
      if (pos >= tokens.size() || tokens[pos] != ")")
        throw std::invalid_argument("Error de sintaxis: falta ')'");
      pos++; // Consume ")"
    } else {
      // Validar que sea un número
      if (!val.ValidarNumero(token))
        throw std::invalid_argument("Error de sintaxis: token invalido '" +
                                    token + "'");
      pos++; // Consume el numero
    }
  }

  // Verifica que se haya consumido toda la expresion
  void verificarSintaxis() {
    parseExpression();
    if (pos != tokens.size())
      throw std::invalid_argument(
          "Error de sintaxis: tokens adicionales encontrados");
  }
};