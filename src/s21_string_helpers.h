#ifndef S21_STRING_HELPERS_H_INCLUDED
#define S21_STRING_HELPERS_H_INCLUDED

#include "../libs/s21_string.h" //заменить на реализации нужных функций
#include "s21_dynamic_memory_helpers.h"

#include <stdio.h> //похже удалить

typedef enum accuracy_or_with_flag {
  accuracy_flag,
  width_flag
} AccuracyOrWidthFlag_t;

typedef enum parsing_state {
  parsing_text,
  parsing_specs_text,
  parsing_end
} ParsingState_t;

// //позже удалить
// void print_lexemmes_throught_format_string(
//     TokenIndicesAndType_t *tokens_metrics, int tokens_count,
//     const char *format_string);
// //позже удалить
void print_generated_tokens(FormattedToken_t *tokens, int tokens_count);
void initialize_token(FormattedToken_t *new_token, int tokens_count);
int change_tokens_count(FormattedToken_t *last_token, int tokens_count);
ParsingState_t parse_to_text(FormattedToken_t *token, const char *format_string,
                             int *returned_index);
ParsingState_t parse_specs_to_text(FormattedToken_t *token,
                                   const char *format_string,
                                   int *returned_index);
// void parse_to_flag(int current_character);
// void parse_to_width(int current_character);
// void parse_to_accuracy(int current_character);
// void parse_to_length(int current_character);
// void parse_to_spec(int current_character);
// void preparse_string_to_lexemmes(TokenIndicesAndType_t
// *returned_tokens_metrics,
//                                  int *returned_tokens_count,
//                                  const char *format_sting, int
//                                  format_length);

// void parse_lexemmes_to_tokens(const char *format_string,
//                               TokenIndicesAndType_t *token_metrics,
//                               int token_metrics_length,
//                               FormattedToken_t *tokens);

// correct
int get_percent_count(const char *format_string);

void parse_string(const char *format_string, int tokens_length,
                  FormattedToken_t *tokens);

// void build_text_token(const char *format_string,
//                       TokenIndicesAndType_t *token_metrics,
//                       FormattedToken_t *text_token);
// void build_specified_token(const char *format_string,
//                            TokenIndicesAndType_t *token_metrics,
//                            FormattedToken_t *specified_token);
// void parse_token_character_to_flag(FormattedToken_t *token,
//                                    int *current_start_index);
// void parse_token_character_to_accuracy_or_width(
//     FormattedToken_t *token, int *current_start_index,
//     AccuracyOrWidthFlag_t is_accuracy_or_width);

// void init_accuracy_or_width(AccuracyOrWidth_t *token_accuracy_or_width);

int is_a_digit(int character);
int is_a_point(int character);

#endif