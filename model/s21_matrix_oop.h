#pragma once

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int _rows, _columns;
  double** matrix;
  void distributionMemory(const int rows, const int columns);
  void check_equal_rows_columns(const S21Matrix& other);
  void check_constructor(const S21Matrix& other);
  void check_square_matrix();

 public:
  // constructors
  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  // destructor
  ~S21Matrix();

  /* accessors */
  int getRows() const;
  int getColumns() const;
  /* mutators */
  void setRows(int rows);
  void setColumns(int columns);

  /* Checks matrices for equality among themselves */
  bool eq_matrix(const S21Matrix& other);
  /* Adds a second matrix to the observer */
  void sum_matrix(const S21Matrix& other);
  /* Subtracts another from the current matrix */
  void sub_matrix(const S21Matrix& other);
  /* Multiplies the current matrix by a number */
  void mul_number(const double num);
  /* Multiplies the current matrix by the second */
  void mul_matrix(const S21Matrix& other);
  /* Creates a new transposed matrix from the current one and returns it */
  S21Matrix transpose();
  /* Calculates and returns the determinant of the current matrix */
  double determinant();
  /* Calculates the matrix of complements from the current one and returns it */
  S21Matrix calc_complements();
  /* Calculates and returns an inverse matrix */
  S21Matrix inverse_matrix();
  /* Clear memory in matrix */
  void clear();
  /* operators overloads */
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(const double num, const S21Matrix& other);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int column);
  double operator()(int row, int column) const;

  /* afinity tranformation */
  void setToIdentity();
  void translateX(const float& x);
  void translateY(const float& y);
  void translateZ(const float& z);
  void rotateX(const float& radian);
  void rotateY(const float& radian);
  void rotateZ(const float& radian);
  void scale(const float scale);
};
