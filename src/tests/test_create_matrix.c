#include "test.h"

START_TEST(create_correct_matrix) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_create_matrix(3, 3, &result), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_int_eq(result.matrix[i][j], 0);
    }
  }
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(result.rows, 3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_uncorrect_matrix_1) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_create_matrix(0, 0, &result), 1);
}
END_TEST

START_TEST(create_uncorrect_matrix_2) {
  matrix_t result = {0, 0, 0};
  ck_assert_int_eq(s21_create_matrix(1, -2, &result), 1);
}
END_TEST

START_TEST(create_uncorrect_matrix_3) {
  matrix_t *result = NULL;
  ck_assert_int_eq(s21_create_matrix(2, 2, result), 1);
}
END_TEST

Suite *test_create_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_create_matrix=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, create_correct_matrix);
  tcase_add_test(tc_core, create_uncorrect_matrix_1);
  tcase_add_test(tc_core, create_uncorrect_matrix_2);
  tcase_add_test(tc_core, create_uncorrect_matrix_3);

  suite_add_tcase(s, tc_core);
  return s;
}
