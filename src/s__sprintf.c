#include "s__sprintf.h"
#include <stdlib.h>

#include "s__string_helpers.h"

//закончить сраный спринтф
//баг в подсчете lenght проверь 5,6,7 -done
// bug with % in the end of string

//вот с утра
void print_format_string_in_buffer(char *buffer_for_printing,
                                   FormattedToken_t *token,va_list *argument) {
    s21_size_t value=0;

    if(token->token_width.value_type==star){
      value=va_arg(*argument,unsigned long);
      printf("\nwidth value : %ld\n",value);
      token->token_width.long_value=value;}

    if(token->token_accuracy.value_type==star){
      value=va_arg(*argument,unsigned long);
      printf("\naccuracy value : %ld\n",value);
      token->token_accuracy.long_value=value;}

    switch (token->token_type) {
    case text:
      print_text_in_buffer(token, buffer_for_printing);
      break;
    // case integer:
    //   print_integer_in_buffer(&tokens[i], buffer_for_printing);
    //   break;
    // case real:
    //   print_real_in_buffer(&tokens[i], buffer_for_printing);
    //   break;
    case string:
      token->variadic_argument=va_arg(*argument,char*);
      //printf("argument : %s\n",(char*)token->variadic_argument);
      print_string_in_buffer(token, buffer_for_printing);
      break;
    // case single_character:
    //   print_single_character_in_buffer(&tokens[i], buffer_for_printing);
    //   break;
    // case no_type:
    //   break;
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

int s__sprintf(char *str, const char *format, ...) {

  FormattedToken_t *tokens = NULL;
  //char *buffer_for_printing = NULL;

  // s21_size_t tokens_metrics_size = 0;
  //считаем точное число токенов, стобы выделить память под массив токенов
  int tokens_count = 0;
  int spec_tokens_count = 0;

  va_list arguments;

  

  // проверить сначала строку на пустоту
  // и действовать под этим условием
  if (format)
    tokens_count = get_percent_count(format);

  tokens = FormattedToken_t_create_array(tokens_count);

  if (tokens) {
    parse_string(format, tokens_count, tokens);

    parse_format_of_tokens(tokens, tokens_count);

    tokens_count = correct_initialized_tokens_count(tokens, tokens_count);

    spec_tokens_count = get_count_of_spec_tokens(tokens, tokens_count);

    print_generated_tokens(tokens, format, tokens_count);
    
    if(spec_tokens_count)
      va_start(arguments,spec_tokens_count);

    for (int i = 0; i < tokens_count; i++){
      print_format_string_in_buffer(str, &tokens[i],&arguments);
      }


    // //
    // // printf("\nresult tokens count = %d\n", tokens_count);
    // // printf("spec tokens count is %d\n\n", spec_tokens_count);

    if(arguments)
      va_end(arguments);

    FormattedToken_t_delete_array(tokens);
    tokens = NULL;
  }

  return 0;
}