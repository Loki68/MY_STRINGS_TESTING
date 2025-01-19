//#include "../src/s21_string.h"
#include "../s21_dynamic_memory_helpers.h"
#include "../s21_string_helpers.h"
#include "../s21_sprintf.h"

#include <stdio.h>
//необходима тому же check.h, чтобы взять тот же пустой указатель NULL
#include <stdlib.h>
//собственно подключение библиотеки для тестирования
#include <check.h>
//ну  эталонная реализация, с которой сравнивать наши реализации функций
#include <string.h>

//чтобы добавить новый набор тестов, нужно просто добавить аналогичную строку
//ниже:
//  Suite *подходящее_название(void);
//а в файле название_тестируемой_функции.c добавить такую же шаблонную
//реализацию

Suite *s21_dynamic_memory_helpers_suite(void);
Suite *s21_string_helpers_suite(void);
Suite *s21_sprintf_suite(void);