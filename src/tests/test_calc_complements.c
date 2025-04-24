#include "test.h"

START_TEST(calc_complements_correct_matrix_1) {
  matrix_t result, matrix1;
  s21_create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(result.matrix[i][j],
                          matrix1.matrix[1 - i][1 - j] * pow(-1, i + j));
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(calc_complements_correct_matrix_2) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 1;
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(calc_complements_correct_matrix_3) {
  matrix_t result = {0, 0, 0}, matrix1 = {0, 0, 0};
  s21_create_matrix(4, 4, &matrix1);
  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[3][2] = 1;
  matrix1.matrix[3][3] = 2;
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), 0);

  ck_assert_double_eq(result.matrix[0][0], 4);
  ck_assert_double_eq(result.matrix[0][1], -2);
  ck_assert_double_eq(result.matrix[0][2], 0);
  ck_assert_double_eq(result.matrix[0][3], 0);
  ck_assert_double_eq(result.matrix[1][0], -8);
  ck_assert_double_eq(result.matrix[1][1], 6);
  ck_assert_double_eq(result.matrix[1][2], 0);
  ck_assert_double_eq(result.matrix[1][3], 0);
  ck_assert_double_eq(result.matrix[2][0], 0);
  ck_assert_double_eq(result.matrix[2][1], 0);
  ck_assert_double_eq(result.matrix[2][2], 4);
  ck_assert_double_eq(result.matrix[2][3], -2);
  ck_assert_double_eq(result.matrix[3][0], 0);
  ck_assert_double_eq(result.matrix[3][1], 0);
  ck_assert_double_eq(result.matrix[3][2], 0);
  ck_assert_double_eq(result.matrix[3][3], 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}

START_TEST(calc_complements_uncorrect_matrix_1) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_calc_complements(NULL, &result), 1);
}

START_TEST(calc_complements_uncorrect_matrix_2) {
  matrix_t matrix1 = {0, 0, 0};
  s21_create_matrix(1, 1, &matrix1);
  ck_assert_int_eq(s21_calc_complements(&matrix1, NULL), 1);
  s21_remove_matrix(&matrix1);
}

START_TEST(calc_complements_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), 1);
}

START_TEST(calc_complements_uncorrect_matrix_4) {
  matrix_t matrix1 = {0, 0, 0}, result = {0, 0, 0};
  s21_create_matrix(3, 1, &matrix1);
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), 2);
  s21_remove_matrix(&matrix1);
}

Suite *test_calc_complements(void) {
  Suite *s = suite_create("\033[45m-=s21_calc_complements=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, calc_complements_correct_matrix_1);
  tcase_add_test(tc_core, calc_complements_correct_matrix_2);
  tcase_add_test(tc_core, calc_complements_correct_matrix_3);

  tcase_add_test(tc_core, calc_complements_uncorrect_matrix_1);
  tcase_add_test(tc_core, calc_complements_uncorrect_matrix_2);
  tcase_add_test(tc_core, calc_complements_uncorrect_matrix_3);
  tcase_add_test(tc_core, calc_complements_uncorrect_matrix_4);

  suite_add_tcase(s, tc_core);
  return s;
}
