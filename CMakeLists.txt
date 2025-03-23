cmake_minimum_required(VERSION 3.20)
project(ExpresionEvaluator CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregar el ejecutable primero
add_executable(${PROJECT_NAME} src/main.cpp)

# Luego agregar directorios de cabeceras
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
