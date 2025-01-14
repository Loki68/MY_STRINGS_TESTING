#ifndef S21_STRING_HELPERS_H_INCLUDED
#define S21_STRING_HELPERS_H_INCLUDED

#include "../libs/s21_string.h" //заменить на реализации нужных функций
#include "s21_dynamic_memory_helpers.h"

#include <stdio.h> //похже удалить

// typedef enum accuracy_or_with_flag {
//   accuracy_flag,
//   width_flag
// } AccuracyOrWidthFlag_t;

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
void print_generated_tokens(FormattedToken_t *tokens, const char *format,
                            int tokens_count);
//
void initialize_token(FormattedToken_t *new_token, const char *format);
void initialize_string_data(FormatStringData_t *string_data);
void initialize_flags(Flags_t *token_flags);
void initialize_accuracy_or_width(
    TokenAccuracyOrWidth_t *token_accuracy_or_width);
void initialize_length(LengthFormat_t *token_length);
void initialize_spec(SpecFormat_t *token_spec);
//
int update_tokens_count(FormattedToken_t *last_token, int tokens_count);
//
ParsingState_t parse_to_text(FormattedToken_t *token, int *returned_index);
ParsingState_t parse_specs_to_text(FormattedToken_t *token,
                                   int *returned_index);
//
void parse_format_of_tokens(FormattedToken_t *tokens, int tokens_count);
void try_parse_percents_to_text(FormattedToken_t *token);
void fill_text_token_value(FormattedToken_t *token);
void parse_single_format_of_token(FormattedToken_t *token);
int parse_to_flags(Flags_t *token_flags, FormatStringData_t *format_data,
                   char *format_string);
int parse_to_width(TokenAccuracyOrWidth_t *token_width, char *format_string,
                   int current_start_index, int current_length);
int parse_to_accuracy(TokenAccuracyOrWidth_t *token_accuracy,
                      char *format_string, int current_start_index,
                      int current_length);
void parse_to_length(LengthFormat_t *token_length, char *format_string,
                     int current_start_index, int current_length);
int parse_to_spec(SpecFormat_t *token_spec, TokenType_t *token_type,
                  char format_character, int current_start_index);
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

// int is_a_digit(int character);
// int is_a_point(int character);

#endif