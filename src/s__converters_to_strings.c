#include "s__string_helpers.h"

#include <math.h>

void s21_reverse_value_string(char *value_string, int value_string_length) {
  char temp_char = 0;
  int start_index = 0;
  int end_index = value_string_length;

  end_index--;

  for (; start_index < end_index; end_index--, start_index++) {
    temp_char = value_string[start_index];
    value_string[start_index] = value_string[end_index];
    value_string[end_index] = temp_char;
  }
}

//мб лонги
void s21_integer_by_base_to_string(char *buffer, int integer, int base) {
  int index = 0;
  int is_negative = 0;
  int tmp_digit = 0;

  if (!integer) {
    buffer[index] = '0';
    index++;
  }

  if (integer < 0 && base == 10) {
    is_negative = 1;
    integer = -integer;
  }

  for (; integer; index++) {
    tmp_digit = integer % base;

    if (tmp_digit > 9)
      buffer[index] = tmp_digit + 87;
    else
      buffer[index] = tmp_digit + 48;

    integer = integer / base;
  }

  if (is_negative) {
    buffer[index] = '-';
    index++;
  }

  buffer[index] = '\0';

  s21_reverse_value_string(buffer, index);
}

int s21_integer_for_real_to_string(char *buffer, long long integer,
                                   int accuracy, int is_negative) {
  int index = 0;
  int value = 0;
  int is_zero = 0;

  if (integer == 0) is_zero = 1;

  for (; integer || index < accuracy; index++) {
    if (is_zero)
      value = '0';
    else {
      value = (integer % 10) + '0';
      integer /= 10;
    }

    buffer[index] = value;
  }

  if (is_negative) {
    buffer[index] = '-';
    index++;
  }

  buffer[index] = '\0';

  if (!is_zero) s21_reverse_value_string(buffer, index);

  return index;
}

void s21_real_to_string(char *buffer, long double real, int accuracy) {
  long long before_point = 0;
  long long long_long_after_point = 0;
  long double after_point = .0;
  int index = 0;
  int is_negative = 0;

  if (real < 0) {
    is_negative = 1;
    real = -real;
  }

  before_point = (long long)real;

  after_point = real - before_point;

  index = s21_integer_for_real_to_string(buffer, before_point, ZERO_ACCURACY,
                                         is_negative);

  if (accuracy < 0) accuracy = NEG_ACCURACY;

  if (accuracy) {
    is_negative = 0;

    buffer[index] = '.';

    after_point *= pow(10, accuracy);

    long_long_after_point = llround(after_point);

    index++;

    s21_integer_for_real_to_string(&buffer[index], long_long_after_point,
                                   accuracy, is_negative);
  }
}