CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

TEST_LIB = ./tests/*.c
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LINK_FLAGS = -lcheck

FILES = *.c
OBJECTS = *.o 

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) 
	LINK_FLAGS += -lm -lsubunit
endif

all: s21_matrix.a

clean:
	rm -fr *.o *.a *.gch *.gcno *.gcda test gcov_test s21_test.info ./report test

s21_matrix.a:
	$(CC) $(CFLAGS) -c $(FILES)
	ar rcs s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a

gcov_report: 
	$(CC) $(FLAGS) $(GCOV_FLAGS) ${TEST_LIB} ${FILES} ${LINK_FLAGS} -o test
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open report/index.html	

test: clean
	$(CC) $(FLAGS) $(LEAKS) $(FILES) ${TEST_LIB} ${LINK_FLAGS} -o test
	./test

leaks: test
ifeq ($(UNAME_S), Linux) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
endif
ifeq ($(UNAME_S), Darwin) 
	leaks -quiet -atExit -- ./test
endif