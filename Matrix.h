// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix {

  int rows;
  int cols;
  float *list;

 public:

  Matrix(int rows, int cols);

  Matrix();

  Matrix(const Matrix& other);

  ~Matrix();

  int get_rows() const;

  int get_cols() const;

  Matrix& transpose();

  Matrix& vectorize();

  void plain_print() const;

  Matrix dot(Matrix const& m) const;

  float norm() const;

  Matrix operator +(const Matrix& rhs) const;

  Matrix& operator = (const Matrix& rhs);

  Matrix operator *(const Matrix& rhs) const;

  Matrix operator*(float  num) const;

  friend Matrix operator *( float num, const Matrix& lhs);

  Matrix& operator +=(const Matrix& rhs);

  float& operator ()(int a, int b) const;

  float& operator ()(int a, int b);

  float operator [](unsigned int idx) const;

  float& operator [](unsigned int idx);

  friend std::ostream & operator <<(std:: ostream &os, const Matrix &other);

  friend std::istream & operator >>(std:: istream &is, const Matrix &other);
};
#endif //MATRIX_H


