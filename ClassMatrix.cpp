#include <iostream>
#include "ClassMatrix.hpp"
#include "Exceptions.hpp"
extern "C" {
#include "matrix/Matrix.h"
}

namespace matrix{
    Matrix::Matrix(const uint32_t height, const uint32_t width) :m_width(width), m_height(height){
        Exceptions::throwAppopriateErrorIfHas(matrix_create(&this->m_pMatrix, m_height, m_width));
    }

    Matrix::Matrix(const Matrix& matrix) :m_width(matrix.m_width), m_height(matrix.m_height){
        Exceptions::throwAppopriateErrorIfHas(matrix_copy(&this->m_pMatrix, matrix.m_pMatrix));
    }

    Matrix::Matrix(Matrix&& matrix) :m_width(matrix.m_width), m_height(matrix.m_height){
        this->m_pMatrix = matrix.m_pMatrix;
        matrix.m_pMatrix = nullptr;
    }

    Matrix& Matrix::operator=(const Matrix& other){
        if(this != &other){
            matrix_destroy(this->m_pMatrix);
            *this = Matrix(other);
        }
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other){
         if(this != &other){
            matrix_destroy(this->m_pMatrix);
            this->m_pMatrix = other.m_pMatrix;
            this->m_height = other.m_height;
            this->m_width = other.m_width;
            other.m_pMatrix = nullptr;
        }
        return *this;
    }

    void Matrix::matrixSetValue(const uint32_t rowIndex, const uint32_t colIndex, const double value){
        Exceptions::throwAppopriateErrorIfHas(matrix_setValue(this->m_pMatrix, rowIndex, colIndex, value));
    }
    
    uint32_t Matrix::matrixGetHeight() const{
        uint32_t result;
        Exceptions::throwAppopriateErrorIfHas(matrix_getHeight(this->m_pMatrix, &result));
        return result;
    } 

    uint32_t Matrix::matrixGetWidth() const{
        uint32_t result;
        Exceptions::throwAppopriateErrorIfHas(matrix_getWidth(this->m_pMatrix, &result));
        return result;
    }
    
    double Matrix::operator()(const uint32_t rowIndex, const uint32_t colIndex) const{
        double value = 0;
        Exceptions::throwAppopriateErrorIfHas(matrix_getValue(this->m_pMatrix, rowIndex, colIndex, &value));
        return value;
    }

    Matrix Matrix::operator+(const Matrix& matrix) const{
        Matrix result(matrix.m_height, matrix.m_width);
        if(matrix.m_height == 0 || matrix.m_width == 0){
            throw Exceptions::ErrorMatrixSizeNotAppopriate();
        }
        Exceptions::throwAppopriateErrorIfHas(matrix_add(&result.m_pMatrix, this->m_pMatrix, matrix.m_pMatrix));
        return result;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const{
        std::cout << "mult!" << std::endl;
        Matrix result(matrix.m_height, this->m_height);
        if(matrix.m_height == 0 || this->m_height == 0){
            throw Exceptions::ErrorMatrixSizeNotAppopriate();
        }
        Exceptions::throwAppopriateErrorIfHas(matrix_multiplyMatrices(&result.m_pMatrix, this->m_pMatrix, matrix.m_pMatrix));
        return result; 
    }

    Matrix Matrix::operator*(const double scalar) const{
        std::cout << "scalar!" << std::endl;
        Matrix result(this->m_height, this->m_width);
        if(this->m_height == 0 || this->m_width == 0){
            throw Exceptions::ErrorMatrixSizeNotAppopriate();
        }
        Exceptions::throwAppopriateErrorIfHas(matrix_multiplyWithScalar(result.m_pMatrix, scalar));
        return result;
    }

    Matrix::~Matrix(){
        matrix_destroy(this->m_pMatrix);
    }
        
    Matrix operator*(double scalar, Matrix& matrix){
        return matrix * scalar;
    }  
}