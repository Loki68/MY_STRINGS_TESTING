#include "tests.h"


// 16 sprintf in_implementation

int main(void) {
  int number_failed = 0;
  SRunner *srunner = NULL;

  srunner_add_suite(srunner, s21_dynamic_memory_helpers_suite());
  srunner_add_suite(srunner, s21_string_helpers_suite());
  srunner_add_suite(srunner, s21_sprintf_suite());

  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}