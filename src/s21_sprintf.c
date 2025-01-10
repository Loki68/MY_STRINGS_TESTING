#include "s21_sprintf.h"

#include "s21_string_helpers.h"

// TODO
//дополнить разбор %%
//выделить в субпарсер для строк формата

//позже удалить, ибо эта функция для проверки токенов

int s21_sprintf(char *str, const char *format, ...) {
  TokenIndicesAndType_t tokens_metrics[64] = {0};

  int tokens_count = 0;
  //чтобы компилятор не ругался
  printf("Buffer string is %p\n", str);

  preparse_string_to_lexemmes(tokens_metrics, &tokens_count, format);

  print_lexemmes_throught_format_string(tokens_metrics, tokens_count, format);

  Token_t tokens[64] = {0};
  // // Token_t current_token;

  // for (int i = 0; i < tokens_count; i++) {
  //   printf("%d) ", i + 1);
  //   // current_token = tokens[i];
  //   switch (tokens_metrics[i].token_type) {
  //   case text:
  //     tokens[i].token_type = text;
  //     tokens[i].generic_token.text_token.token_position = i + 1;
  //     build_text_token(format, &tokens_metrics[i],
  //                      &tokens[i].generic_token.text_token);

  //     printf("hello from text token\n");
  //     break;
  //   case integer:
  //     tokens[i].token_type = integer;
  //     tokens[i].generic_token.formatted_token.token_position = i + 1;
  //     build_digit_token(format, &tokens_metrics[i],
  //                       &tokens[i].generic_token.formatted_token);

  //     printf("hello from integer token\n");
  //     break;
  //   case string:
  //     tokens[i].token_type = string;
  //     tokens[i].generic_token.formatted_token.token_position = i + 1;
  //     build_string_token(format, &tokens_metrics[i],
  //                        &tokens[i].generic_token.formatted_token);

  //     printf("hello from string token\n");
  //     break;
  //   }
  // }

  // Token_t current_token;

  for (int i = 0; i < tokens_count; i++) {
    printf("%d) ", i + 1);
    // current_token = tokens[i];
    switch (tokens_metrics[i].token_type) {
    case text:
      tokens[i].token_type = text;
      tokens[i].generic_token.text_token.token_position = i + 1;
      build_text_token(format, &tokens_metrics[i],
                       &tokens[i].generic_token.text_token);

      printf("hello from text token\n");
      break;
    case integer:
      tokens[i].token_type = integer;
      tokens[i].generic_token.formatted_token.token_position = i + 1;
      build_specified_token(format, &tokens_metrics[i],
                            &tokens[i].generic_token.formatted_token);

      printf("hello from integer token\n");
      break;
    case string:
      tokens[i].token_type = string;
      tokens[i].generic_token.formatted_token.token_position = i + 1;
      build_specified_token(format, &tokens_metrics[i],
                            &tokens[i].generic_token.formatted_token);

      printf("hello from string token\n");
      break;
    }
  }

  print_generated_tokens(tokens, tokens_count);

  return 0;
}
