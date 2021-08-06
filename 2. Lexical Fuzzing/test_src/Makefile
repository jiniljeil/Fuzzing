all: invoking_external_programs.c ../src/fuzzer.c ../src/file.c ../src/dictionary.c
	gcc -o invoking_external_programs invoking_external_programs.c ../src/fuzzer.c ../src/file.c
	gcc -o bugs_fuzzers_find bugs_fuzzers_find.c ../src/fuzzer.c
	gcc -o information_leaks information_leaks.c ../src/fuzzer.c
	gcc -o program_specific_checkers program_specific_checkers.c ../src/dictionary.c

invoking_external_programs:
	gcc -o invoking_external_programs invoking_external_programs.c ../src/fuzzer.c ../src/file.c

bugs_fuzzers_find:
	gcc -o bugs_fuzzers_find bugs_fuzzers_find.c ../src/fuzzer.c

information_leaks:
	gcc -o information_leaks information_leaks.c ../src/fuzzer.c

program_specific_checkers:
	gcc -o program_specific_checkers program_specific_checkers.c ../src/dictionary.c

clean:
	rm -rf invoking_external_programs bugs_fuzzers_find information_leaks fuzzer.o tmp.* error output program program_specific_checkers
