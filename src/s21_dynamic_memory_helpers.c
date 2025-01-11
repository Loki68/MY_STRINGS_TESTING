#include "s21_dynamic_memory_helpers.h"

//строим массив для хранения инфы о лексеммах
TokenIndicesAndType_t *
TokenIndicesAndType_t_create_array(unsigned long elements_count) {
  TokenIndicesAndType_t *tokens_metrics_array = NULL;

  if (elements_count)
    tokens_metrics_array = (TokenIndicesAndType_t *)calloc(
        elements_count, sizeof(TokenIndicesAndType_t));

  return tokens_metrics_array;
}

//прибираемся после парсинга лексемм
void TokenIndicesAndType_t_delete_array(TokenIndicesAndType_t *tokens_metrics) {
  if (tokens_metrics) {
    free(tokens_metrics);
    tokens_metrics = NULL;
  }
}

FormatForToken_t *FormatForToken_t_create() {
  FormatForToken_t *format_for_token = NULL;

  format_for_token = (FormatForToken_t *)malloc(sizeof(FormatForToken_t));

  return format_for_token;
}

void FormatForToken_t_delete(FormatForToken_t *format_for_token) {
  if (format_for_token) {
    free(format_for_token);

    format_for_token = NULL;
  }
}

Flags_t *Flags_t_create() {
  Flags_t *flags_for_token = NULL;

  flags_for_token = (Flags_t *)malloc(sizeof(Flags_t));

  return flags_for_token;
}

void Flags_t_delete(Flags_t *flags_for_token) {
  if (flags_for_token) {
    free(flags_for_token);

    flags_for_token = NULL;
  }
}