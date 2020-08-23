#include "ClassMatrix.hpp"
#include <iostream>

void printMatrix(const matrix::Matrix& matrix){
    for(int i = matrix.matrixGetHeight() - 1; i >= 0; --i){
        for(uint32_t j = 0; j < matrix.matrixGetWidth(); ++j){
            std::cout << matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main(){
    matrix::Matrix A(2, 2);
    matrix::Matrix B(2, 2);
    std::cout << "height: " << A.matrixGetHeight() << std::endl << "width: " << A.matrixGetWidth() << std::endl << std::endl;
    A.matrixSetValue(0, 0, 3);
    A.matrixSetValue(0, 1, 1);
    A.matrixSetValue(1, 0, 7);
    A.matrixSetValue(1, 1, 4);
    B.matrixSetValue(0, 0, 1);
    B.matrixSetValue(0, 1, 2);
    B.matrixSetValue(1, 0, 6);
    B.matrixSetValue(1, 1, 5);
    printMatrix(A);
    printMatrix(B);
    //printMatrix(A + B);
    //printMatrix(A * B);
    printMatrix(A * 3);
    









    return 0;
}