#include "s__string_helpers.h"

#include "../libs/s21_string.h"

void print_text_in_buffer(FormattedToken_t *token, char *buffer_for_printing) {
  char *string = NULL;
  int current_length = 0;

  string = token->format_string;
  current_length = token->token_value_string_data.data_length;

  s21_strncat(buffer_for_printing,&string[token->token_value_string_data.data_start_index],current_length);
}

void print_integer_in_buffer(FormattedToken_t *token,
                             char *buffer_for_printing) {
  char *string = NULL;
  int current_index = 0;
  int current_length = 0;

  string = token->format_string;
  current_index = token->token_format_string_data.data_start_index;
  current_length = token->token_format_string_data.data_length + current_index;

  printf("\ninteger : ");

  for (; current_index < current_length && string[current_index];
       current_index++)
    putchar(string[current_index]);

  putchar('\n');
}

void print_real_in_buffer(FormattedToken_t *token, char *buffer_for_printing) {
  char *string = NULL;
  int current_index = 0;
  int current_length = 0;

  string = token->format_string;
  current_index = token->token_format_string_data.data_start_index;
  current_length = token->token_format_string_data.data_length + current_index;

  printf("\nreal : ");

  for (; current_index < current_length && string[current_index];
       current_index++)
    putchar(string[current_index]);

  putchar('\n');
}

//доработать формат
void print_string_in_buffer(FormattedToken_t *token,
                            char *buffer_for_printing) {
  char *va_string = NULL;
  int current_index = 0;
  s21_size_t current_length = 0;
  s21_size_t accuracy=0;
  s21_size_t width=0;
  s21_size_t box_size=0;
  s21_size_t value_size=0;

  va_string=(char*)token->variadic_argument;
  accuracy=token->token_accuracy.long_value;
  width =token->token_width.long_value;
  current_length=s21_strlen(va_string);
  box_size=(int)current_length;
  value_size=(int)current_length;
  current_index=0;

  if(width && width>current_length)
    box_size=(int)width;

  if(accuracy && accuracy<current_length)
    value_size=(int)accuracy;
  
  char string[(int)box_size+1];  
  string[(int)box_size]='\0';
  //доработать и тесты тесты тесты
  current_index=(int)(box_size-value_size);
  s21_memset(string,' ',(int)box_size);
  
  s21_strncpy(string+current_index,va_string,value_size);
  
  s21_strncat(buffer_for_printing,string,(int)box_size);
  
}

void print_single_character_in_buffer(FormattedToken_t *token,
                                      char *buffer_for_printing) {
  char *string = NULL;
  int current_index = 0;
  int current_length = 0;

  //*buffer_for_printing=

  string = token->format_string;
  current_index = token->token_format_string_data.data_start_index;
  current_length = token->token_format_string_data.data_length + current_index;

  printf("\nsingle_character : ");

  for (; current_index < current_length && string[current_index];
       current_index++)
    putchar(string[current_index]);

  putchar('\n');
}

void print_generated_tokens(FormattedToken_t *tokens, const char *format,
                            int tokens_count) {
  char *format_string = NULL;
  int begin_index = 0;
  int end_index = 0;
  format_string = format;
  printf("\nTokens count = %d items\n\n", tokens_count);

  for (int j = 0; j < tokens_count; j++) {
    printf("-------------------------------------------------------------------"
           "\n");
    switch (tokens[j].token_type) {
    case text:
      printf("\tToken type : text\n");
      break;
    case integer:
      printf("\tToken type : integer\n");
      break;
    case string:
      printf("\tToken type : string\n");
      break;
    case no_type:
      printf("\tToken type : no type\n");
      break;
    }

    printf("\tToken initializing status : ");
    if (tokens[j].is_initialized)
      printf("initialized\n");
    else
      printf("not initialized\n");

    // format_string = tokens[j].format_string;
    printf("\tToken begin index = %d\n\tToken length = %d\n",
           tokens[j].token_format_string_data.data_start_index,
           tokens[j].token_format_string_data.data_length);

    printf("\tToken string : \"");

    begin_index = tokens[j].token_format_string_data.data_start_index;
    end_index = tokens[j].token_format_string_data.data_start_index +
                tokens[j].token_format_string_data.data_length;

    for (int k = begin_index; k < end_index && format_string[k]; k++)
      putchar(format_string[k]);

    printf("\"\n\tToken value : \"");

    if (tokens[j].token_value_string_data.data_start_index >= 0 &&
        tokens[j].token_value_string_data.data_length > 0) {
      begin_index = tokens[j].token_value_string_data.data_start_index;
      end_index = tokens[j].token_value_string_data.data_start_index +
                  tokens[j].token_value_string_data.data_length;

      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);
    }

    printf("\"\n");

    printf("\tToken value begin index = %d\n\tToken value length = %d\n",
           tokens[j].token_value_string_data.data_start_index,
           tokens[j].token_value_string_data.data_length);

    printf("\tToken flags :\n");

    printf("\t\tno_flags = %d\n\t\tminus = %d\n\t\tplus = %d\n\t\tspace = "
           "%d\n\t\tsharp = %d\n\t\tzero = %d\n",
           tokens[j].token_flags.no_flags, tokens[j].token_flags.minus,
           tokens[j].token_flags.plus, tokens[j].token_flags.space,
           tokens[j].token_flags.sharp, tokens[j].token_flags.zero);

    printf("\t\tflags_length = %d\n", tokens[j].token_flags.flags_length);

    printf("\tToken width: ");
    if (tokens[j].token_width.value_type == no_width_or_accuracy)
      printf("No width\n\t");

    if (tokens[j].token_width.value_type == star)
      printf("Star\n\t");

    if (tokens[j].token_width.value_type == number)
      printf("Number\n\t");

    if (tokens[j].token_width.accuracy_or_width_data.data_start_index >= 0 &&
        tokens[j].token_width.accuracy_or_width_data.data_length > 0) {
      begin_index =
          tokens[j].token_width.accuracy_or_width_data.data_start_index;
      end_index =
          tokens[j].token_width.accuracy_or_width_data.data_start_index +
          tokens[j].token_width.accuracy_or_width_data.data_length;

      printf("\tWidth value : \"");
      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);

      printf("\"\n\t");
    }

    printf("\tWidth start index : %d\n\t\tWidth length: %d\n",
           tokens[j].token_width.accuracy_or_width_data.data_start_index,
           tokens[j].token_width.accuracy_or_width_data.data_length);

    printf("\t\tWidth long_value : %ld\n",tokens[j].token_width.long_value);

    printf("\tToken accuracy: ");
    if (tokens[j].token_accuracy.value_type == no_width_or_accuracy)
      printf("No accuracy\n\t");

    if (tokens[j].token_accuracy.value_type == star)
      printf("Star\n\t");

    if (tokens[j].token_accuracy.value_type == number)
      printf("Number\n\t");

    if (tokens[j].token_accuracy.accuracy_or_width_data.data_start_index >= 0 &&
        tokens[j].token_accuracy.accuracy_or_width_data.data_length > 0) {
      begin_index =
          tokens[j].token_accuracy.accuracy_or_width_data.data_start_index;
      end_index =
          tokens[j].token_accuracy.accuracy_or_width_data.data_start_index +
          tokens[j].token_accuracy.accuracy_or_width_data.data_length;

      printf("\tAccuracy value : \"");
      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);

      printf("\"\n\t");
    }

    printf("\tAccuracy start index : %d\n\t\tAccuracy length: %d\n",
           tokens[j].token_accuracy.accuracy_or_width_data.data_start_index,
           tokens[j].token_accuracy.accuracy_or_width_data.data_length);

    printf("\t\tAccuracy long_value : %ld\n",tokens[j].token_accuracy.long_value);

    printf("\tToken length : ");
    switch (tokens[j].token_length.length_type) {
    case no_length:
      printf("no length\n\t");
      break;
    case short_or_unsigned_short_int_length:
      printf("short int or unsigned short\n");
      break;
    case long_int_length:
      printf("long int\n");
      break;
    case long_double_length:
      printf("long float\n");
      break;
    }

    if (tokens[j].token_length.length_data.data_start_index >= 0 &&
        tokens[j].token_length.length_data.data_length > 0) {
      begin_index = tokens[j].token_length.length_data.data_start_index;
      end_index = tokens[j].token_length.length_data.data_start_index +
                  tokens[j].token_length.length_data.data_length;

      printf("\tLength value : \"");
      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);

      printf("\"\n\t");
    }

    printf("\tLength start index : %d\n\t\tLength length: %d\n",
           tokens[j].token_length.length_data.data_start_index,
           tokens[j].token_length.length_data.data_length);

    //     typedef struct formatted_token {
    //   FormatStringData_t token_format_string_data;
    //   FormatStringData_t token_value_string_data;
    //   Flags_t token_flags;
    //   TokenAccuracyOrWidth_t token_width;
    //   TokenAccuracyOrWidth_t token_accuracy;
    //   LengthFormat_t token_length;
    //   SpecFormat_t token_spec;
    //   char *format_string;
    //   TokenType_t token_type;
    //   int is_initialized;
    // } FormattedToken_t;

    // typedef enum spec_type{
    // no_spec,
    //   c='c', d='d', f='f', s='s', u='u',g='g', G='G', e='e', E='E', x='x',
    //   X='X', o='o', p='p'
    // }SpecType_t;
    printf("\tToken spec : ");
    switch (tokens[j].token_spec.type) {
    case no_spec:
      printf("no_spec\n\t");
      break;
    case c:
      printf("c\n\t");
      break;
    case d:
      printf("d\n");
      break;
    case f:
      printf("f\n");
      break;
    case s:
      printf("s\n");
      break;
    case u:
      printf("u\n");
      break;
    case g:
      printf("g\n");
      break;
    case G:
      printf("G\n");
      break;
    case e:
      printf("e\n");
      break;
    case E:
      printf("E\n");
      break;
    case x:
      printf("x\n");
      break;
    case X:
      printf("X\n");
      break;
    case o:
      printf("o\n");
      break;
    case p:
      printf("p\n");
      break;
    }

    if (tokens[j].token_spec.spec_format_data.data_start_index >= 0 &&
        tokens[j].token_spec.spec_format_data.data_length > 0) {
      begin_index = tokens[j].token_spec.spec_format_data.data_start_index;
      end_index = tokens[j].token_spec.spec_format_data.data_start_index +
                  tokens[j].token_spec.spec_format_data.data_length;

      printf("\tSpec value : \"");
      for (int k = begin_index; k < end_index && format_string[k]; k++)
        putchar(format_string[k]);

      printf("\"\n\t");
    }

    printf("\tSpec start index : %d\n\t\tSpec length: %d\n",
           tokens[j].token_spec.spec_format_data.data_start_index,
           tokens[j].token_spec.spec_format_data.data_length);

    printf("\n---------------------------------------------------------------"
           "---\n\n");
  }
}
