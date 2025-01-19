#include "tests.h"

//  char *str = "there is no power as no knowledge";
//  int c = '[';
START_TEST(test_FormattedToken_t_create_array_1) {}
END_TEST
//

//коды вне символов строки дают сегу
Suite *s21_dynamic_memory_helpers_suite(void) {
  Suite *suite;
  TCase *tc_FormattedToken_t_create_array;

  suite = suite_create("FormattedToken_t_create_array");

  tc_FormattedToken_t_create_array = tcase_create("FormattedToken_t_create_array");

  //  char *str = "Hello world";
  //  int c = 'w';
  tcase_add_test(tc_FormattedToken_t_create_array, test_FormattedToken_t_create_array_1);
  suite_add_tcase(suite, tc_FormattedToken_t_create_array);

  return suite;
}