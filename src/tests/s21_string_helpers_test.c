#include "tests.h"

// int parse_to_spec(SpecFormat_t *token_spec, TokenType_t *token_type,
//                   char format_character, int current_start_index)
  // SpecType_t type;
  // FormatStringData_t spec_format_data;
//  char *str = "cdfsugGeExXop #_12334549";
START_TEST(tests_parse_to_spec) {
    char *str = "cdfsugGeExXop #_12334549";
    SpecFormat_t token_spec={0};
    TokenType_t token_type={0};
    int found=1;
    int not_found=0;
    int result=0;
    int dev=0;
    size_t len=0;
    // len=strlen(str);
    // dev=(int)(strchr(str,' ')-str);

    // for(int i=0; i<(int)len;i++){
    //     parse_to_spec(&token_spec, &token_type,
    //               str[i], result);
    //     if(i<dev)
    //         ck_assert_int_eq(result,found);
    //     else
    //         ck_assert_int_eq(result,not_found);
    // }
}
END_TEST
//

//коды вне символов строки дают сегу
Suite *s21_string_helpers_suite(void) {
  Suite *suite=NULL;;
  TCase *tc_parse_to_spec=NULL;;

  suite = suite_create("s21_string_helpers");

  tc_parse_to_spec = tcase_create("parse_to_spec");

  //  char *str = "Hello world";
  //  int c = 'w';
  tcase_add_test(tc_parse_to_spec, tests_parse_to_spec);
  suite_add_tcase(suite, tc_parse_to_spec);

  return suite;
}