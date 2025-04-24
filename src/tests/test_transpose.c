#include "test.h"

START_TEST(transpose_correct_matrix_1) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(3, 3, &matrix1);
  for (int i = 1; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_transpose(&matrix1, &result), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 0)
        ck_assert_double_eq(result.matrix[i][j], 0);
      else
        ck_assert_double_eq(result.matrix[i][j], 1);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(transpose_correct_matrix_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 1;
  ck_assert_int_eq(s21_transpose(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(transpose_uncorrect_matrix_1) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_transpose(NULL, &result), 1);
}

START_TEST(transpose_uncorrect_matrix_2) {
  matrix_t matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_transpose(&matrix1, NULL), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(transpose_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  ck_assert_int_eq(s21_transpose(&matrix1, &result), 1);
}

Suite *test_transpose(void) {
  Suite *s = suite_create("\033[45m-=s21_transpose=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, transpose_correct_matrix_1);
  tcase_add_test(tc_core, transpose_correct_matrix_2);

  tcase_add_test(tc_core, transpose_uncorrect_matrix_1);
  tcase_add_test(tc_core, transpose_uncorrect_matrix_2);
  tcase_add_test(tc_core, transpose_uncorrect_matrix_3);

  suite_add_tcase(s, tc_core);
  return s;
}
