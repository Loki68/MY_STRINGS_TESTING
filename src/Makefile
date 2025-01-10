PROGRAM = s21_strings_tests
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

LIBRARY = ../libs
CLIBS = -L$(LIBRARY) -l:s21_string.a

SOURCE = main.c s21_sprintf.c s21_string_helpers.c
OBJECTS = main.o s21_sprintf.o s21_string_helpers.o

#all : clean copy_lib build_program

all : clean format build_program

build_program : s21_string_helpers s21_sprintf main
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(CLIBS)

main :
	$(CC) $(CFLAGS) -c main.c -o main.o

s21_sprintf :
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o

s21_string_helpers :
	$(CC) $(CFLAGS) -c s21_string_helpers.c -o s21_string_helpers.o

copy_lib : 
	cp -rf ../../MY_STRINGS/src/s21_string.a ../../MY_STRINGS/src/s21_string.h ../libs

format :
	clang-format -i *.c *.h

clean : 
	rm -rf $(OBJECTS) $(PROGRAM)
	
clean_lib :
	$(LIBRARY)/*.a $(LIBRARY)/*.h