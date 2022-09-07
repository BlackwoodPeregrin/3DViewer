#pragma once

#include <QMatrix4x4>

#include "s21_matrix_oop.h"

namespace s21_3DViewer {
class Adapter : public QMatrix4x4 {
 private:
  Adapter() : QMatrix4x4() {}
  explicit Adapter(const S21Matrix &matrix) = delete;
  Adapter &operator=(Adapter const &) = delete;

 public:
  static Adapter &getInstance() {
    static Adapter adapter;
    return adapter;
  }

  QMatrix4x4 adapt(const S21Matrix &matrix) {
    QMatrix4x4 instance;
    if (matrix.getRows() == 4 && matrix.getColumns() == 4) {
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          instance(i, j) = matrix(i, j);
        }
      }
    }
    return instance;
  }
};
}  // namespace s21_3DViewer
