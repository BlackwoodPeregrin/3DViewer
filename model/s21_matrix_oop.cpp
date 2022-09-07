#include "s21_matrix_oop.h"

#include <cstring>

S21Matrix::S21Matrix() { distributionMemory(3, 3); }

S21Matrix::S21Matrix(int rows, int columns) {
  if (rows < 1 || columns < 1) {
    throw std::invalid_argument("ERROR, invalid input");
  }
  distributionMemory(rows, columns);
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  matrix = nullptr;
  *this = other;
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  check_constructor(other);
  _rows = other._rows;
  _columns = other._columns;
  matrix = other.matrix;

  other.matrix = nullptr;
  other._rows = 0;
  other._columns = 0;
}

S21Matrix::~S21Matrix() { clear(); }

void S21Matrix::clear() {
  if (matrix != nullptr) {
    for (int i = 0; i < _rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
    _rows = 0;
    _columns = 0;
  }
}

int S21Matrix::getRows() const { return _rows; }

int S21Matrix::getColumns() const { return _columns; }

void S21Matrix::setRows(int rows) {
  S21Matrix cur(rows, _columns);

  for (int i = 0; i < cur._rows && i < _rows; i++) {
    for (int j = 0; j < cur._columns; j++) {
      cur.matrix[i][j] = matrix[i][j];
    }
  }
  *this = cur;
}

void S21Matrix::setColumns(int columns) {
  S21Matrix cur(_rows, columns);

  for (int i = 0; i < cur._rows; i++) {
    for (int j = 0; j < cur._columns && i < _columns; j++) {
      cur.matrix[i][j] = matrix[i][j];
    }
  }
  *this = cur;
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    return false;
  }
  for (int i = 0; i < _rows; i++) {
    if (memcmp(matrix[i], other.matrix[i], _columns * sizeof(double)) != 0) {
      return false;
    }
  }
  return true;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  check_equal_rows_columns(other);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      matrix[i][j] += other.matrix[i][j];
    }
  }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  check_equal_rows_columns(other);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      matrix[i][j] -= other.matrix[i][j];
    }
  }
}

void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      matrix[i][j] *= num;
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (_columns != other._rows) {
    throw std::invalid_argument(
        "ERROR in mult matrix columns unequal rows mult matrix");
  }
  S21Matrix result(_rows, other._columns);
  for (int i = 0; i < result._rows; i++)
    for (int j = 0; j < result._columns; j++)
      for (int k = 0; k < _columns; k++)
        result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
  *this = result;
}

S21Matrix S21Matrix::transpose() {
  S21Matrix newMatrix(_columns, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      newMatrix.matrix[j][i] = matrix[i][j];
    }
  }
  return newMatrix;
}

bool swapStrMatrix(double** Matrix, int row, int rowsMatrix, int column) {
  bool swap = false;
  double* swapStr = new double[rowsMatrix];

  for (int i = row + 1; i < rowsMatrix && swap != true; i++) {
    if (Matrix[i][column] != 0.0) {
      swap = true;
      for (int k = 0; k < rowsMatrix; k++) {
        swapStr[k] = Matrix[i][k];
        Matrix[i][k] = Matrix[row][k];
        Matrix[row][k] = swapStr[k];
      }
    }
  }
  delete[] swapStr;
  return swap;
}

void subStrMatrix(double** Matrix, int row, int rowsMatrix, int column) {
  double multiplier = Matrix[row][column] / Matrix[column][column];
  for (int j = 0; j < rowsMatrix; j++) {
    Matrix[row][j] -= multiplier * Matrix[column][j];
  }
}

double S21Matrix::determinant() {
  check_square_matrix();
  if (_rows == 1) {
    return matrix[0][0];
  }

  double determinant = 1;
  int sign = 1;

  S21Matrix copyMatrix(*this);

  for (int j = 0; j < copyMatrix._columns; j++) {
    if (copyMatrix.matrix[j][j] == (double)0) {
      if (swapStrMatrix(copyMatrix.matrix, j, copyMatrix._rows, j)) {
        sign *= -1;
      } else {
        continue;
      }
    }
    for (int i = j + 1; i < copyMatrix._rows; i++) {
      if (copyMatrix.matrix[i][j] != (double)0) {
        subStrMatrix(copyMatrix.matrix, i, copyMatrix._rows, j);
      }
    }
  }
  for (int i = 0; i < copyMatrix._rows; i++) {
    determinant *= copyMatrix.matrix[i][i];
  }
  if (sign < 0) {
    determinant *= -1.0;
  }

  return determinant;
}

double getMinorMatrix(double** Matrix, int row, int column, int rowsMatrix,
                      int columnsMatrix) {
  S21Matrix minorMatrix(rowsMatrix - 1, columnsMatrix - 1);
  int tmp1 = 0, tmp2 = 0;
  for (int i = 0; i < rowsMatrix; i++) {
    if (i == row) continue;
    for (int j = 0; j < columnsMatrix; j++) {
      if (j == column) continue;
      minorMatrix(tmp1, tmp2) = Matrix[i][j];
      tmp2++;
    }
    tmp1++;
    tmp2 = 0;
  }
  return minorMatrix.determinant();
}

S21Matrix S21Matrix::calc_complements() {
  check_square_matrix();

  S21Matrix newMatrix(_rows, _columns);
  if (_rows == 1) {
    newMatrix.matrix[0][0] = 1;
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        newMatrix.matrix[i][j] =
            pow(-1, i + j) * getMinorMatrix(matrix, i, j, _rows, _columns);
      }
    }
  }
  return newMatrix;
}

S21Matrix S21Matrix::inverse_matrix() {
  if (determinant() == 0.0) {
    throw std::invalid_argument(
        "ERROR determinant equality zero");  /////// epsilon
  }

  S21Matrix calcMatrix = calc_complements();
  S21Matrix inverseMatrix = calcMatrix.transpose();
  inverseMatrix.mul_number(1.0 / determinant());

  return inverseMatrix;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  check_constructor(other);
  clear();
  distributionMemory(other._rows, other._columns);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      matrix[i][j] = other.matrix[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix newMatrix(*this);
  newMatrix.sum_matrix(other);
  return newMatrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix newMatrix(*this);
  newMatrix.sub_matrix(other);
  return newMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix newMatrix(*this);
  newMatrix.mul_matrix(other);
  return newMatrix;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix newMatrix(*this);
  newMatrix.mul_number(num);
  return newMatrix;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix res(other);
  res.mul_number(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  sum_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  sub_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  mul_matrix(other);
  return *this;
}

double S21Matrix::operator()(int row, int column) const {
  if (_rows <= row || _columns <= column) {
    throw std::out_of_range("ERROR index out of range");
  }
  if (row < 0 || column < 0) {
    throw std::invalid_argument("ERROR index is negative");
  }
  return matrix[row][column];
}

/*--------------------afinity tranformation-------------------*/

void S21Matrix::setToIdentity() {
  matrix[0][0] = 1.0f;
  matrix[0][1] = 0.0f;
  matrix[0][2] = 0.0f;
  matrix[0][3] = 0.0f;
  matrix[1][0] = 0.0f;
  matrix[1][1] = 1.0f;
  matrix[1][2] = 0.0f;
  matrix[1][3] = 0.0f;
  matrix[2][0] = 0.0f;
  matrix[2][1] = 0.0f;
  matrix[2][2] = 1.0f;
  matrix[2][3] = 0.0f;
  matrix[3][0] = 0.0f;
  matrix[3][1] = 0.0f;
  matrix[3][2] = 0.0f;
  matrix[3][3] = 1.0f;
}

void S21Matrix::translateX(const float& x) { matrix[0][3] = x; }

void S21Matrix::translateY(const float& y) { matrix[1][3] = y; }

void S21Matrix::translateZ(const float& z) { matrix[2][3] = z; }

void S21Matrix::rotateX(const float& radian) {
  float deg = radian * float(M_PI / 180);
  float c = cos(deg);
  float s = sin(deg);
  float tmp;
  matrix[1][0] = (tmp = matrix[1][0]) * c + matrix[2][0] * s;
  matrix[2][0] = matrix[2][0] * c - tmp * s;
  matrix[1][1] = (tmp = matrix[1][1]) * c + matrix[2][1] * s;
  matrix[2][1] = matrix[2][1] * c - tmp * s;
  matrix[1][2] = (tmp = matrix[1][2]) * c + matrix[2][2] * s;
  matrix[2][2] = matrix[2][2] * c - tmp * s;
  matrix[1][3] = (tmp = matrix[1][3]) * c + matrix[2][3] * s;
  matrix[2][3] = matrix[2][3] * c - tmp * s;
}

void S21Matrix::rotateY(const float& radian) {
  float deg = radian * float(M_PI / 180);
  float c = cos(deg);
  float s = sin(deg);
  float tmp;
  matrix[2][0] = (tmp = matrix[2][0]) * c + matrix[0][0] * s;
  matrix[0][0] = matrix[0][0] * c - tmp * s;
  matrix[2][1] = (tmp = matrix[2][1]) * c + matrix[0][1] * s;
  matrix[0][1] = matrix[0][1] * c - tmp * s;
  matrix[2][2] = (tmp = matrix[2][2]) * c + matrix[0][2] * s;
  matrix[0][2] = matrix[0][2] * c - tmp * s;
  matrix[2][3] = (tmp = matrix[2][3]) * c + matrix[0][3] * s;
  matrix[0][3] = matrix[0][3] * c - tmp * s;
}

void S21Matrix::rotateZ(const float& radian) {
  float deg = radian * float(M_PI / 180);
  float c = cos(deg);
  float s = sin(deg);
  float tmp;
  matrix[0][0] = (tmp = matrix[0][0]) * c + matrix[1][0] * s;
  matrix[1][0] = matrix[1][0] * c - tmp * s;
  matrix[0][1] = (tmp = matrix[0][1]) * c + matrix[1][1] * s;
  matrix[1][1] = matrix[1][1] * c - tmp * s;
  matrix[0][2] = (tmp = matrix[0][2]) * c + matrix[1][2] * s;
  matrix[1][2] = matrix[1][2] * c - tmp * s;
  matrix[0][3] = (tmp = matrix[0][3]) * c + matrix[1][3] * s;
  matrix[1][3] = matrix[1][3] * c - tmp * s;
}

void S21Matrix::scale(const float scale) {
  matrix[0][0] *= scale;
  matrix[0][1] *= scale;
  matrix[0][2] *= scale;
  matrix[1][0] *= scale;
  matrix[1][1] *= scale;
  matrix[1][2] *= scale;
  matrix[2][0] *= scale;
  matrix[2][1] *= scale;
  matrix[2][2] *= scale;
}

/*------------------------------------------------------*/

S21Matrix& S21Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

double& S21Matrix::operator()(int row, int column) {
  if (_rows <= row || _columns <= column) {
    throw std::out_of_range("ERROR index out of range");
  }
  if (row < 0 || column < 0) {
    throw std::invalid_argument("ERROR index is negative");
  }
  return matrix[row][column];
}

void S21Matrix::distributionMemory(const int rows, const int columns) {
  _rows = rows;
  _columns = columns;
  matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) {
    matrix[i] = new double[_columns]{};
  }
}

void S21Matrix::check_equal_rows_columns(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::invalid_argument("ERROR, different dimensions of matrices");
  }
}

void S21Matrix::check_square_matrix() {
  if (_rows != _columns) {
    throw std::invalid_argument("ERROR rows unequal columns");
  }
}

void S21Matrix::check_constructor(const S21Matrix& other) {
  if (this == &other) {
    throw std::invalid_argument(
        "ERROR in costruct copy, can't copy yourself object");
  }
}
