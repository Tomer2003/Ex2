cmake_minimum_required(VERSION 3.0.0)
project(test1 VERSION 0.1.0)

include(CTest)
enable_testing()

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

add_executable(test1 main.cpp)

target_link_libraries(test1 bmp_tester BitMapFactory BitMap Headers Exceptions)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)