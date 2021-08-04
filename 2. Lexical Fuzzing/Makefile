all: invoking_external_programs.c fuzzer.c 
	gcc -o invoking_external_programs invoking_external_programs.c fuzzer.c

long_running_fuzzing:
	gcc -o invoking_external_programs invoking_external_programs.c fuzzer.c

clean:
	rm -rf invoking_external_programs fuzzer.o
