PROGRAM = s21_strings_tests
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11

LIBRARY = ../libs
CLIBS = -L$(LIBRARY) -l:s21_string.a -lm
#CLIBS = -lm
TEST_LIB = 

SOURCE = main.c s__sprintf.c s__string_to_token_parsers.c s__dynamic_memory_helpers.c s__token_value_printers.c s__converters_to_strings.c s__token_initializers.c s__converters_from_strings.c
OBJECTS = main.o s__sprintf.o s__string_to_token_parsers.o s__dynamic_memory_helpers.o s__token_value_printers.o s__converters_to_strings.o s__token_initializers.o s__converters_from_strings.o

# SOURCE = s21_sprintf.c s21_string_helpers.c s21_dynamic_memory_helpers.c
# OBJECTS = s21_sprintf.o s21_string_helpers.o s21_dynamic_memory_helpers.o

# TEST_PROG = ./make_me_hard_baby
# TEST_DIR = tests
# TEST_SRC = $(TEST_DIR)/tests.c $(TEST_DIR)/s__sprintf_test.c $(TEST_DIR)/s21_string_helpers_test.c $(TEST_DIR)/s21_dynamic_memory_helpers_test.c
# TEST_OBJ = $(TEST_DIR)/tests.o $(TEST_DIR)/s__sprintf_test.o $(TEST_DIR)/s21_string_helpers_test.o $(TEST_DIR)/s21_dynamic_memory_helpers_test.o
# TEST_FLAGS = -lcheck -lrt -lm -lsubunit 

# GCOV_REPORT_DIR = ../gcov_report

#all : clean copy_lib build_program
#all : clean format build_program
all : clean build_program 

build_program : main s__dynamic_memory_helpers s__string_to_token_parsers s__sprintf s__token_value_printers s__token_initializers s__converters_to_strings s__converters_from_strings
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(CLIBS) 

main :
	$(CC) $(CFLAGS) -c main.c -o main.o

# build_test_program : s21_dynamic_memory_helpers s21_string_helpers s21_sprintf main
# 	$(CC) $(CFLAGS) $(TEST_SRC) $(SOURCE) -o $(TEST_PROGRAM) $(TEST_FLAGS)

# main :
# 	$(CC) $(CFLAGS) -c tests/tests.c -o tests/tests.o

s__sprintf :
	$(CC) $(CFLAGS) -c s__sprintf.c -o s__sprintf.o

s__string_to_token_parsers :
	$(CC) $(CFLAGS) -c s__string_to_token_parsers.c -o s__string_to_token_parsers.o

s__dynamic_memory_helpers :
	$(CC) $(CFLAGS) -c s__dynamic_memory_helpers.c -o s__dynamic_memory_helpers.o

s__converters_to_strings :
	$(CC) $(CFLAGS) -c s__converters_to_strings.c -o s__converters_to_strings.o

s__converters_from_strings :
	$(CC) $(CFLAGS) -c s__converters_from_strings.c -o s__converters_from_strings.o

s__token_initializers :
	$(CC) $(CFLAGS) -c s__token_initializers.c -o s__token_initializers.o

s__token_value_printers :
	$(CC) $(CFLAGS) -c s__token_value_printers.c -o s__token_value_printers.o

copy_lib : 
	mkdir ../libs
	cp ~/21-school-problems/C2_s21_stringplus-1/src/s21_string.a ~/21-school-problems/C2_s21_stringplus-1/src/s21_string.h ../libs/

format :
	clang-format -i *.c *.h
	
clean_lib :
	$(LIBRARY)/*.a $(LIBRARY)/*.h




# test : s21_dynamic_memory_helpers_tests s21_string_helpers_tests s21_sprintf_tests test_program
# 	$(TEST_PROG)

# test_program :
# 	$(CC) $(CFLAGS) $(TEST_SRC) $(SOURCE) -o $(TEST_PROG) $(TEST_FLAGS) --coverage

# s21_sprintf_tests :
# 	$(CC) $(CFLAGS) -c $(TEST_DIR)/s21_sprintf_test.c -o $(TEST_DIR)/s21_sprintf_test.o

# s21_string_helpers_tests :
# 	$(CC) $(CFLAGS) -c $(TEST_DIR)/s21_string_helpers_test.c -o $(TEST_DIR)/s21_string_helpers_test.o

# s21_dynamic_memory_helpers_tests :
# 	$(CC) $(CFLAGS) -c $(TEST_DIR)/s21_dynamic_memory_helpers_test.c -o $(TEST_DIR)/s21_dynamic_memory_helpers_test.o


# gcov_report : 
# # # В соответствии с требованием создания отчета, собираем:
# # # из файлов исходного кода функций нашей библиотеки $(SOURCE)
# # # из файлов исходного кода тестов $(TESTS)
# # # используя общие флаги $(CFLAGS)
# # # используя тестовые флаги для сборки с библиотекой check $(TEST_FLAGS)
# # # используя флаги для подсчета покрытия через gcov $(GCOV_FLAGS)
# # # исполняемый файл для составления отчета gcov $(TEST_PROGRAM)
# # # исполняемый файл тот же,что и просто в тестах. Просто собран иначе.
# # 	$(CC) $(CFLAGS) $(TESTS) $(SOURCE) -o $(TEST_PROGRAM) $(TEST_FLAGS) $(GCOV_FLAGS)
# 	$(CC) $(CFLAGS) $(TEST_SRC) $(SOURCE) -o $(TEST_PROG) $(TEST_FLAGS) --coverage
# # # Требование gcov - запустить получившегося франкенштейна
# # 	$(TEST_PROGRAM)
# 	$(TEST_PROG)
# # # Создаем папку для хранения отчета
# 	mkdir -p $(GCOV_REPORT_DIR)
# # # Собственно получаем файл с отчетом с учетом ветвлений - флаги $(BRANCHES)
# 	lcov -t "Report" -c -d . -o $(GCOV_REPORT_DIR)/coverage.info --rc lcov_branch_coverage=1
# # # и генерируем на основе файла с отчетом html разметку
# 	genhtml -o $(GCOV_REPORT_DIR)/html $(GCOV_REPORT_DIR)/coverage.info --rc lcov_branch_coverage=1

# # xdg-open $(GCOV_REPORT_DIR)/html/index.html
# # #конец стадии gcov_report

clean : 
# Чистим объектные файлы функций и файл библиотеки
	rm -rf $(OBJECTS)
# # Чистим объектные файлы тестов и исполняемый файл
# 	rm -rf $(TESTS_OBJECTS) $(TEST_PROGRAM)
# # Чистим файлы, сгенерированные gcov/lcov/genhtml и удаляем папку с вебмордой ака html
# 	rm -rf $(GCOV_RESULT) $(GCOV_REPORT_DIR)
# #	rm -rf *.gcno
#конец стадии clean