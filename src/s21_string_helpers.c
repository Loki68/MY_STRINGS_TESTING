#include "s21_string_helpers.h"

typedef enum parsing_specs_state {
  parsing_flag,
  parsing_width,
  parsing_accuracy,
  parcing_length,
  parsing_spec,
  parsing_specs_end
} ParsingSpecsState_t;

int get_percent_count(const char *format_string) {
  int result = 1;

  for (int index = 0; format_string[index]; index++)
    if (format_string[index] == '%') {
      if (format_string[index + 1] == '%')
        index++;
      result += 2;
    }

  return result;
}

void parse_string(const char *format_string, int tokens_length,
                  FormattedToken_t *tokens) {

  FormattedToken_t *array_of_tokens = NULL;
  array_of_tokens = tokens;
  // // int format_length = 0;
  // int current_char = 0;
  int tokens_counter = 0;
  int current_index = 0;
  int continue_loop = 1;

  // int is_spec_format_substring = 0;
  array_of_tokens = tokens;
  ParsingState_t state = parsing_text;

  while (continue_loop) {
    switch (state) {
    case parsing_text:
      initialize_token(&array_of_tokens[tokens_counter], tokens_counter);
      state = parse_to_text(&array_of_tokens[tokens_counter], format_string,
                            &current_index);
      if (tokens_counter < tokens_length)
        tokens_counter = change_tokens_count(&array_of_tokens[tokens_counter],
                                             tokens_counter);
      break;
    case parsing_specs_text:

      initialize_token(&array_of_tokens[tokens_counter], tokens_counter);

      state = parse_specs_to_text(&array_of_tokens[tokens_counter],
                                  format_string, &current_index);

      if (tokens_counter < tokens_length)
        tokens_counter = change_tokens_count(&array_of_tokens[tokens_counter],
                                             tokens_counter);
      break;
    case parsing_end:
      continue_loop = 0;
      break;
    }
  }
}

void initialize_token(FormattedToken_t *new_token, int tokens_count) {
  new_token->token_size = 0;
  new_token->token_position = tokens_count + 1;
}

int change_tokens_count(FormattedToken_t *last_token, int tokens_count) {
  FormattedToken_t *token = NULL;
  int result = 0;

  token = last_token;

  result = tokens_count;

  if (token->token_size)
    result++;

  return result;
}

ParsingState_t parse_to_text(FormattedToken_t *token, const char *format_string,
                             int *returned_index) {
  ParsingState_t returning_state = parsing_text;
  int index = 0;
  int size = 0;

  index = *returned_index;

  for (; format_string[index] && format_string[index] != '%'; index++) {
    token->token_string[index - *returned_index] = format_string[index];
    size++;
  }

  if (size) {
    token->token_type = text;
    token->token_size = size;
    token->token_string[size] = '\0';
    *returned_index = index;
    // printf("%d\n", index);
  }

  switch (format_string[index]) {
  case '\0':
    returning_state = parsing_end;
    break;
  case '%':
    returning_state = parsing_specs_text;
    // printf("%c %d\n", format_string[index], index);
    break;
  }

  return returning_state;
}

ParsingState_t parse_specs_to_text(FormattedToken_t *token,
                                   const char *format_string,
                                   int *returned_index) {
  ParsingState_t returning_state = parsing_text;
  int index = 0;
  int size = 1;
  int continue_loop = 1;
  index = *returned_index;
  token->token_string[index - *returned_index] = format_string[index];
  index++;

  if (format_string[index] != '%') {
    for (; format_string[index] && continue_loop; index++)
      switch (format_string[index]) {
      case 'd':
        continue_loop = 0;
        break;
      case 's':
        continue_loop = 0;
        break;
      default:
        token->token_string[index - *returned_index] = format_string[index];
        size++;
        break;
      }

    index--;
  }
  token->token_string[index - *returned_index] = format_string[index];
  size++;
  returning_state = parsing_text;

  index++;

  if (size) {
    token->token_size = size;
    token->token_string[size] = '\0';
    *returned_index = index;
  }

  if (format_string[index] == '\0')
    returning_state = parsing_end;
  return returning_state;
}

// typedef struct formatted_token {
//   char token_string[256]; //позже изменить эту дичь на маллок
//   char token_value[256]; //позже изменить эту дичь на маллок
//   Flags_t token_flags;
//   TokenAccuracyOrWidth_t token_width;
//   TokenAccuracyOrWidth_t token_accuracy;
//   LengthFormat_t token_length;
//   TokenType_t token_type;
//   int token_size;
//   int token_position;
// } FormattedToken_t;

void parse_format_of_tokens(FormattedToken_t *tokens, int tokens_count) {
  for (int i = 0; i < tokens_count; i++)
    if (tokens[i].token_type != text)
      parse_single_format_of_token(&tokens[i]);
    else
      fill_text_token_value(&tokens[i]);
}

void parse_single_format_of_token(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  char *string_pointer = NULL;
  int current_index = 0;
  current_token = token;

  if (current_token->token_size == 2)
    try_parse_percents_to_text(current_token);

  if (current_token->token_type == no_type && current_token->token_size) {
    string_pointer = current_token->token_string + 1;

    current_index = parse_to_flags(&current_token->token_flags, string_pointer,
                                   current_index, current_token->token_size);

    printf("\ncurrent_index is %d\nstring is %s", current_index,
           string_pointer);
  }
}

void try_parse_percents_to_text(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  current_token = token;
  if (current_token->token_string[0] == '%' &&
      current_token->token_string[1] == '%') {
    current_token->token_type = text;
    current_token->token_value[0] = '%';
    current_token->token_value[1] = '\0';
  }
}

void fill_text_token_value(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  int current_size = 0;
  int index = 0;

  current_token = token;
  printf("\ntext\n");
  current_size = current_token->token_size;

  if (current_size) {
    for (; index < current_size; index++)
      current_token->token_value[index] = current_token->token_string[index];

    current_token->token_value[index] = '\0';
  }
}

int parse_to_flags(Flags_t *token_flags, char *token_string,
                   int current_start_index, int token_size) {
  int continue_parsing = 1;
  int index = 0;
  index = current_start_index;

  for (; index < token_size && continue_parsing; index++)
    if (token_flags)
      switch (token_string[index]) {
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
        break;
      }

  printf("\nhello\n");
  return index;
}

// typedef struct token_accuracy_or_width {
//   int no_width_or_accuracy_flag;
//   int number_flag;
//   int star_flag;
//   // AccuracyOrWidth_t accuracy_or_width_flags;
//   char accuracy_or_width_value[64];
// } TokenAccuracyOrWidth_t;

void parse_to_width(TokenAccuracyOrWidth_t token_width) {}
void parse_to_accuracy(TokenAccuracyOrWidth_t token_accuracy) {}
void parse_to_length(int current_character) {}
void parse_to_spec(int current_character) {}

// void parse_lexemmes_to_tokens(const char *format_string,
//                               TokenIndicesAndType_t *token_metrics,
//                               int token_metrics_length,
//                               FormattedToken_t *tokens) {

//   TokenIndicesAndType_t *parsed_token_metrics = NULL;
//   FormattedToken_t *new_tokens = NULL;

//   parsed_token_metrics = token_metrics;
//   new_tokens = tokens;
//   // end в отдельную функцию
//   for (int i = 0; i < token_metrics_length; i++) {
//     switch (parsed_token_metrics[i].token_type) {
//     case text:
//       new_tokens[i].token_type = text;
//       new_tokens[i].token_position = i + 1;
//       build_text_token(format_string, &parsed_token_metrics[i],
//       &new_tokens[i]); break;
//     case integer:
//       new_tokens[i].token_type = integer;
//       new_tokens[i].token_position = i + 1;
//       build_specified_token(format_string, &parsed_token_metrics[i],
//                             &new_tokens[i]);
//       break;
//     case string:
//       new_tokens[i].token_type = string;
//       new_tokens[i].token_position = i + 1;
//       build_specified_token(format_string, &parsed_token_metrics[i],
//                             &new_tokens[i]);
//       break;
//     }
//   }
// }

// // minus='-', plus='+', space=' ', sharp='#', zero='0'
// //строим текстовый токен
// void build_text_token(const char *format_string,
//                       TokenIndicesAndType_t *token_metrics,
//                       FormattedToken_t *text_token) {
//   int token_length = 0;

//   token_length =
//       token_metrics->token_end_index - token_metrics->token_begin_index;

//   for (int i = token_metrics->token_begin_index;
//        i < token_metrics->token_end_index; i++) {
//     text_token->token_string[i - token_metrics->token_begin_index] =
//         format_string[i];
//   }

//   text_token->token_string[token_length] = '\0';
//   // token_length++;//с учетом '\0'
//   text_token->token_size = token_length;
// }

// void build_specified_token(const char *format_string,
//                            TokenIndicesAndType_t *token_metrics,
//                            FormattedToken_t *specified_token) {
//   // // Flags_t *flags = S21_NULL;
//   // TokenAccuracyOrWidth_t *width = S21_NULL;
//   // TokenAccuracyOrWidth_t *accuracy = S21_NULL;
//   int token_length = 0;
//   int current_index = 0;

//   token_length =
//       token_metrics->token_end_index - token_metrics->token_begin_index;
//   //где то тут должно быть разделение на формат.
//   if (token_length)
//     for (int i = token_metrics->token_begin_index;
//          i < token_metrics->token_end_index; i++) {
//       specified_token->token_string[i - token_metrics->token_begin_index] =
//           format_string[i];
//     }

//   specified_token->token_string[token_length] = '\0';
//   // token_length++;
//   specified_token->token_size = token_length;

//   //выделить отдельную функцию инициализации флагов, ширины и точности
//   parse_token_character_to_flag(specified_token, &current_index);
//   parse_token_character_to_accuracy_or_width(specified_token, &current_index,
//                                              width_flag);

//   if (specified_token->token_string[current_index] == '.') {
//     current_index++;
//     parse_token_character_to_accuracy_or_width(specified_token,
//     &current_index,
//                                                accuracy_flag);
//   }

//   // //мб добавить флаги типа формат установлен или нет
//   // token->is_format_installed=1/0;
//   // и обнуление формата
//   //а дальше вот это:
//   //в отдельную функцию
//   //   if(flags->no_flags && token_length)
//   //
//   s21_strncpy(digit_token->token_value,digit_token->token_string,token_length);
// }

// void parse_token_character_to_flag(FormattedToken_t *token,
//                                    int *current_start_index) {
//   Flags_t *token_flags = NULL;
//   int continue_parsing = 1;
//   int token_length = 0;
//   // int current_character = 0;

//   token_flags = &token->token_format.token_flags;
//   token_flags->no_flags = 1;

//   token_length = token->token_size;

//   for (int index = *current_start_index;
//        index < token_length && continue_parsing; index++)
//     if (token_flags)
//       switch (token->token_string[index]) {
//       case minus:
//         token_flags->minus = 1;
//         token_flags->no_flags = 0;
//         break;
//       case plus:
//         token_flags->plus = 1;
//         token_flags->no_flags = 0;
//         break;
//       case space:
//         token_flags->space = 1;
//         token_flags->no_flags = 0;
//         break;
//       case sharp:
//         token_flags->sharp = 1;
//         token_flags->no_flags = 0;
//         break;
//       case zero:
//         token_flags->zero = 1;
//         token_flags->no_flags = 0;
//         break;
//       default:
//         continue_parsing = 0;
//         *current_start_index = index;
//         break;
//       }
// }

// void parse_token_character_to_accuracy_or_width(
//     FormattedToken_t *token, int *current_start_index,
//     AccuracyOrWidthFlag_t is_accuracy_or_width) {
//   TokenAccuracyOrWidth_t *token_accuracy_or_width = NULL;
//   int continue_parsing = 1;
//   int token_length = 0;
//   int current_character = 0;
//   int index = 0;

//   if (is_accuracy_or_width == accuracy_flag)
//     token_accuracy_or_width = &token->token_format.token_accuracy;
//   else
//     token_accuracy_or_width = &token->token_format.token_width;

//   token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy = 1;

//   token_length = token->token_size;
//   //звезда и число вместе дают не формат
//   for (index = *current_start_index; index < token_length &&
//   continue_parsing;
//        index++) {
//     current_character = token->token_string[index];

//     switch (current_character) {
//     case star:
//       token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy =
//       0; token_accuracy_or_width->accuracy_or_width_flags.star = 1; break;
//     default:
//       if (current_character < 48 || current_character > 57) {
//         continue_parsing = 0;
//       } else {
//         token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy
//         =
//             0;
//         token_accuracy_or_width->accuracy_or_width_flags.number = 1;
//         token_accuracy_or_width
//             ->accuracy_or_width_value[index - *current_start_index] =
//             current_character;
//       }
//       break;
//     }
//   }

//   token_accuracy_or_width
//       ->accuracy_or_width_value[index - *current_start_index] = '\0';
//   index--;

//   // if (token->token_string[index] != '.' && is_accuracy_or_width ==
//   // width_flag)
//   if (token->token_string[index] != '\0' && token->token_string[index] != '.'
//   &&
//       is_accuracy_or_width == width_flag)
//     init_accuracy_or_width(&token_accuracy_or_width->accuracy_or_width_flags);

//   if (token_accuracy_or_width->accuracy_or_width_flags.star &&
//       token_accuracy_or_width->accuracy_or_width_flags.number)
//     init_accuracy_or_width(&token_accuracy_or_width->accuracy_or_width_flags);

//   *current_start_index = index;
// }

// void init_accuracy_or_width(AccuracyOrWidth_t *token_accuracy_or_width) {
//   if (token_accuracy_or_width) {
//     token_accuracy_or_width->star = 0;
//     token_accuracy_or_width->number = 0;
//     token_accuracy_or_width->no_width_or_accuracy = 1;

//     //заменить на динамику
//     // token_accuracy_or_width->accuracy_or_width_value[0] = '\0';
//   }
// }

// int is_a_digit(int character) {
//   int result = 0;
//   return result;
// }
// int is_a_point(int character) {
//   int result = 0;
//   return result;
// }

// void print_lexemmes_throught_format_string(
//     TokenIndicesAndType_t *tokens_metrics, int tokens_count,
//     const char *format_string) {

//   printf("Tokens count = %d items\n\n", tokens_count);

//   for (int j = 0; j < tokens_count; j++) {
//     printf("-------------------------------------------------------------------"
//            "\n");
//     switch (tokens_metrics[j].token_type) {
//     case text:
//       printf("\tToken type : text\n");
//       break;
//     case integer:
//       printf("\tToken type : integer\n");
//       break;
//     case string:
//       printf("\tToken type : string\n");
//       break;
//     }

//     printf("\tToken begin index = %d\n\tToken end index = %d\n",
//            tokens_metrics[j].token_begin_index,
//            tokens_metrics[j].token_end_index);

//     printf("\tToken string : \"");

//     for (int k = tokens_metrics[j].token_begin_index;
//          k <= tokens_metrics[j].token_end_index && format_string[k]; k++)
//       putchar(format_string[k]);

//     printf("\"\n---------------------------------------------------------------"
//            "---\n\n");
//   }
// }

void print_generated_tokens(FormattedToken_t *tokens, int tokens_count) {
  printf("\nGenerated tokens:\n");
  for (int i = 0; i < tokens_count; i++) {
    printf("-------------------------------------------------------------------"
           "\n");
    switch (tokens[i].token_type) {
    case text:
      printf("\tToken type : text\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n\tToken value is : \"%s\"\n\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string, tokens[i].token_value);
      break;
    case integer:
      printf("\tToken type : integer\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);

      printf("\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\t"
             "plus = %d\n\t\tspace = %d\n\t\tsharp = %d\n\t\tzero ="
             "%d\n",
             tokens[i].token_flags.no_flags, tokens[i].token_flags.minus,
             tokens[i].token_flags.plus, tokens[i].token_flags.space,
             tokens[i].token_flags.sharp, tokens[i].token_flags.zero);
      printf("\tToken width:\n");

      printf("\t\tNo width = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_width.no_width_or_accuracy_flag,
             tokens[i].token_width.number_flag,
             tokens[i].token_width.star_flag);

      printf("\t\tValue is %s\n",
             tokens[i].token_width.accuracy_or_width_value);

      printf("\tToken accuracy:\n");

      printf("\t\tNo accuracy = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_accuracy.no_width_or_accuracy_flag,
             tokens[i].token_accuracy.number_flag,
             tokens[i].token_accuracy.star_flag);

      printf("\t\tValue is %s",
             tokens[i].token_accuracy.accuracy_or_width_value);

      printf("\n\n");
      break;
    case string:
      printf("\tToken type : string\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);

      printf("\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\t"
             "plus = %d\n\t\tspace = %d\n\t\tsharp = %d\n\t\tzero ="
             "%d\n",
             tokens[i].token_flags.no_flags, tokens[i].token_flags.minus,
             tokens[i].token_flags.plus, tokens[i].token_flags.space,
             tokens[i].token_flags.sharp, tokens[i].token_flags.zero);
      printf("\tToken width:\n");

      printf("\t\tNo width = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_width.no_width_or_accuracy_flag,
             tokens[i].token_width.number_flag,
             tokens[i].token_width.star_flag);

      printf("\t\tValue is %s\n",
             tokens[i].token_width.accuracy_or_width_value);

      printf("\tToken accuracy:\n");

      printf("\t\tNo accuracy = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_accuracy.no_width_or_accuracy_flag,
             tokens[i].token_accuracy.number_flag,
             tokens[i].token_accuracy.star_flag);

      printf("\t\tValue is %s",
             tokens[i].token_accuracy.accuracy_or_width_value);

      printf("\n\n");

      break;

    case no_type:
      printf("\tToken type : no typed\n\tToken size = %d\n\tToken position = "
             "%d\n\tToken string is : \"%s\"\n",
             tokens[i].token_size, tokens[i].token_position,
             tokens[i].token_string);

      printf("\tToken flags:\n\t\tis no_flags = %d\n\t\tis minus = %d\n\t\t"
             "plus = %d\n\t\tspace = %d\n\t\tsharp = %d\n\t\tzero ="
             "%d\n",
             tokens[i].token_flags.no_flags, tokens[i].token_flags.minus,
             tokens[i].token_flags.plus, tokens[i].token_flags.space,
             tokens[i].token_flags.sharp, tokens[i].token_flags.zero);
      printf("\tToken width:\n");

      printf("\t\tNo width = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_width.no_width_or_accuracy_flag,
             tokens[i].token_width.number_flag,
             tokens[i].token_width.star_flag);

      printf("\t\tValue is %s\n",
             tokens[i].token_width.accuracy_or_width_value);

      printf("\tToken accuracy:\n");

      printf("\t\tNo accuracy = %d\n\t\tNumber = %d\n\t\tStar = %d\n",
             tokens[i].token_accuracy.no_width_or_accuracy_flag,
             tokens[i].token_accuracy.number_flag,
             tokens[i].token_accuracy.star_flag);

      printf("\t\tValue is %s",
             tokens[i].token_accuracy.accuracy_or_width_value);

      printf("\n\n");
      break;
    }
    printf("\n---------------------------------------------------------------"
           "---\n\n");
  }
  printf("\n\n");
}