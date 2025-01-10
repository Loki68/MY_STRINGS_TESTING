#include "s21_string_helpers.h"

//#include "s21_strlen.c"

void preparse_string_to_lexemmes(TokenIndicesAndType_t *returned_tokens_metrics,
                                 int *returned_tokens_count,
                                 const char *format_sting) {

  TokenIndicesAndType_t *current_token_metrics = S21_NULL;
  int format_length = 0;
  int current_char = 0;
  int tokens_count = 0;
  int is_spec_format_substring = 0;

  format_length = (int)s21_strlen(format_sting);
  format_length++;

  // "hello     %d\n world%s from sprintf\n"

  printf("Source string is : \"%s\"\n\n", format_sting);

  for (int i = 0; i < format_length; i++) {
    current_char = format_sting[i];
    //дополнить разбор %%
    if ((current_char == '%' || i == format_length - 1) &&
        format_sting[i + 1] != '%') {
      current_token_metrics = &returned_tokens_metrics[tokens_count];
      current_token_metrics->token_end_index = i;
      current_token_metrics->token_type = text;
      tokens_count++;

      current_token_metrics = &returned_tokens_metrics[tokens_count];
      current_token_metrics->token_begin_index = i + 1;
      is_spec_format_substring = 1;
    }

    //выделить в субпарсер для строк формата
    if (is_spec_format_substring) {
      switch (current_char) {
      case 'd':
        current_token_metrics->token_type = integer;
        is_spec_format_substring = 0;
        current_token_metrics->token_end_index = i;
        tokens_count++;

        current_token_metrics = &returned_tokens_metrics[tokens_count];
        current_token_metrics->token_begin_index = i + 1;
        break;
      case 's':
        current_token_metrics->token_type = string;
        is_spec_format_substring = 0;
        current_token_metrics->token_end_index = i;
        tokens_count++;

        current_token_metrics = &returned_tokens_metrics[tokens_count];
        current_token_metrics->token_begin_index = i + 1;
        break;
      }
    }
  }

  *returned_tokens_count = tokens_count;
}

// minus='-', plus='+', space=' ', sharp='#', zero='0'
//строим текстовый токен
void build_text_token(const char *format_string,
                      TokenIndicesAndType_t *token_metrics,
                      TextToken_t *text_token) {
  int token_length = 0;

  token_length =
      token_metrics->token_end_index - token_metrics->token_begin_index;

  for (int i = token_metrics->token_begin_index;
       i < token_metrics->token_end_index; i++) {
    text_token->token_string[i - token_metrics->token_begin_index] =
        format_string[i];
  }

  text_token->token_string[token_length] = '\0';
  // token_length++;//с учетом '\0'
  text_token->token_size = (s21_size_t)token_length;
}

void build_specified_token(const char *format_string,
                           TokenIndicesAndType_t *token_metrics,
                           FormattedToken_t *specified_token) {
  int token_length = 0;
  int current_char = 0;
  Flags_t *flags = S21_NULL;

  flags = &specified_token->token_format.token_flags;

  token_length =
      token_metrics->token_end_index - token_metrics->token_begin_index;
  //где то тут должно быть разделение на формат.
  for (int i = token_metrics->token_begin_index;
       i < token_metrics->token_end_index; i++) {
    current_char = format_string[i];
    switch (current_char) {
    case minus:
      flags->minus = 1;
      flags->no_flags = 0;
      break;
    case plus:
      flags->plus = 1;
      flags->no_flags = 0;
      break;
    case space:
      flags->space = 1;
      flags->no_flags = 0;
      break;
    case sharp:
      flags->sharp = 1;
      flags->no_flags = 0;
      break;
    case zero:
      flags->zero = 1;
      flags->no_flags = 0;
      break;
    }

    specified_token->token_string[i - token_metrics->token_begin_index] =
        current_char;
  }

  specified_token->token_string[token_length] = '\0';
  // token_length++;
  specified_token->token_size = (s21_size_t)token_length;

  //в отдельную функцию
  //   if(flags->no_flags && token_length)
  //         s21_strncpy(digit_token->token_value,digit_token->token_string,token_length);
}

// void build_digit_token(const char *format_string,
//                        TokenIndicesAndType_t *token_metrics,
//                        FormattedToken_t *digit_token) {
//   int token_length = 0;
//   int current_char = 0;
//   Flags_t *flags = S21_NULL;

//   flags = &digit_token->token_format.token_flags;

//   token_length =
//       token_metrics->token_end_index - token_metrics->token_begin_index;
//   //где то тут должно быть разделение на формат.
//   for (int i = token_metrics->token_begin_index;
//        i < token_metrics->token_end_index; i++) {
//     current_char = format_string[i];
//     switch (current_char) {
//     case minus:
//       flags->minus = 1;
//       flags->no_flags = 0;
//       break;
//     case plus:
//       flags->plus = 1;
//       flags->no_flags = 0;
//       break;
//     case space:
//       flags->space = 1;
//       flags->no_flags = 0;
//       break;
//     case sharp:
//       flags->sharp = 1;
//       flags->no_flags = 0;
//       break;
//     case zero:
//       flags->zero = 1;
//       flags->no_flags = 0;
//       break;
//     }

//     digit_token->token_string[i - token_metrics->token_begin_index] =
//         current_char;
//   }

//   digit_token->token_string[token_length] = '\0';
//   // token_length++;
//   digit_token->token_size = (s21_size_t)token_length;

//   //в отдельную функцию
//   //   if(flags->no_flags && token_length)
//   //
//   s21_strncpy(digit_token->token_value,digit_token->token_string,token_length);
// }

// void build_string_token(const char *format_string,
//                         TokenIndicesAndType_t *token_metrics,
//                         FormattedToken_t *string_token) {
//   int token_length = 0;

//   token_length =
//       token_metrics->token_end_index - token_metrics->token_begin_index;

//   for (int i = token_metrics->token_begin_index;
//        i < token_metrics->token_end_index; i++)
//     string_token->token_string[i - token_metrics->token_begin_index] =
//         format_string[i];

//   string_token->token_string[token_length] = '\0';
//   // token_length++;
//   string_token->token_size = (s21_size_t)token_length;
// }

void print_lexemmes_throught_format_string(
    TokenIndicesAndType_t *tokens_metrics, int tokens_count,
    const char *format_string) {

  printf("Tokens count = %d items\n\n", tokens_count);

  for (int j = 0; j < tokens_count; j++) {
    switch (tokens_metrics[j].token_type) {
    case text:
      printf("\tToken type : text\n");
      break;
    case integer:
      printf("\tToken type : integer\n");
      break;
    case string:
      printf("\tToken type : string\n");
      break;
    }

    printf("\tToken begin index = %d\n\tToken end index = %d\n",
           tokens_metrics[j].token_begin_index,
           tokens_metrics[j].token_end_index);

    printf("\tToken string : \"");

    for (int k = tokens_metrics[j].token_begin_index;
         k <= tokens_metrics[j].token_end_index && format_string[k]; k++)
      putchar(format_string[k]);

    printf("\"\n\n");
  }
}

void print_generated_tokens(Token_t *tokens, int tokens_count) {
  Flags_t *flags = S21_NULL;
  printf("\nGenerated tokens:\n");
  for (int i = 0; i < tokens_count; i++) {
    switch (tokens[i].token_type) {
    case text:
      printf("\tToken type : text\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n\n",
             tokens[i].generic_token.text_token.token_size,
             tokens[i].generic_token.text_token.token_position,
             tokens[i].generic_token.text_token.token_string);
      break;
    case integer:
      flags = &tokens[i].generic_token.formatted_token.token_format.token_flags;
      printf("\tToken type : integer\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].generic_token.formatted_token.token_size,
             tokens[i].generic_token.formatted_token.token_position,
             tokens[i].generic_token.formatted_token.token_string);

      printf(
          "\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\tis "
          "plus = %d\n\t\tis space = %d\n\t\tis sharp = %d\n\t\tis zero = %d",
          flags->no_flags, flags->minus, flags->plus, flags->space,
          flags->sharp, flags->zero);
      printf("\n\n");
      break;
    case string:
      flags = &tokens[i].generic_token.formatted_token.token_format.token_flags;
      printf("\tToken type : string\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].generic_token.formatted_token.token_size,
             tokens[i].generic_token.formatted_token.token_position,
             tokens[i].generic_token.formatted_token.token_string);

      printf(
          "\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\tis "
          "plus = %d\n\t\tis space = %d\n\t\tis sharp = %d\n\t\tis zero = %d",
          flags->no_flags, flags->minus, flags->plus, flags->space,
          flags->sharp, flags->zero);
      printf("\n\n");
      break;
    }
  }
  printf("\n\n");
}