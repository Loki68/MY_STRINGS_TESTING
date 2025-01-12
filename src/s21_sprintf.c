#include "s21_sprintf.h"

#include "s21_string_helpers.h"

// TODO
//дополнить разбор %%
//обработать конец строки
//выделить в субпарсер для строк формата
// В этом файле и построение токена и его удаление ибо сложная процедура
// build_specified_token
//выделить отдельную функцию инициализации флагов, ширины и точности

//позже удалить, ибо эта функция для проверки токенов

int s21_sprintf(char *str, const char *format, ...) {

  // TokenIndicesAndType_t *tokens_metrics = NULL;
  FormattedToken_t *tokens = NULL;

  // s21_size_t tokens_metrics_size = 0;
  //считаем точное число токенов, стобы выделить память под массив токенов
  int tokens_count = 0;

  // проверить сначала строку на пустоту
  // и действовать под этим условием
  if (format)
    tokens_count = get_percent_count(format);

  printf("source = %s\nresult = %d\n", format, tokens_count);

  tokens = FormattedToken_t_create_array(tokens_count);

  if (tokens) {
    parse_string(format, tokens_count, tokens);

    print_generated_tokens(tokens, tokens_count);

    FormattedToken_t_delete_array(tokens);
    tokens = NULL;
  }

  // if (tokens_metrics_size) {
  //   //в отдельную функцию
  //   tokens_metrics = TokenIndicesAndType_t_create_array(tokens_metrics_size);

  //   if (tokens_metrics) {

  //     preparse_string_to_lexemmes(tokens_metrics, &tokens_count, format,
  //                                 tokens_metrics_size);
  //     print_lexemmes_throught_format_string(tokens_metrics, tokens_count,
  //                                           format);

  //     generated_tokens = FormattedToken_t_create_array(tokens_count);

  //     if (generated_tokens) {
  //       parse_lexemmes_to_tokens(format, tokens_metrics, tokens_count,
  //                                generated_tokens);
  //       FormattedToken_t_delete_array(generated_tokens);
  //       generated_tokens = NULL;
  //     }

  //     // print_generated_tokens(generated_tokens, tokens_count);

  //     TokenIndicesAndType_t_delete_array(tokens_metrics);
  //     tokens_metrics = NULL;
  //   }
  // }

  return 0;
}