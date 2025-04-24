#include "test.h"

START_TEST(mult_number_correct_1) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(3, 3, &matrix1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_mult_number(&matrix1, 2, &result), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], 2);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(mult_number_correct_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(3, 4, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[1][2] = 3;
  matrix1.matrix[0][1] = 1;
  matrix1.matrix[1][1] = 2.5;
  matrix1.matrix[2][3] = 4;
  matrix1.matrix[1][0] = 1.09;

  ck_assert_int_eq(s21_mult_number(&matrix1, 5.2, &result), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result.matrix[i][j], matrix1.matrix[i][j] * 5.2);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(mult_number_correct_3) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 1;
  ck_assert_int_eq(s21_mult_number(&matrix1, 3.333333, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 3.333333);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}

START_TEST(mult_number_uncorrect_1) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_mult_number(NULL, 1, &result), 1);
}
START_TEST(mult_number_uncorrect_2) {
  matrix_t matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_mult_number(&matrix1, 1, NULL), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(mult_number_uncorrect_3) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  ck_assert_int_eq(s21_mult_number(&matrix1, 1, &result), 1);
}

Suite *test_mult_number(void) {
  Suite *s = suite_create("\033[45m-=s21_mult_number=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, mult_number_correct_1);
  tcase_add_test(tc_core, mult_number_correct_2);
  tcase_add_test(tc_core, mult_number_correct_3);

  tcase_add_test(tc_core, mult_number_uncorrect_1);
  tcase_add_test(tc_core, mult_number_uncorrect_2);
  tcase_add_test(tc_core, mult_number_uncorrect_3);

  suite_add_tcase(s, tc_core);
  return s;
}
