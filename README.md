# Expresion_Evaluator_cpp23

Proyecto en C++23 para evaluar expresiones matemáticas en notación infija. El flujo principal es sencillo: primero se valida la sintaxis de la expresión y luego se convierte a notación postfija para ejecutar la evaluación.

## Características

- Soporte para operaciones aritméticas básicas: suma, resta, multiplicación, división, módulo y potencia.
- Manejo de paréntesis para cambiar la precedencia de las operaciones.
- Validación de sintaxis antes de evaluar la expresión.
- Soporte para números enteros y decimales.
- Soporte para variables cargadas desde `variables.txt`.
- Implementación con características de C++23, como `std::expected`, `std::float64_t` y `std::unreachable`.
- Suite de pruebas automatizadas con Catch2.

## Requisitos

- Compilador con soporte para C++23.
- CMake 3.20 o superior.
- Internet al configurar el proyecto, ya que Catch2 se descarga con `FetchContent`.

## Estructura del proyecto

- `src/main.cpp`: punto de entrada de la aplicación.
- `lib/ExpresionEvaluator.h`: conversión a postfija y evaluación de expresiones.
- `lib/Parser.h`: tokenización y validación sintáctica.
- `lib/Validator.h`: validación de operadores y precedencia.
- `lib/Variables.h`: carga y gestión de variables.
- `variables.txt`: archivo de variables iniciales.
- `test/TestRunner.cpp`: pruebas unitarias con Catch2.

## Compilación

```bash
cmake -S . -B build
cmake --build build
```

## Ejecución

El ejecutable principal espera una expresión como argumento:

```bash
./build/ExpresionEvaluator "3 * (4 + 5)"
```

En Windows, el nombre del ejecutable puede variar según el generador de CMake usado.

## Pruebas

El proyecto incluye un ejecutable de pruebas llamado `TestRunner`.

```bash
cmake --build build --target TestRunner
./build/TestRunner
```

## Notas

- La evaluación imprime en consola la expresión infija, su forma postfija y el resultado final.
- Si la expresión contiene variables, el parser intenta resolverlas usando las variables cargadas desde `variables.txt`.
- Si una variable no existe, el programa solicita su valor por consola.
