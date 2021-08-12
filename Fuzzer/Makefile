all: run.c testdriver.c fuzzer.c create_input.c 
	gcc -o testdriver testdriver.c fuzzer.c create_input.c run.c oracle.c


clean:
	rm -rf testdriver