#include "test.h"

START_TEST(remove_matrix) {
  matrix_t result = {0, 0, 0};
  s21_create_matrix(3, 3, &result);
  s21_remove_matrix(&result);
  _ck_assert_ptr_null(result.matrix, ==);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);
}
END_TEST

Suite *test_remove_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_remove_matrix=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, remove_matrix);

  suite_add_tcase(s, tc_core);
  return s;
}
