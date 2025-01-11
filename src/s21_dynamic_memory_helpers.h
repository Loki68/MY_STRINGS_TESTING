#ifndef S21_DYNAMIC_MEMORY_HELPERS_H_INCLUDED
#define S21_DYNAMIC_MEMORY_HELPERS_H_INCLUDED

#include <stdlib.h>

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

typedef enum accuracy_or_width_type {
  no_width_or_accuracy,
  number,
  star = '*'
} AccuracyOrWidthType_t;

typedef enum length {
  //мб и нинад
  no_length,
  short_int_or_unsigned_short = 'h',
  long_int = 'l',
  long_float = 'L'
} Length_t;

typedef struct token_accuracy_or_width {
  AccuracyOrWidthType_t type;
  int accuracy_or_width_value;
} TokenAccuracyOrWidth_t;

typedef struct format_for_token {
  Flags_t token_flags;
  TokenAccuracyOrWidth_t token_width;
  TokenAccuracyOrWidth_t token_accuracy;
  Length_t token_length;
  // int is_not_format; //чтобы считать, что у нас текст
} FormatForToken_t;

// not format and union of this
//  typedef struct format {
//    Generic_Token_t generic_token;
//    int token_type;
//  } Format_t;

typedef struct formatted_token {
  char token_string[256]; //позже изменить эту дичь на маллок
  char token_value[256]; //позже изменить эту дичь на маллок
  FormatForToken_t token_format;
  TokenType_t token_type;
  int token_size;
  int token_position;
} FormattedToken_t;

// typedef struct text_token {
//   char token_string[256];
//   char token_value[256];
//   int token_size;
//   int token_position;
// } TextToken_t;

// typedef union generic_token {
//   FormattedToken_t formatted_token;
//   TextToken_t text_token;
// } Generic_Token_t;

// typedef struct token {
//   Generic_Token_t generic_token;
//   int token_type;
// } Token_t;

//работай плоской простыней структур,идиотто)
TokenIndicesAndType_t *
TokenIndicesAndType_t_create_array(unsigned long elements_count);
void TokenIndicesAndType_t_delete_array(TokenIndicesAndType_t *tokens_metrics);

FormattedToken_t *FormattedToken_t_create(unsigned long elements_count);
void FormattedToken_t_delete(FormattedToken_t *formated_token);

// FormatForToken_t *FormatForToken_t_create();
// void FormatForToken_t_delete(FormatForToken_t *format_for_token);

// Flags_t *Flags_t_create();
// void Flags_t_delete(Flags_t *flags_for_token);
#endif