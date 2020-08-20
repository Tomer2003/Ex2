cmake_minimum_required(VERSION 3.0.0)
project(matrix VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)



add_executable(matrix main.cpp)


file(GLOB matrix_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

target_sources(matrix PRIVATE ${matrix_SRC})

target_link_libraries(matrix ${CMAKE_CURRENT_SOURCE_DIR}/libmatrix.so)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


