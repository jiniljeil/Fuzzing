all: invoking_external_programs.c src/fuzzer.c 
	gcc -o invoking_external_programs invoking_external_programs.c src/fuzzer.c

long_running_fuzzing:
	gcc -o invoking_external_programs invoking_external_programs.c src/fuzzer.c

clean:
	rm -rf invoking_external_programs fuzzer.o
