#include "s21_sprintf.h"

#include "s21_string_helpers.h"

//закончить сраный спринтф
//баг в подсчете lenght проверь 5,6,7 -done
//bug with % in the end of string

//вот с утра
void print_format_string_in_buffer(char *buffer_for_printing,
                                   FormattedToken_t *tokens,int tokens_count,
                                   int spec_tokens_count) {
  for(int i=0;i<tokens_count;i++){
    switch(tokens[i].token_type){
      case text:
      print_text_in_buffer(&tokens[i],buffer_for_printing);
      break;
      case integer:
      print_integer_in_buffer(&tokens[i],buffer_for_printing);
      break;
      case real:
      print_real_in_buffer(&tokens[i],buffer_for_printing);
      break;
      case string:
      print_string_in_buffer(&tokens[i],buffer_for_printing);
      break;
      case single_character:
      print_single_character_in_buffer(&tokens[i],buffer_for_printing);
      break;
      case no_type:
      break;
    }
  }


  //  va_list arg=NULL;
  //  int va_args_count = 0;            // указатель на параметр

  //   va_start(arg, count);   // получение адреса первого вариадического
  //   параметра

  //   for(int i=0; i < count; ++i) {
  //               s += va_arg(arg, long);  // получение значение вариадического
  //               параметра
  //                                       // и переход к следующему параметру
  //   }

  //   va_end(arg);               // завершение процедуры перебора вариадических
  //   параметров
}

int s21_sprintf(char *str, const char *format, ...) {
  // FormattedToken_t *tokens = S21_NULL;
  // char *buffer_for_printing = S21_NULL;

  FormattedToken_t *tokens = NULL;
  char *buffer_for_printing = NULL;

  // s21_size_t tokens_metrics_size = 0;
  //считаем точное число токенов, стобы выделить память под массив токенов
  int tokens_count = 0;
  int spec_tokens_count = 0;

  // проверить сначала строку на пустоту
  // и действовать под этим условием
  if (format)
    tokens_count = get_percent_count(format);

  tokens = FormattedToken_t_create_array(tokens_count);

  if (tokens) {
    parse_string(format, tokens_count, tokens);

    parse_format_of_tokens(tokens, tokens_count);

    printf("previous tokens count = %d\n", tokens_count);

    tokens_count=correct_initialized_tokens_count(tokens,tokens_count);

    

    spec_tokens_count = get_count_of_spec_tokens(tokens, tokens_count);

    

    
    //а эту подчистить после написания
    print_generated_tokens(tokens, format, tokens_count);

//проверь парсер,он врет!!11
    //завершение писанины
    print_format_string_in_buffer(buffer_for_printing, tokens,tokens_count,
                                  spec_tokens_count);
    printf("\nresult tokens count = %d\n", tokens_count);
    printf("spec tokens count is %d\n\n",spec_tokens_count);

    FormattedToken_t_delete_array(tokens);
    tokens = NULL;
  }

  return 0;
}