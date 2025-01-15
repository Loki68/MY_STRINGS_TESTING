#include "s21_sprintf.h"

#include "s21_string_helpers.h"

//закончить сраный спринтф

int s21_sprintf(char *str, const char *format, ...) {
  // FormattedToken_t *tokens = S21_NULL;
  // char *buffer_for_printing = S21_NULL;

  FormattedToken_t *tokens = NULL;
  char *buffer_for_printing = NULL;

  // s21_size_t tokens_metrics_size = 0;
  //считаем точное число токенов, стобы выделить память под массив токенов
  int tokens_count = 0;
  int spec_tokens_count = 0;

  // проверить сначала строку на пустоту
  // и действовать под этим условием
  if (format)
    tokens_count = get_percent_count(format);

  printf("source = %s\nresult = %d\n", format, tokens_count);

  tokens = FormattedToken_t_create_array(tokens_count);

  if (tokens) {
    parse_string(format, tokens_count, tokens);

    parse_format_of_tokens(tokens, tokens_count);

    //а эту подчистить после написания
    print_generated_tokens(tokens, format, tokens_count);

    spec_tokens_count = get_count_of_spec_tokens(tokens, tokens_count);

    //завершение писанины
    print_format_string_in_buffer(buffer_for_printing, tokens,
                                  spec_tokens_count);

    FormattedToken_t_delete_array(tokens);
    tokens = NULL;
  }

  return 0;
}