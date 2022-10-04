// Copyright [2022] <Smithjan>
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./s21_smartcalc.h"

START_TEST(s21_smartcalc1) {
  char *string = "10*10/10+10-10 + (-10)";
  string = remove_space(string);
  double value1 = 0;
  double value2 = calculate(string);
  ck_assert_double_eq(value1, value2);
}
END_TEST

START_TEST(s21_smartcalc2) {
  char string[20] = "10^2mod30=";
  double value1 = fmod(pow(10.0, 2), 30.0);
  double value2 = calculate(string);
  ck_assert_double_eq(value1, value2);
}
END_TEST

START_TEST(s21_smartcalc3) {
  char string[30] = "cos(1)+sin(1)+tan(1/2)=";
  double value1 = 1.9280758;
  double value2 = calculate(string);
  int check = value1 - value2;
  ck_assert_int_eq(0, check);
}
END_TEST

START_TEST(s21_smartcalc4) {
  char string[30] = "asin(1/2)+acos(0)+atan(1)=";
  double value1 = 2.8797933;
  double value2 = calculate(string);
  int check = value1 - value2;
  ck_assert_int_eq(0, check);
}
END_TEST

START_TEST(s21_smartcalc5) {
  char string[30] = "sqrt(4)+log(10)+ln(10)=";
  double value1 = 5.3025851;
  double value2 = calculate(string);
  int check = value1 - value2;
  ck_assert_int_eq(0, check);
}
END_TEST

START_TEST(s21_smartcalc6) {
  char string[50] = "16-(7+38*(6/2))*((3*6)-(9*(4+9-99)))/(96*9)";
  double value1 = -94.9166667;
  double value2 = calculate(string);
  int check = value1 - value2;
  ck_assert_int_eq(0, check);
}
END_TEST
START_TEST(s21_smartcalc7) {
  char string[100] = "sqrt(4)+9.235+23*sin(cos(10))-564-sqrt(25)+28.6*35";
  if (validator(string)) {
    double value1 = 426.122;
    double value2 = calculate(string);
    int check = value1 - value2;
    ck_assert_int_eq(0, check);
  }
}
END_TEST
START_TEST(s21_smartcalc8) {
  char string[100] = "sqrt(4)+9.235+23^sin(cos(10^2))-564-sqrt(25)+28.6*35+2^8";
  if (validator(string)) {
    double value1 = 710.050;
    double value2 = calculate(string);
    int check = value1 - value2;
    ck_assert_int_eq(0, check);
  }
}
END_TEST

START_TEST(s21_smartcalc9) {
  char *string = "2+3+(3+5)*2+3/(1-4)^3*(3^((2+1)+1))/(((1)))+log(2)";
  string = remove_space(string);
  if (validator(string)) {
    double value1 = 12.6931;
    double value2 = calculate(string);
    int check = value1 - value2;
    ck_assert_int_eq(0, check);
  }
}
END_TEST
START_TEST(s21_smartcalc10) {
  char *string =
      "5+(1+2)*4*cos(2*7.5-2)+sin(cos(2*5))-sqrt(2^5)+asin(0.5)+tan(50)";
  string = remove_space(string);
  if (validator(string)) {
    double value1 = 9.74018;
    double value2 = calculate(string);
    int check = value1 - value2;
    ck_assert_int_eq(0, check);
  }
}
END_TEST

START_TEST(s21_smartcalc11) {
  char *string =
      "5+(1+2)*4*cos(2*7.5-2)+sin(cos(2*5))-sqrt(2mod5)+asin(0.5)+tan(50)";
  string = remove_space(string);
  if (validator(string)) {
    double value1 = 13.9828;
    double value2 = calculate(string);
    int check = value1 - value2;
    ck_assert_int_eq(0, check);
  }
}
END_TEST
START_TEST(s21_smartcalc12) {
  char *string = "3 + * 4";
  string = remove_space(string);
  double value = validator(string);
  ck_assert_int_eq(value, 0);
}
END_TEST
START_TEST(s21_smartcalc13) {
  char *string = "2 + (8 * 9 + 1";
  string = remove_space(string);
  double value = validator(string);
  ck_assert_int_eq(value, 0);
}
END_TEST
START_TEST(s21_smartcalc14) {
  char *string = ") 4 kfsa 23r";
  string = remove_space(string);
  double value = validator(string);
  ck_assert_int_eq(value, 0);
}
END_TEST
START_TEST(s21_smartcalc15) {
  char *string = "5.3 * 42.43.54";
  string = remove_space(string);
  double value = validator(string);
  ck_assert_int_eq(value, 0);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_smartcalc1);
  tcase_add_test(tc1_1, s21_smartcalc2);
  tcase_add_test(tc1_1, s21_smartcalc3);
  tcase_add_test(tc1_1, s21_smartcalc4);
  tcase_add_test(tc1_1, s21_smartcalc5);
  tcase_add_test(tc1_1, s21_smartcalc6);
  tcase_add_test(tc1_1, s21_smartcalc7);
  tcase_add_test(tc1_1, s21_smartcalc8);
  tcase_add_test(tc1_1, s21_smartcalc9);
  tcase_add_test(tc1_1, s21_smartcalc10);
  tcase_add_test(tc1_1, s21_smartcalc11);
  tcase_add_test(tc1_1, s21_smartcalc12);
  tcase_add_test(tc1_1, s21_smartcalc13);
  tcase_add_test(tc1_1, s21_smartcalc14);
  tcase_add_test(tc1_1, s21_smartcalc15);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
