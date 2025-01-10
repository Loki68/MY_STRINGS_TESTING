#ifndef S21_STRING_HELPERS_H_INCLUDED
#define S21_STRING_HELPERS_H_INCLUDED

#include "../libs/s21_string.h" //заменить на реализации нужных функций
#include <stdio.h> //похже удалить

typedef enum type { text, integer, string } TokenType_t;

typedef struct token_indices_and_type {
  int token_begin_index;
  int token_end_index;
  TokenType_t token_type;
} TokenIndicesAndType_t;

// sprintf flags
typedef enum flags_enumeration {
  minus = '-',
  plus = '+',
  space = ' ',
  sharp = '#',
  zero = '0'
} FlagsEnumeration_t;

typedef struct flags {
  int no_flags;
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
} Flags_t;

typedef enum width_and_accuracy_type {
  no_item,
  number,
  star = '*'
} WidthAndAccuracyType_t;

// typedef enum accuracy { accuracy_number, accuracy_star } Accuracy_t;

typedef enum length {
  //мб и нинад
  no_length,
  short_int_or_unsigned_short = 'h',
  long_int = 'l',
  long_float = 'L'
} Length_t;

typedef struct token_accuracy_and_width {
  WidthAndAccuracyType_t type;
  int width_value;
} TokenAccuracyAndWidth_t;

typedef struct format_for_token {
  Flags_t token_flags;
  TokenAccuracyAndWidth_t token_width;
  TokenAccuracyAndWidth_t token_accuracy;
  Length_t token_length;
} FormatForToken_t;

typedef struct formatted_token {
  char token_string[256];
  char token_value[256];
  FormatForToken_t token_format;
  int token_size;
  int token_position;
} FormattedToken_t;

// typedef struct digit_token {
//   char token_string[256];
//   char token_value[256];
//   TokenFormat_t digit_format;
//   int token_size;
//   int token_position;
// } DigitToken_t;

// typedef struct string_token {
//   char token_string[256];
//   TokenFormat_t string format;
//   int token_size;
//   int token_position;
// } StringToken_t;

typedef struct text_token {
  char token_string[256];
  char token_value[256];
  int token_size;
  int token_position;
} TextToken_t;

typedef union generic_token {
  //   DigitToken_t digit_token;
  //   StringToken_t string_token;
  FormattedToken_t formatted_token;
  TextToken_t text_token;
} Generic_Token_t;

typedef struct token {
  Generic_Token_t generic_token;
  int token_type;
} Token_t;

//позже удалить
void print_lexemmes_throught_format_string(
    TokenIndicesAndType_t *tokens_metrics, int tokens_count,
    const char *format_string);
//позже удалить
void print_generated_tokens(Token_t *tokens, int tokens_count);

void preparse_string_to_lexemmes(TokenIndicesAndType_t *returned_tokens_metrics,
                                 int *returned_tokens_count,
                                 const char *format_sting);
void build_text_token(const char *format_string,
                      TokenIndicesAndType_t *token_metrics,
                      TextToken_t *text_token);
void build_specified_token(const char *format_string,
                           TokenIndicesAndType_t *token_metrics,
                           FormattedToken_t *specified_token);
// void build_digit_token(const char *format_string,
//                        TokenIndicesAndType_t *token_metrics,
//                        FormattedToken_t *digit_token);
// void build_string_token(const char *format_string,
//                         TokenIndicesAndType_t *token_metrics,
//                         FormattedToken_t *string_token);

#endif