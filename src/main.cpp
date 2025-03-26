#include "ExpresionEvaluator.h"
#include "Parser.h"
#include <Variables.h>
#include <iostream>

int main(int argc, char *argv[]) {
  ExpresionEvaluator evaluator;
  Parser parser;
  std::string expresion = argv[1];

  std::cout << "|----Evaluador de expresiones----|" << std::endl;
  auto result = parser.Validar(expresion);
  std::string ValidExpresion = "";

  if (result.has_value()) {
    std::cout << "Sintaxis correcta" << std::endl;
    parser.setExpresion(ValidExpresion);
  } else {
    std::cout << result.error() << std::endl;
    return 1;
  }

  std::cout << "--Evaluacion--" << std::endl;
  evaluator.setExpresion(ValidExpresion);
  evaluator.EvaluarExpresion();
  std::cout << "|-----------------------------|" << std::endl;
  return 0;
}
