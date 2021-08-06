all: invoking_external_programs.c ../src/fuzzer.c ../src/file.c
	gcc -o invoking_external_programs invoking_external_programs.c ../src/fuzzer.c ../src/file.c
	gcc -o bugs_fuzzers_find bugs_fuzzers_find.c ../src/fuzzer.c

long_running_fuzzing:
	gcc -o invoking_external_programs invoking_external_programs.c ../src/fuzzer.c ../src/file.c

invoking_external_programs:
	gcc -o bugs_fuzzers_find bugs_fuzzers_find.c ../src/fuzzer.c
	
clean:
	rm -rf invoking_external_programs fuzzer.o tmp.* error output
