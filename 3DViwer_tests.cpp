#include <gtest/gtest.h>

#include "model/s21_matrix_oop.h"

TEST(viwerTest, test_translateX) {
  S21Matrix matrix(4, 4);
  matrix(0, 3) = 7;
  matrix.translateX(10);

  ASSERT_EQ(matrix(0, 3), 10);
}

TEST(viwerTest, test_translateY) {
  S21Matrix matrix(4, 4);
  matrix(1, 3) = 7;
  matrix.translateY(10);

  ASSERT_EQ(matrix(1, 3), 10);
}

TEST(viwerTest, test_translateZ) {
  S21Matrix matrix(4, 4);
  matrix(2, 3) = 7;
  matrix.translateZ(10);

  ASSERT_EQ(matrix(2, 3), 10);
}

TEST(viwerTest, test_rotateX) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;

  matrix.rotateX(20);

  ASSERT_EQ(matrix(1, 0), 0);
  ASSERT_EQ(matrix(1, 1), 0.93969261646270751953);
  ASSERT_EQ(matrix(1, 2), 0.34202012419700622559);
  ASSERT_EQ(matrix(1, 3), 0);
  ASSERT_EQ(matrix(2, 0), 0);
  ASSERT_EQ(matrix(2, 1), -0.34202012419700622559);
  ASSERT_EQ(matrix(2, 2), 0.93969261646270751953);
  ASSERT_EQ(matrix(2, 3), 0);
}

TEST(viwerTest, test_rotateY) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;

  matrix.rotateY(90);

  ASSERT_EQ(matrix(1, 0), 0);
  ASSERT_EQ(matrix(1, 1), 1);
  ASSERT_EQ(matrix(1, 2), 0);
  ASSERT_EQ(matrix(1, 3), 0);
  ASSERT_EQ(matrix(2, 0), 1);
  ASSERT_EQ(matrix(2, 1), 0);
  ASSERT_EQ(matrix(2, 2), -4.3711388286737928865e-08);
  ASSERT_EQ(matrix(2, 3), 0);
}

TEST(viwerTest, test_rotateZ) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;

  matrix.rotateZ(90);

  ASSERT_EQ(matrix(1, 0), -1);
  ASSERT_EQ(matrix(1, 1), -4.3711388286737928865e-08);
  ASSERT_EQ(matrix(1, 2), 0);
  ASSERT_EQ(matrix(1, 3), 0);
  ASSERT_EQ(matrix(2, 0), 0);
  ASSERT_EQ(matrix(2, 1), 0);
  ASSERT_EQ(matrix(2, 2), 1);
  ASSERT_EQ(matrix(2, 3), 0);
}

TEST(viwerTest, test_scale) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;

  matrix.scale(9);

  ASSERT_EQ(matrix(0, 0), 9);
  ASSERT_EQ(matrix(1, 1), 9);
  ASSERT_EQ(matrix(2, 2), 9);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

