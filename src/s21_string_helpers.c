#include "s21_string_helpers.h"

// // typedef struct format_string_data{
// //   int data_start_index;
// //   int data_length;
// // }FormatStringData_t;

// // typedef struct flags {
// //   int no_flags;
// //   int minus;
// //   int plus;
// //   int space;
// //   int sharp;
// //   int zero;
// //   //int not_flags; //днем
// // } Flags_t;

// // typedef struct formatted_token {
// //   FormatStringData_t token_format_string_data;
// //   FormatStringData_t token_value_string_data;
// //   Flags_t token_flags;
// //   TokenAccuracyOrWidth_t token_width_data;
// //   TokenAccuracyOrWidth_t token_accuracy_data;
// //   LengthFormat_t token_length;
// //   char *format_string;
// //   TokenType_t token_type;
// // } FormattedToken_t;

// // typedef struct token_accuracy_or_width {
// //   AccuracyOrWidthType_t value_type;
// //   FormatStringData_t number_data;
// // } TokenAccuracyOrWidth_t;

// // typedef enum accuracy_or_width_type {
// //   no_width_or_accuracy,
// //   number,
// //   star = '*',
// //   not_width_or_accuracy
// // } AccuracyOrWidthType_t;

// typedef enum parsing_specs_state {
//   parsing_flag,
//   parsing_width,
//   parsing_accuracy,
//   parcing_length,
//   parsing_spec,
//   parsing_specs_end
// } ParsingSpecsState_t;

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
  int tokens_counter = 0;
  int current_index = 0;
  int continue_loop = 1;

  array_of_tokens = tokens;
  ParsingState_t state = parsing_text;

  while (continue_loop) {
    switch (state) {
    case parsing_text:
      initialize_token(&array_of_tokens[tokens_counter], format_string);

      state = parse_to_text(&array_of_tokens[tokens_counter], &current_index);

      if (tokens_counter < tokens_length)
        tokens_counter = update_tokens_count(&array_of_tokens[tokens_counter],
                                             tokens_counter);

      break;
    case parsing_specs_text:

      initialize_token(&array_of_tokens[tokens_counter], format_string);

      state =
          parse_specs_to_text(&array_of_tokens[tokens_counter], &current_index);

      if (tokens_counter < tokens_length)
        tokens_counter = update_tokens_count(&array_of_tokens[tokens_counter],
                                             tokens_counter);

      break;
    case parsing_end:
      continue_loop = 0;
      break;
    }
  }
}

void initialize_token(FormattedToken_t *new_token, const char *format) {

  initialize_string_data(&new_token->token_format_string_data);
  initialize_string_data(&new_token->token_value_string_data);

  initialize_flags(&new_token->token_flags);

  initialize_accuracy_or_width(&new_token->token_width);
  initialize_accuracy_or_width(&new_token->token_accuracy);

  initialize_length(&new_token->token_length);

  new_token->format_string = (char *)format;
  new_token->token_type = no_type;
}

void initialize_string_data(FormatStringData_t *string_data) {
  FormatStringData_t *current_string_data = NULL;

  current_string_data = string_data;

  current_string_data->data_start_index = -1;
  current_string_data->data_length = -1;
}

void initialize_flags(Flags_t *token_flags) {
  Flags_t *current_token_flags = NULL;

  current_token_flags = token_flags;

  current_token_flags->no_flags = 1;
  current_token_flags->minus = 0;
  current_token_flags->plus = 0;
  current_token_flags->space = 0;
  current_token_flags->sharp = 0;
  current_token_flags->zero = 0;
  current_token_flags->flags_length=0;
}

void initialize_accuracy_or_width(
    TokenAccuracyOrWidth_t *token_accuracy_or_width) {
  TokenAccuracyOrWidth_t *current_accuracy_or_width = NULL;

  current_accuracy_or_width = token_accuracy_or_width;

  current_accuracy_or_width->value_type = no_width_or_accuracy;

  initialize_string_data(&current_accuracy_or_width->accuracy_or_width_data);
}

void initialize_length(LengthFormat_t *token_length) {
  LengthFormat_t *current_token_length = NULL;

  current_token_length = token_length;

  current_token_length->no_length = 1;
  current_token_length->short_int_or_unsigned_short = 0;
  current_token_length->long_int = 0;
  current_token_length->long_float = 0;
}

int update_tokens_count(FormattedToken_t *last_token, int tokens_count) {
  FormattedToken_t *token = NULL;
  int result = 0;

  token = last_token;

  result = tokens_count;

  if (token->token_format_string_data.data_length)
    result++;

  return result;
}

ParsingState_t parse_to_text(FormattedToken_t *token, int *returned_index) {
  FormattedToken_t *current_token = NULL;
  FormatStringData_t *token_format_data = NULL;
  char *format_string = NULL;
  ParsingState_t returning_state = parsing_text;
  int index = 0;
  int size = 0;

  current_token = token;
  token_format_data = &token->token_format_string_data;
  format_string = token->format_string;
  index = *returned_index;

  token_format_data->data_start_index = *returned_index;

  for (; format_string[index] && format_string[index] != '%'; index++)
    size++;

  if (size > 0) {
    current_token->token_type = text;
    token_format_data->data_length = size;

    *returned_index = index;
  }

  switch (format_string[index]) {
  case '\0':
    returning_state = parsing_end;
    break;
  case '%':
    returning_state = parsing_specs_text;
    break;
  }

  return returning_state;
}

ParsingState_t parse_specs_to_text(FormattedToken_t *token,
                                   int *returned_index) {
  FormattedToken_t *current_token = NULL;
  FormatStringData_t *token_format_data = NULL;
  char *format_string = NULL;
  ParsingState_t returning_state = parsing_text;
  int index = 0;
  int size = 1;
  int continue_loop = 1;
  index = *returned_index;

  current_token = token;
  token_format_data = &token->token_format_string_data;
  format_string = token->format_string;
  token_format_data->data_start_index = *returned_index;
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
        size++;
        break;
      }

    index--;
  }

  size++;

  returning_state = parsing_text;

  index++;

  if (size > 0) {
    token_format_data->data_length = size;

    *returned_index = index;
  }

  if (format_string[index] == '\0')
    returning_state = parsing_end;

  return returning_state;
}

void parse_format_of_tokens(FormattedToken_t *tokens, int tokens_count) {
  for (int i = 0; i < tokens_count; i++) {
    if (tokens[i].token_type != text)
      parse_single_format_of_token(&tokens[i]);

    if (tokens[i].token_type == text &&
        tokens[i].token_value_string_data.data_length == -1)
      fill_text_token_value(&tokens[i]);
  }
}

void parse_single_format_of_token(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  char *string_pointer = NULL;
  int current_index = 0;
  current_token = token;

  if (current_token->token_format_string_data.data_length == 2)
    try_parse_percents_to_text(current_token);

  if (current_token->token_type == no_type &&
      current_token->token_format_string_data.data_length) {
    //string_pointer = current_token->format_string + 1;
    string_pointer = current_token->format_string;

    current_index = parse_to_flags(
        &current_token->token_flags, &current_token->token_format_string_data,string_pointer);
    //string_pointer = current_token->format_string-1;

    current_index = parse_to_width(
        &current_token->token_width,string_pointer,current_index,current_token->token_format_string_data.data_length);
//
//
//
//
  }
}

void try_parse_percents_to_text(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  FormatStringData_t *format_data = NULL;
  FormatStringData_t *value_data = NULL;
  char *format_string = NULL;
  int begin_index = 0;
  int end_index = 0;

  current_token = token;
  format_string = token->format_string;
  format_data = &token->token_format_string_data;
  value_data = &token->token_value_string_data;

  begin_index = format_data->data_start_index;
  end_index = begin_index + format_data->data_length - 1;

  if (format_string[begin_index] == '%' && format_string[end_index] == '%') {
    current_token->token_type = text;
    value_data->data_start_index = begin_index;
    value_data->data_length = 1;
  }
}

void fill_text_token_value(FormattedToken_t *token) {
  FormattedToken_t *current_token = NULL;
  FormatStringData_t *format_data = NULL;
  FormatStringData_t *value_data = NULL;
  char *format_string = NULL;
  int begin_index = 0;
  int current_size = 0;

  current_token = token;
  format_string = token->format_string;
  format_data = &token->token_format_string_data;
  begin_index = format_data->data_start_index;
  current_size = format_data->data_length;

  if (current_size > 0) {
    value_data = &token->token_value_string_data;

    value_data->data_start_index = begin_index;
    value_data->data_length = current_size;
  }
}


int parse_to_flags(Flags_t *token_flags,FormatStringData_t *format_data, char *format_string) {
  Flags_t *current_flags=NULL;
  char *format=NULL;

  int continue_parsing = 1;
  int index = 0;
  int format_length=0;
  int flags_length=0;

  current_flags=token_flags;
  format=format_string;

  index = format_data->data_start_index+1;
  format_length=index+format_data->data_length;

  for (; index < format_length && continue_parsing; index++)
      switch (format[index]) {
      case minus:
        current_flags->minus = 1;
        current_flags->no_flags = 0;
        flags_length++;
        break;
      case plus:
        current_flags->plus = 1;
        current_flags->no_flags = 0;
        flags_length++;
        break;
      case space:
        current_flags->space = 1;
        current_flags->no_flags = 0;
        flags_length++;
        break;
      case sharp:
        current_flags->sharp = 1;
        current_flags->no_flags = 0;
        flags_length++;
        break;
      case zero:
        current_flags->zero = 1;
        current_flags->no_flags = 0;
        flags_length++;
        break;
      default:
        continue_parsing = 0;
        break;
      }

//if(flags_length)
current_flags->flags_length=flags_length;

if(flags_length>=0)
  index--;

  return index;
}


// typedef struct token_accuracy_or_width {
//   AccuracyOrWidthType_t value_type;
//   FormatStringData_t number_data;
// } TokenAccuracyOrWidth_t;

// typedef struct format_string_data{
//   int data_start_index;
//   int data_length;
// }FormatStringData_t;

//звездочка и число взаимно исключают друг друга,так что перечисление
//а вместе-это текст.
//тут не format_data_string, а current_index
int parse_to_width(TokenAccuracyOrWidth_t *token_width, char *format_string, int current_start_index,int current_length) {

  TokenAccuracyOrWidth_t *width_format = NULL;
  char *format = NULL;
  int continue_parsing = 1;
  int index = 0;
  int format_length = 0;
  // int current_character = 0;
  
  int is_star = 0;
  int is_digit = 0;

  width_format = token_width;
  format = format_string;
  index = current_start_index;
  format_length=index+current_length;

  for (; index < format_length && continue_parsing;
       index++){
    switch (format[index]) {
      case '*':
        is_star = 1;
        break;
      default:
        if (format[index] > 47 && format[index] < 58)
          is_digit = 1;
        else
          continue_parsing = 0;
        break;
        
    }}


  if (is_star && is_digit)
    width_format->value_type = no_width_or_accuracy;
  else if(is_star || is_digit) {

    if(is_star)
      width_format->value_type = star;
    else 
      width_format->value_type = number;
      
      width_format->accuracy_or_width_data.data_start_index=current_start_index;
      width_format->accuracy_or_width_data.data_length = index-current_start_index-1;
  }
  // index--;

  // //   TokenAccuracyOrWidth_t *token_accuracy_or_width = NULL;
  // //   int continue_parsing = 1;
  // //   int token_length = 0;
  // //   int current_character = 0;
  // //   int index = 0;

  // //   if (is_accuracy_or_width == accuracy_flag)
  // //     token_accuracy_or_width = &token->token_format.token_accuracy;
  // //   else
  // //     token_accuracy_or_width = &token->token_format.token_width;

  // //   token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy
  // =
  // //   1;

  // //   token_length = token->token_size;
  // //   //звезда и число вместе дают не формат
  // // for (index = *current_start_index; index < token_length &&
  // // continue_parsing;
  // //      index++) {
  // //   current_character = token->token_string[index];

  // //   switch (current_character) {
  // //   case star:
  // // token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy
  // //     = 0; token_accuracy_or_width->accuracy_or_width_flags.star = 1;
  // //     break;
  // //   default:
  // //     if (current_character < 48 || current_character > 57) {
  // //       continue_parsing = 0;
  // //     } else {
  // // token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy
  // //       =
  // //           0;
  // //       token_accuracy_or_width->accuracy_or_width_flags.number = 1;
  // //       token_accuracy_or_width
  // //           ->accuracy_or_width_value[index - *current_start_index] =
  // //           current_character;
  // //     }
  // //     break;
  // //   }
  // // }

  // // token_accuracy_or_width
  // //     ->accuracy_or_width_value[index - *current_start_index] = '\0';
  // // index--;

  // //   // if (token->token_string[index] != '.' && is_accuracy_or_width ==
  // //   // width_flag)
  // //   if (token->token_string[index] != '\0' && token->token_string[index]
  // !=
  // //   '.'
  // //   &&
  // //       is_accuracy_or_width == width_flag)
  // //
  // init_accuracy_or_width(&token_accuracy_or_width->accuracy_or_width_flags);

  // //   if (token_accuracy_or_width->accuracy_or_width_flags.star &&
  // //       token_accuracy_or_width->accuracy_or_width_flags.number)
  // //
  // init_accuracy_or_width(&token_accuracy_or_width->accuracy_or_width_flags);

  // //   *current_start_index = index;

   return index;
  //return 0;
}

void parse_to_accuracy(TokenAccuracyOrWidth_t *token_width, char *format_string, int current_start_index,int current_length) {}
void parse_to_length(int current_character) {}
void parse_to_spec(int current_character) {}

// int is_a_point(int character) {
//   int result = 0;
//   return result;
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
//   parse_token_character_to_accuracy_or_width(specified_token,
//   &current_index,
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

//   token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy =
//   1;

//   token_length = token->token_size;
//   //звезда и число вместе дают не формат
//   for (index = *current_start_index; index < token_length &&
//   continue_parsing;
//        index++) {
//     current_character = token->token_string[index];

//     switch (current_character) {
//     case star:
//       token_accuracy_or_width->accuracy_or_width_flags.no_width_or_accuracy
//       = 0; token_accuracy_or_width->accuracy_or_width_flags.star = 1;
//       break;
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
//   if (token->token_string[index] != '\0' && token->token_string[index] !=
//   '.'
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

void print_generated_tokens(FormattedToken_t *tokens, const char *format,
                            int tokens_count) {
  char *format_string = NULL;
  int begin_index = 0;
  int end_index = 0;
  format_string = format;
  printf("\nTokens count = %d items\n\n", tokens_count);

  for (int j = 0; j < tokens_count; j++) {
    printf("-------------------------------------------------------------------"
           "\n");
    switch (tokens[j].token_type) {
    case text:
      printf("\tToken type : text\n");
      break;
    case integer:
      printf("\tToken type : integer\n");
      break;
    case string:
      printf("\tToken type : string\n");
      break;
    case no_type:
      printf("\tToken type : no type\n");
      break;
    }

    // format_string = tokens[j].format_string;
    printf("\tToken begin index = %d\n\tToken length = %d\n",
           tokens[j].token_format_string_data.data_start_index,
           tokens[j].token_format_string_data.data_length);

    printf("\tToken string : \"");

    begin_index = tokens[j].token_format_string_data.data_start_index;
    end_index = tokens[j].token_format_string_data.data_start_index +
                tokens[j].token_format_string_data.data_length;

    for (int k = begin_index; k < end_index && format_string[k]; k++)
      putchar(format_string[k]);

    printf("\"\n\tToken value : \"");

    

    if (tokens[j].token_value_string_data.data_start_index >= 0 &&
        tokens[j].token_value_string_data.data_length > 0) {
      begin_index = tokens[j].token_value_string_data.data_start_index;
      end_index = tokens[j].token_value_string_data.data_start_index +
                  tokens[j].token_value_string_data.data_length;

      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);
    }

    printf("\"\n");

    printf("\tToken value begin index = %d\n\tToken value length = %d\n",
           tokens[j].token_value_string_data.data_start_index,
           tokens[j].token_value_string_data.data_length);

    printf("\tToken flags :\n");

    printf("\t\tno_flags = %d\n\t\tminus = %d\n\t\tplus = %d\n\t\tspace = "
           "%d\n\t\tsharp = %d\n\t\tzero = %d\n",
           tokens[j].token_flags.no_flags, tokens[j].token_flags.minus,
           tokens[j].token_flags.plus, tokens[j].token_flags.space,
           tokens[j].token_flags.sharp, tokens[j].token_flags.zero);
    
    printf("\t\tflags_length = %d\n",tokens[j].token_flags.flags_length);

// typedef struct token_accuracy_or_width {
//   AccuracyOrWidthType_t value_type;
//   FormatStringData_t accuracy_or_width_data;
// } TokenAccuracyOrWidth_t;

// typedef struct format_string_data{
//   int data_start_index;
//   int data_length;
// }FormatStringData_t;

// typedef struct formatted_token {
//   FormatStringData_t token_format_string_data;
//   FormatStringData_t token_value_string_data;
//   char token_string[256]; //позже изменить эту дичь на маллок
//   char token_value[256]; //позже изменить эту дичь на маллок
//   Flags_t token_flags;
//   TokenAccuracyOrWidth_t token_width;
//   TokenAccuracyOrWidth_t token_accuracy;
//   LengthFormat_t token_length;
//   char *format_string;
//   TokenType_t token_type;
//   // int token_size;
//   // int token_position;
// } FormattedToken_t;
    printf("\tToken width:\n");
// typedef enum accuracy_or_width_type {
//   no_width_or_accuracy,
//   number,
//   star = '*'//,
//   //not_width_or_accuracy
// } AccuracyOrWidthType_t;
    if(tokens[j].token_width.value_type==no_width_or_accuracy)
      printf("\t\tNo width\n");

    if(tokens[j].token_width.value_type==star)
      printf("\t\tStar: ");

    if(tokens[j].token_width.value_type==number)
      printf("\t\tNumber: ");

    if (tokens[j].token_width.accuracy_or_width_data.data_start_index >= 0 &&
        tokens[j].token_width.accuracy_or_width_data.data_length > 0) {
      begin_index = tokens[j].token_width.accuracy_or_width_data.data_start_index;
      end_index = tokens[j].token_width.accuracy_or_width_data.data_start_index +
                  tokens[j].token_width.accuracy_or_width_data.data_length;

      printf("\"");
      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);
      
      printf("\"\n");
      }
      

    // current_token->token_value_string_data.begin_index = begin_index;
    // current_token->token_value_string_data.begin_index = 1;

    printf("\n---------------------------------------------------------------"
           "---\n\n");
  }
}
