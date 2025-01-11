#ifndef S21_STRING_HELPERS_H_INCLUDED
#define S21_STRING_HELPERS_H_INCLUDED

#include "../libs/s21_string.h" //заменить на реализации нужных функций
#include "s21_dynamic_memory_helpers.h"

#include <stdio.h> //похже удалить

//позже удалить
void print_lexemmes_throught_format_string(
    TokenIndicesAndType_t *tokens_metrics, int tokens_count,
    const char *format_string);
//позже удалить
void print_generated_tokens(FormattedToken_t *tokens, int tokens_count);

void preparse_string_to_lexemmes(TokenIndicesAndType_t *returned_tokens_metrics,
                                 int *returned_tokens_count,
                                 const char *format_sting);

void build_text_token(const char *format_string,
                      TokenIndicesAndType_t *token_metrics,
                      FormattedToken_t *text_token);
void build_specified_token(const char *format_string,
                           TokenIndicesAndType_t *token_metrics,
                           FormattedToken_t *specified_token);

#endif