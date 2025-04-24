#include "s21_matrix.h"

int s21_is_correct_matrix(matrix_t *A) {
  int res = 0;
  if (A && A->columns > 0 && A->rows > 0) {
    res = 1;
  }
  return res;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (result == NULL || rows <= 0 || columns <= 0) {
    res = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = A->rows - 1; i >= 0; i--) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (s21_is_correct_matrix(A) && s21_is_correct_matrix(B) &&
      s21_is_equal_size(A, B)) {
    int rows = A->rows;
    int columns = A->columns;
    for (int i = 0; i < rows && res; i++) {
      for (int j = 0; j < columns && res; j++) {
        double diff = (A->matrix[i][j] - fmod(A->matrix[i][j], 0.0000001)) -
                      (B->matrix[i][j] - fmod(B->matrix[i][j], 0.0000001));
        if (diff) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_is_equal_size(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns);
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sub_or_sum(A, B, result, s21_sum);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sub_or_sum(A, B, result, s21_sub);
}

int s21_sub_or_sum(matrix_t *A, matrix_t *B, matrix_t *result,
                   double func(double, double)) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B) ||
      result == NULL) {
    res = 1;
  } else if (!s21_is_equal_size(A, B)) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = func(A->matrix[i][j], B->matrix[i][j]);
      }
    }
  }
  return res;
}

double s21_sub(double a, double b) { return a - b; }

double s21_sum(double a, double b) { return a + b; }

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    res = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B) ||
      result == NULL) {
    res = 1;
  } else if (A->columns != B->rows) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int n = 0; n < A->columns; n++) {
          result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    res = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (A->columns == 1) {
    if (A->matrix[0][0]) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
    } else {
      res = 2;
    }
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (det) {
      matrix_t minors, minorsT;
      s21_calc_complements(A, &minors);
      s21_transpose(&minors, &minorsT);
      s21_mult_number(&minorsT, 1 / det, result);
      s21_remove_matrix(&minors);
      s21_remove_matrix(&minorsT);
    } else {
      res = 2;
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;

  if (!s21_is_correct_matrix(A) || result == NULL) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    *result = 0;
    s21_calc_determinant(A, result);
  }
  return res;
}

void s21_calc_determinant(matrix_t *A, double *result) {
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int j = 0; j < A->columns; j++) {
      double minor_det = 0;
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      s21_fill_minor(A, 0, j, &minor);
      s21_determinant(&minor, &minor_det);
      *result += A->matrix[0][j] * minor_det * ((j % 2 == 0) ? 1 : -1);
      s21_remove_matrix(&minor);
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (A->columns == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double minor_det = 0;
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        s21_fill_minor(A, i, j, &minor);
        s21_determinant(&minor, &minor_det);
        result->matrix[i][j] = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
        s21_remove_matrix(&minor);
      }
    }
  }
  return res;
}

void s21_fill_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  int minor_row = 0, minor_col;
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      minor_col = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != col) {
          minor->matrix[minor_row][minor_col] = A->matrix[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
}