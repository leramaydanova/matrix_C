#include "test.h"

START_TEST(mult_correct_matrix_1) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = 1;
      matrix2.matrix[i][j] = 2;
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], 6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(mult_correct_matrix_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 2, &matrix2);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 1;
  matrix1.matrix[1][2] = 2.5;
  matrix1.matrix[1][0] = 1.09;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = 2.22;
  matrix2.matrix[1][1] = 2;
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);

  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_float_eq(result.matrix[0][1], 4.22);
  ck_assert_double_eq(result.matrix[1][0], 1.09);
  ck_assert_float_eq(result.matrix[1][1], 2.4198);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(mult_correct_matrix_3) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &matrix2);
  matrix1.matrix[0][0] = 1;
  matrix2.matrix[0][0] = 2.22;
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 2.22);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(mult_uncorrect_matrix_1) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(1, 2, &matrix1);
  s21_create_matrix(1, 1, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(mult_uncorrect_matrix_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 2, &matrix1);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, NULL, &result), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(mult_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(1, 2, &matrix1);
  s21_create_matrix(1, 1, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, NULL), 1);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(mult_uncorrect_matrix_4) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(1, 2, &matrix1);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 1);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(mult_uncorrect_matrix_5) {
  matrix_t result = {0, 0, 0}, matrix2 = {0, 0, 0};
  s21_create_matrix(1, 2, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(NULL, &matrix2, NULL), 1);
  s21_remove_matrix(&matrix2);
}

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_mult_matrix=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, mult_correct_matrix_1);
  tcase_add_test(tc_core, mult_correct_matrix_2);
  tcase_add_test(tc_core, mult_correct_matrix_3);

  tcase_add_test(tc_core, mult_uncorrect_matrix_1);
  tcase_add_test(tc_core, mult_uncorrect_matrix_2);
  tcase_add_test(tc_core, mult_uncorrect_matrix_3);
  tcase_add_test(tc_core, mult_uncorrect_matrix_4);
  tcase_add_test(tc_core, mult_uncorrect_matrix_5);

  suite_add_tcase(s, tc_core);
  return s;
}
