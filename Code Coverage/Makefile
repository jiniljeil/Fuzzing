all: src/coverage.c black_box_testing.c 
	gcc -fprofile-arcs -ftest-coverage -o black_box_testing black_box_testing.c src/coverage.c

clean: 
	rm -rf black_box_testing *.gcov *.gcda *.gcno