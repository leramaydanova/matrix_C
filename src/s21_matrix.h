#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct matrix_struct
{
    double **matrix;
    int rows;
    int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_or_sum(matrix_t *A, matrix_t *B, matrix_t *result, double func(double, double));
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_is_correct_matrix(matrix_t *A);
int s21_is_equal_size(matrix_t *A, matrix_t *B);
double s21_sub(double a, double b);
double s21_sum(double a, double b);
void s21_fill_minor(matrix_t *A, int row, int col, matrix_t *minor);
void s21_calc_determinant(matrix_t *A, double *result);

#endif