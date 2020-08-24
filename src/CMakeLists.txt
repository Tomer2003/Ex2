cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_library(
    BitMapFactory
    BitMapFactory.cpp
    BitMapFactory.hpp
)

add_library(
    BitMap
    BitMap.cpp
    BitMap.hpp
)

add_library(
    Headers
    Headers.cpp
    Headers.hpp
)

add_library(
    bmp_tester
    bmp_tester.cpp
    bmp_tester.hpp
)

add_library(
    Exceptions
    Exceptions.cpp
    Exceptions.hpp
)

add_library(
    BMPFunctions
    BitMapHelpFunctions.cpp
    BitMapHelpFunctions.hpp
)

add_executable(ex2 main.cpp)

target_link_libraries(ex2 bmp_tester BitMapFactory BitMap Headers Exceptions BMPFunctions)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)