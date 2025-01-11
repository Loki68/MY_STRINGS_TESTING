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

FormattedToken_t *FormattedToken_t_create(unsigned long elements_count) {
  FormattedToken_t *formated_token = NULL;

  if (elements_count)
    formated_token =
        (FormattedToken_t *)calloc(elements_count, sizeof(FormattedToken_t));

  return formated_token;
}

void FormattedToken_t_delete(FormattedToken_t *formated_token) {
  if (formated_token) {
    free(formated_token);

    formated_token = NULL;
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