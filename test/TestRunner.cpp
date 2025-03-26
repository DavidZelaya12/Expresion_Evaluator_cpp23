#define CATCH_CONFIG_MAIN
#include "../lib/ExpresionEvaluator.h"
#include "catch2/catch_test_macros.hpp"
#include <ExpresionEvaluator.h>
#include <Parser.h>

ExpresionEvaluator evaluator;
Parser parser;

TEST_CASE("Evaluar expresiones", "[ExpresionEvaluator]") {
  REQUIRE(evaluator.EvaluarExpresion("2 + 2") == 4);
  REQUIRE(evaluator.EvaluarExpresion("5 - 3") == 2);
  REQUIRE(evaluator.EvaluarExpresion("10 * 2") == 20);
  REQUIRE(evaluator.EvaluarExpresion("8 / 4") == 2);
  REQUIRE(evaluator.EvaluarExpresion("6 + 7 - 2") == 11);
  REQUIRE(evaluator.EvaluarExpresion("3 * (4 + 5)") == 27);
  REQUIRE(evaluator.EvaluarExpresion("(10 / 2) + 3") == 8);
  REQUIRE(evaluator.EvaluarExpresion("15 - 3 * 2") == 9);
  REQUIRE(evaluator.EvaluarExpresion("18 / (3 + 3)") == 3);
  REQUIRE(evaluator.EvaluarExpresion("2 + 3 * 4 - 6 / 2") == 11);
}

TEST_CASE("Evaluar Errores de sintaxis y de calculo", "[ExpresionEvaluator]") {
  auto result = parser.Validar("5 + * 3");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("(4 + 3");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("6 -");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("6 6 + 3");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("* 2 + 3");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("12 ++ 4");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("(7 * 2))");
  REQUIRE_FALSE(result.has_value());

  result = parser.Validar("");
  REQUIRE_FALSE(result.has_value());

  REQUIRE_THROWS(evaluator.EvaluarExpresion("5 / 0"));
  REQUIRE_THROWS(evaluator.EvaluarExpresion("5/(10-10)/(2-2)"));
}
