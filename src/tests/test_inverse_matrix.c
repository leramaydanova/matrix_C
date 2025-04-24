#include "test.h"

START_TEST(inverse_correct_matrix_1) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], -2);
  ck_assert_double_eq(result.matrix[1][0], -0.5);
  ck_assert_double_eq(result.matrix[1][1], 1.5);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(inverse_correct_matrix_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 0.5);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(inverse_correct_matrix_3) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], -2);
  ck_assert_double_eq(result.matrix[1][0], -0.5);
  ck_assert_double_eq(result.matrix[1][1], 1.5);
  ck_assert_double_eq(result.matrix[2][2], 1);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(inverse_correct_matrix_4) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(4, 4, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[3][2] = 1;
  matrix1.matrix[3][3] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], -2);
  ck_assert_double_eq(result.matrix[1][0], -0.5);
  ck_assert_double_eq(result.matrix[1][1], 1.5);
  ck_assert_double_eq(result.matrix[2][2], 1);
  ck_assert_double_eq(result.matrix[3][2], -0.5);
  ck_assert_double_eq(result.matrix[3][3], 0.5);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(inverse_correct_matrix_5) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(inverse_uncorrect_matrix_1) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), 1);
}

START_TEST(inverse_uncorrect_matrix_2) {
  matrix_t matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, NULL), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(inverse_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 1);
}

START_TEST(inverse_uncorrect_matrix_4) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  s21_create_matrix(2, 3, &matrix1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 2);
  s21_remove_matrix(&matrix1);
}

START_TEST(inverse_uncorrect_matrix_5) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  s21_create_matrix(2, 2, &matrix1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix1.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), 2);
  s21_remove_matrix(&matrix1);
}

Suite *test_inverse(void) {
  Suite *s = suite_create("\033[45m-=s21_inverse_matrix=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, inverse_correct_matrix_1);
  tcase_add_test(tc_core, inverse_correct_matrix_2);
  tcase_add_test(tc_core, inverse_correct_matrix_3);
  tcase_add_test(tc_core, inverse_correct_matrix_4);
  tcase_add_test(tc_core, inverse_correct_matrix_5);

  tcase_add_test(tc_core, inverse_uncorrect_matrix_1);
  tcase_add_test(tc_core, inverse_uncorrect_matrix_2);
  tcase_add_test(tc_core, inverse_uncorrect_matrix_3);
  tcase_add_test(tc_core, inverse_uncorrect_matrix_4);
  tcase_add_test(tc_core, inverse_uncorrect_matrix_5);

  suite_add_tcase(s, tc_core);
  return s;
}
