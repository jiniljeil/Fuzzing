all: exercise2.c exercise3.c exercise4.c my_sqrt_test.c src/my_sqrt.c src/shellsort.c src/quadratic.c
	gcc -o exercise2 exercise2.c src/shellsort.c
	gcc -o exercise3 exercise3.c src/quadratic.c src/my_sqrt.c
	gcc -o exercise4 exercise4.c src/my_sqrt.c
	gcc -o my_sqrt_test my_sqrt_test.c src/my_sqrt.c

exercise2: 
	gcc -o exercise2 exercise2.c src/shellsort.c

exercise3: 
	gcc -o exercise3 exercise3.c src/quadratic.c src/my_sqrt.c

exercise4: 
	gcc -o exercise4 exercise4.c src/my_sqrt.c

my_sqrt_test:
	gcc -o my_sqrt_test my_sqrt_test.c src/my_sqrt.c

clean:
	rm -rf my_sqrt_test exercise2 exercise3	exercise4 my_sqrt.o shellsort.o quadratic.o