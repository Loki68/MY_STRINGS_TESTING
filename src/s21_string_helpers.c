#include "s21_string_helpers.h"

void preparse_string_to_lexemmes(TokenIndicesAndType_t *returned_tokens_metrics,
                                 int *returned_tokens_count,
                                 const char *format_sting) {
  int format_length = 0;
  int current_char = 0;
  int tokens_count = 0;
  int is_spec_format_substring = 0;

  format_length = (int)s21_strlen(format_sting);
  format_length++;

  for (int i = 0; i < format_length; i++) {
    current_char = format_sting[i];
    //дополнить разбор %%
    if ((current_char == '%' || i == format_length - 1) &&
        format_sting[i + 1] != '%') {
      returned_tokens_metrics[tokens_count].token_end_index = i;
      returned_tokens_metrics[tokens_count].token_type = text;
      tokens_count++;

      returned_tokens_metrics[tokens_count].token_begin_index = i + 1;
      is_spec_format_substring = 1;
    }

    //выделить в субпарсер для строк формата
    if (is_spec_format_substring)
      switch (current_char) {
      case 'd':
        is_spec_format_substring = 0;
        returned_tokens_metrics[tokens_count].token_type = integer;
        returned_tokens_metrics[tokens_count].token_end_index = i;
        tokens_count++;

        returned_tokens_metrics[tokens_count].token_begin_index = i + 1;
        break;
      case 's':
        is_spec_format_substring = 0;
        returned_tokens_metrics[tokens_count].token_type = string;
        returned_tokens_metrics[tokens_count].token_end_index = i;
        tokens_count++;

        returned_tokens_metrics[tokens_count].token_begin_index = i + 1;
        break;

        // case '%':
        // smth about text token
        //  break;
      }
  }
  *returned_tokens_count = tokens_count;
}

// minus='-', plus='+', space=' ', sharp='#', zero='0'
//строим текстовый токен
void build_text_token(const char *format_string,
                      TokenIndicesAndType_t *token_metrics,
                      FormattedToken_t *text_token) {
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
  // Flags_t *flags = S21_NULL;
  TokenAccuracyOrWidth_t *width = S21_NULL;
  TokenAccuracyOrWidth_t *accuracy = S21_NULL;
  int token_length = 0;
  // int is_flag_parsing = 0;
  // int is_width_parsing = 0;
  int is_accuracy_parsing_started = 0;
  FormatParsingStates_t parsing_state = parse_flags;
  // int is_length_parsing = 0;

  int current_char = 0;
  int parsing_result = 0;

  // flags = &specified_token->token_format.token_flags;
  // flags->no_flags = 1;
  width = &specified_token->token_format.token_width;
  width->type = no_width_or_accuracy;
  width->accuracy_or_width_value = -1;

  token_length =
      token_metrics->token_end_index - token_metrics->token_begin_index;
  //где то тут должно быть разделение на формат.
  if (flags && token_length)
    for (int i = token_metrics->token_begin_index;
         i < token_metrics->token_end_index; i++) {
      specified_token->token_string[i - token_metrics->token_begin_index] =
          format_string[i];
      // current_char = format_string[i];
      // if (i == token_metrics->token_begin_index)
      //   switch (parsing_state) {
      //   case parse_flags:
      //     if (parse_token_character_to_flag(flags, current_char))
      //       parsing_state = parse_width;
      //     else
      //       break;
      //   case parse_width:
      //     if (parse_token_character_to_width(width, current_char))
      //       parsing_state = parse_accuracy;
      //     else
      //       break;
      //   case parse_accuracy:
      //     break;
      //   case parse_length:
      //     break;
      //   }

      // // if (i == token_metrics->token_begin_index)
      // //   is_flag_parsing = 1;

      // // if (is_flag_parsing && !parsing_result)
      // //   parsing_result = parse_token_character_to_flag(flags,
      // current_char);
      // // else if (is_flag_parsing && parsing_result) {
      // //   is_flag_parsing = 0;
      // //   is_width_parsing = 1;
      // //   parsing_result = 0;
      // // }

      // // if (is_width_parsing && !parsing_result)
      // //   parsing_result = parse_token_character_to_accuracy(width,
      // //   current_char);
      // // else if (is_width_parsing && parsing_result) {
      // //   is_width_parsing = 0;
      // //   is_accuracy_parsing=1;
      // //   parsing_result = 0;
      // // }

      // // // if (is_accuracy_parsing && !parsing_result)
      // // //   parsing_result = parse_token_character_to_width(width,
      // // current_char);
      // // // else if (is_accuracy_parsing && parsing_result) {
      // // //   is_accuracy_parsing = 0;
      // // //   is_length_parsing=1;
      // // //   parsing_result = 0;
      // // // }

      specified_token->token_string[i - token_metrics->token_begin_index] =
          current_char;
    }

  specified_token->token_string[token_length] = '\0';
  // token_length++;
  specified_token->token_size = (s21_size_t)token_length;

  // //мб добавить флаги типа формат установлен или нет
  // token->is_format_installed=1/0;
  // и обнуление формата
  //а дальше вот это:
  //в отдельную функцию
  //   if(flags->no_flags && token_length)
  //         s21_strncpy(digit_token->token_value,digit_token->token_string,token_length);
}

void parse_token_character_to_flag(FormattedToken_t *token,
                                   int *current_start_index, int token_length) {
  Flags_t *flags = S21_NULL;
  int continue_parsing = 1;
  int current_character = 0;

  flags = &specified_token->token_format.token_flags;
  flags->no_flags = 1;

  for (int index = *current_start_index;
       index < token_length && continue_parsing; index++)
    if (token_flags)
      switch (token->token_string[index]) {
      case minus:
        token_flags->minus = 1;
        token_flags->no_flags = 0;
        break;
      case plus:
        token_flags->plus = 1;
        token_flags->no_flags = 0;
        break;
      case space:
        token_flags->space = 1;
        token_flags->no_flags = 0;
        break;
      case sharp:
        token_flags->sharp = 1;
        token_flags->no_flags = 0;
        break;
      case zero:
        token_flags->zero = 1;
        token_flags->no_flags = 0;
        break;
      default:
        continue_parsing = 0;
        *current_start_index = index;
        break;
      }
}

int parse_token_character_to_width(TokenAccuracyOrWidth_t *token_width,
                                   int current_character) {
  int result = 0;
  //вот тут будут проблемы и надо покурить механику,что главнее и как работает
  //звезда и число вместе
  if (token_width)
    if (current_character == star) //{
      token_width->type = star;

    else if (current_character > 47 && current_character < 58) {
      token_width->type = number;
      token_width->accuracy_or_width_value = 0;
    } else
      result = -1;

  return result;
}

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

void print_generated_tokens(FormattedToken_t *tokens, int tokens_count) {
  printf("\nGenerated tokens:\n");
  for (int i = 0; i < tokens_count; i++) {
    switch (tokens[i].token_type) {
    case text:
      printf("\tToken type : text\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);
      break;
    case integer:
      printf("\tToken type : integer\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);

      printf("\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\tis "
             "plus = %d\n\t\tis space = %d\n\t\tis sharp = %d\n\t\tis zero = "
             "%d\n",
             tokens[i].token_format.token_flags.no_flags,
             tokens[i].token_format.token_flags.minus,
             tokens[i].token_format.token_flags.plus,
             tokens[i].token_format.token_flags.space,
             tokens[i].token_format.token_flags.sharp,
             tokens[i].token_format.token_flags.zero);
      printf("\tToken width:\n");
      switch (tokens[i].token_format.token_width.type) {
      case no_width_or_accuracy:
        printf("\t\tType is No width\n");
        break;
      case number:
        printf("\t\tType is Number\n");
        break;
      case star:
        printf("\t\tType is *\n");
        break;
      }
      printf("\t\tValue is %d",
             tokens[i].token_format.token_width.accuracy_or_width_value);
      printf("\n\n");
      break;
    case string:
      printf("\tToken type : string\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);

      printf("\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\tis "
             "plus = %d\n\t\tis space = %d\n\t\tis sharp = %d\n\t\tis zero = "
             "%d\n",
             tokens[i].token_format.token_flags.no_flags,
             tokens[i].token_format.token_flags.minus,
             tokens[i].token_format.token_flags.plus,
             tokens[i].token_format.token_flags.space,
             tokens[i].token_format.token_flags.sharp,
             tokens[i].token_format.token_flags.zero);
      printf("\tToken width:\n");
      switch (tokens[i].token_format.token_width.type) {
      case no_width_or_accuracy:
        printf("\t\tType is No width\n");
        break;
      case number:
        printf("\t\tType is Number\n");
        break;
      case star:
        printf("\t\tType is *\n");
        break;
      }
      printf("\t\tValue is %d",
             tokens[i].token_format.token_width.accuracy_or_width_value);
      printf("\n\n");
      break;
    }
  }
  printf("\n\n");
}