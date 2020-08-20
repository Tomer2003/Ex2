
#pragma once
#include <stdint.h>
#include "Matrix.h"

namespace matrix{

    class Matrix{
    public:
        Matrix(const uint32_t height, const uint32_t width);

        Matrix(const Matrix& matrix);

        Matrix(Matrix&& matrix);

        Matrix& operator=(const Matrix& other);

        Matrix& operator=(Matrix&& other);

        uint32_t matrixGetHeight() const;

        uint32_t matrixGetWidth() const;

        void matrixSetValue(const uint32_t rowIndex, const uint32_t colIndex, const double value);

        double operator()(const uint32_t rowIndex, const uint32_t colIndex) const;

        Matrix operator+(const Matrix& matrix) const;

        Matrix operator*(const Matrix& matrix) const;

        Matrix operator*(const double scalar) const;

        ~Matrix();

    private:
        uint32_t width;
        uint32_t height;
        PMatrix pMatrix;
    };

    Matrix operator*(double scalar, Matrix& matrix);
};