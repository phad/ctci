#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rows_;
  int cols_;
  int* data_;
} Matrix;

Matrix make(int rows, int cols) {
  Matrix result;
  result.rows_ = rows;
  result.cols_ = cols;
  result.data_ = (int*) malloc(rows * cols * sizeof(int));
  memset(result.data_, 0, rows * cols * sizeof(int));
  return result;
}

void release(Matrix mtx) {
  free(mtx.data_);
  mtx.rows_ = 0;
  mtx.cols_ = 0;
  mtx.data_ = NULL;
}

void set(Matrix mtx, int row, int col, int value) {
  assert(row >= 0 && row < mtx.rows_);
  assert(col >= 0 && col < mtx.cols_);
  mtx.data_[col + row * mtx.cols_] = value;
}

int get(Matrix mtx, int row, int col) {
  assert(row >= 0 && row < mtx.rows_);
  assert(col >= 0 && col < mtx.cols_);
  return mtx.data_[col + row * mtx.cols_];
}

void print(Matrix mtx) {
  printf("\n[\n");
  int row, col;
  for (row = 0; row < mtx.rows_; ++row) {
    for (col = 0; col < mtx.cols_; ++col) {
      printf("%3d ", get(mtx, row, col));
    }
    printf("\n");
  }
  printf("]\n");
}

Matrix rotate(Matrix input) {
  Matrix result = make(input.cols_, input.rows_);
  int row, col;
  for (row = 0; row < result.rows_; ++row) {
    for (col = 0; col < result.cols_; ++col) {
      set(result, row, col, get(input, col, row));
    }
  }
  return result;
}

int main(int argc, char **argv) {
  Matrix m = make(3, 4);
  set(m, 0, 0, 1); set(m, 0, 1, 2);  set(m, 0, 2, 3);  set(m, 0, 3, 4);
  set(m, 1, 0, 5); set(m, 1, 1, 6);  set(m, 1, 2, 7);  set(m, 1, 3, 8);
  set(m, 2, 0, 9); set(m, 2, 1, 10); set(m, 2, 2, 11); set(m, 2, 3, 12);
  print(m);

  Matrix r = rotate(m);
  print(r);

  release(m);
  release(r);
  return 0;
}