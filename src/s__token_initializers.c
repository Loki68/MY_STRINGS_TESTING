#include "s__string_helpers.h"

#include "../libs/s21_string.h"

void initialize_token(FormattedToken_t *new_token, const char *format) {

  initialize_string_data(&new_token->token_format_string_data);
  initialize_string_data(&new_token->token_value_string_data);

  initialize_flags(&new_token->token_flags);

  initialize_accuracy_or_width(&new_token->token_width);
  initialize_accuracy_or_width(&new_token->token_accuracy);

  initialize_length(&new_token->token_length);

  initialize_spec(&new_token->token_spec);

  new_token->format_string = (char *)format;
  new_token->token_type = no_type;
  new_token->is_initialized = 1;
}

void initialize_string_data(FormatStringData_t *string_data) {
  FormatStringData_t *current_string_data = NULL;

  current_string_data = string_data;

  current_string_data->data_start_index = -1;
  current_string_data->data_length = 0;
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
  current_token_flags->flags_length = 0;
}

void initialize_accuracy_or_width(
    TokenAccuracyOrWidth_t *token_accuracy_or_width) {
  TokenAccuracyOrWidth_t *current_accuracy_or_width = NULL;

  current_accuracy_or_width = token_accuracy_or_width;

  current_accuracy_or_width->value_type = no_width_or_accuracy;

  current_accuracy_or_width->long_value=0;

  initialize_string_data(&current_accuracy_or_width->accuracy_or_width_data);
}

void initialize_length(LengthFormat_t *token_length) {
  LengthFormat_t *current_token_length = NULL;

  current_token_length = token_length;

  current_token_length->length_type = no_length;

  initialize_string_data(&current_token_length->length_data);
}

void initialize_spec(SpecFormat_t *token_spec) {
  SpecFormat_t *current_token_spec = NULL;

  current_token_spec = token_spec;

  current_token_spec->type = no_spec;

  initialize_string_data(&current_token_spec->spec_format_data);
}