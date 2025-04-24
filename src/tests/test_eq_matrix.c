#include "test.h"

START_TEST(eq_correct_matrix_1) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[1][2] = 3;
  matrix1.matrix[0][1] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 4;
  matrix1.matrix[1][0] = 1;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[1][2] = 3;
  matrix2.matrix[0][1] = 1;
  matrix2.matrix[1][1] = 2;
  matrix2.matrix[2][2] = 4;
  matrix2.matrix[1][0] = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_2) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[1][2] = 3;
  matrix1.matrix[0][1] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[2][2] = 4;
  matrix1.matrix[1][0] = 1;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[1][2] = 3;
  matrix2.matrix[0][1] = 1;
  matrix2.matrix[1][1] = 2;
  matrix2.matrix[2][2] = 4;
  matrix2.matrix[1][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_3) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = i + 0.0000001;
      matrix2.matrix[i][j] = i + 0.0000002;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_4) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = i + 0.000001;
      matrix2.matrix[i][j] = i + 0.000001;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_5) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = i + 0.00000001;
      matrix2.matrix[i][j] = i + 0.00000005;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_6) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = i + 0.0000001;
      matrix2.matrix[i][j] = i + 0.00000005;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_7) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = i + 0.0000001;
      matrix2.matrix[i][j] = i + 0.00000009;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_correct_matrix_8) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = 9.99999;
      matrix2.matrix[i][j] = 9.99999;
    }
  }
  matrix1.matrix[2][0] = 10;
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_uncorrect_matrix_1) {
  matrix_t matrix1 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix1);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, NULL), FAILURE);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(eq_uncorrect_matrix_2) {
  matrix_t matrix2 = {0, 0, 0};

  s21_create_matrix(3, 3, &matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix2.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(NULL, &matrix2), FAILURE);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_uncorrect_matrix_3) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};
  s21_create_matrix(3, 3, &matrix2);
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_uncorrect_matrix_4) {
  matrix_t matrix1 = {0, 0, 0};
  matrix_t matrix2 = {0, 0, 0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

Suite *test_eq_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_eq_matrix=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, eq_correct_matrix_1);
  tcase_add_test(tc_core, eq_correct_matrix_2);
  tcase_add_test(tc_core, eq_correct_matrix_3);
  tcase_add_test(tc_core, eq_correct_matrix_4);
  tcase_add_test(tc_core, eq_correct_matrix_5);
  tcase_add_test(tc_core, eq_correct_matrix_6);
  tcase_add_test(tc_core, eq_correct_matrix_7);
  tcase_add_test(tc_core, eq_correct_matrix_8);

  tcase_add_test(tc_core, eq_uncorrect_matrix_1);
  tcase_add_test(tc_core, eq_uncorrect_matrix_2);
  tcase_add_test(tc_core, eq_uncorrect_matrix_3);
  tcase_add_test(tc_core, eq_uncorrect_matrix_4);

  suite_add_tcase(s, tc_core);
  return s;
}
