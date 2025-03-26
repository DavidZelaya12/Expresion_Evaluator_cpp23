cmake_minimum_required(VERSION 3.20)
project(ExpresionEvaluator CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Runner de tests
add_executable(TestRunner test/TestRunner.cpp)
target_include_directories(TestRunner PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(TestRunner PRIVATE Catch2::Catch2WithMain)
