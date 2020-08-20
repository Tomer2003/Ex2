#include <iostream>
#include "ClassMatrix.hpp"

namespace matrix{
    Matrix::Matrix(const uint32_t height, const uint32_t width) :width(width), height(height){
        matrix_create(&this->pMatrix, height, width);
    }

    Matrix::Matrix(const Matrix& matrix) :width(matrix.width), height(matrix.height){
        matrix_copy(&this->pMatrix, matrix.pMatrix);
    }

    Matrix::Matrix(Matrix&& matrix) :width(matrix.width), height(matrix.height){
        this->pMatrix = matrix.pMatrix;
        matrix.pMatrix = nullptr;
    }

    Matrix& Matrix::operator=(const Matrix& other){
        if(this != &other){
            matrix_destroy(this->pMatrix);
            *this = Matrix(other);
        }
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other){
         if(this != &other){
            matrix_destroy(this->pMatrix);
            this->pMatrix = other.pMatrix;
            this->height = other.height;
            this->width = other.width;
            other.pMatrix = nullptr;
        }
        return *this;
    }

    void Matrix::matrixSetValue(const uint32_t rowIndex, const uint32_t colIndex, const double value){
        matrix_setValue(this->pMatrix, rowIndex, colIndex, value);
    }
    
    uint32_t Matrix::matrixGetHeight() const{
        uint32_t result;
        matrix_getHeight(this->pMatrix, &result);
        return result;
    } 

    uint32_t Matrix::matrixGetWidth() const{
        uint32_t result;
        matrix_getWidth(this->pMatrix, &result);
        return result;
    }
    
    double Matrix::operator()(const uint32_t rowIndex, const uint32_t colIndex) const{
        double value = 0;
        matrix_getValue(this->pMatrix, rowIndex, colIndex, &value);
        return value;
    }

    Matrix Matrix::operator+(const Matrix& matrix) const{
        Matrix result(matrix.height, matrix.width);
        matrix_add(&result.pMatrix, this->pMatrix, matrix.pMatrix);
        return result;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const{
        Matrix result(matrix.height, this->height);
        matrix_multiplyMatrices(&result.pMatrix, this->pMatrix, matrix.pMatrix);
        return result; 
    }

    Matrix Matrix::operator*(const double scalar) const{
        Matrix result(this->height, this->width);
        matrix_multiplyWithScalar(result.pMatrix, scalar);
        return result;
    }

    Matrix::~Matrix(){
        matrix_destroy(this->pMatrix);
    }
        
    Matrix operator*(double scalar, Matrix& matrix){
        return matrix * scalar;
    }
};