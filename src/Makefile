CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
GCOV = --coverage
UNIT = unit_tests
STLIB = s21_smart_calc.a
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
    LIBS := -lcheck
else
    LIBS := -lcheck_pic -lpthread -lrt -lm -lsubunit -g
endif

all: clean s21_smart_calc.a

s21_smart_calc.a: build_s21_smart_calc

build_s21_smart_calc:
	@$(CC) -c s21_*.c
	@ar rcs $(STLIB) s21_*.o
	@ranlib $(STLIB)

test: $(STLIB)
	@$(CC) $(FLAGS) unit_tests.c $(STLIB) -o $(UNIT) $(LIBS)
	@./$(UNIT)

gcov_report: $(STLIB)
	@$(CC) $(FLAGS) $(GCOV) unit_tests.c s21_*.c -o $(UNIT) $(LIBS)
	@./$(UNIT)
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	open report/src/index.html

check: $(STLIB)
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	@cppcheck --suppress=missingIncludeSystem *.c *.h
	@CK_FORK=no leaks --atExit -- ./$(UNIT)

install:
	@make clean
	@mkdir build_calk
	@cd smartcalc && qmake && make && make clean && rm Makefile && cd ../ && mv smartcalc/restest.app build_calk
open:
	cd build_calk && open restest.app

uninstall:
	@rm -rf build_calk*

dvi:
	@open dvi.md

dist:
	@rm -rf Archive_SmartCalc_v1.0/
	@mkdir Archive_SmartCalc_v1.0/
	@mkdir Archive_SmartCalc_v1.0/src
	@mv ./build_calk/restest.app Archive_SmartCalc_v1.0/src/
	@tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	@rm -rf Archive_SmartCalc_v1.0/

coverage:
	@open report/index.html

clean:
	@rm -rf *.o *.a *.gc* *.info test report *dSYM $(UNIT) CPPLINT.cfg Archive_SmartCalc_v1.0 *tgz build_calk
