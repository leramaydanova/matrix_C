#include "test.h"

START_TEST(determinant_correct_matrix_1) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_correct_matrix_2) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(4, 4, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[3][2] = 1;
  matrix1.matrix[3][3] = 2;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 4);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_correct_matrix_3) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(4, 4, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[3][2] = 1;
  matrix1.matrix[3][3] = 2.2;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 4.4);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_correct_matrix_4) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 2);
  s21_remove_matrix(&matrix1);
}

START_TEST(determinant_correct_matrix_5) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 1;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(determinant_correct_matrix_6) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[1][0] = 3;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_double_eq(result, 0);
  s21_remove_matrix(&matrix1);
}

START_TEST(determinant_uncorrect_matrix_1) {
  matrix_t matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_determinant(&matrix1, NULL), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(determinant_uncorrect_matrix_2) {
  double result;
  ck_assert_int_eq(s21_determinant(NULL, &result), 1);
}

START_TEST(determinant_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 1);
}

START_TEST(determinant_uncorrect_matrix_4) {
  matrix_t matrix1 = {0, 0, 0};
  double result;
  s21_create_matrix(3, 4, &matrix1);
  ck_assert_int_eq(s21_determinant(&matrix1, &result), 2);
  s21_remove_matrix(&matrix1);
}

Suite *test_determinant(void) {
  Suite *s = suite_create("\033[45m-=s21_determinant=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, determinant_correct_matrix_1);
  tcase_add_test(tc_core, determinant_correct_matrix_2);
  tcase_add_test(tc_core, determinant_correct_matrix_3);
  tcase_add_test(tc_core, determinant_correct_matrix_4);
  tcase_add_test(tc_core, determinant_correct_matrix_5);

  tcase_add_test(tc_core, determinant_uncorrect_matrix_1);
  tcase_add_test(tc_core, determinant_uncorrect_matrix_2);
  tcase_add_test(tc_core, determinant_uncorrect_matrix_3);
  tcase_add_test(tc_core, determinant_uncorrect_matrix_4);

  suite_add_tcase(s, tc_core);
  return s;
}
