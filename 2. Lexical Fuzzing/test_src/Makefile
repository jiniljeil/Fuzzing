all: ../src/simpleFuzzer.c ../src/file.c ../src/dictionary.c ../src/airport.c ../src/runner.c ../src/programRunner.c ../src/randomFuzzer.c
	gcc -o 1_invoking_external_programs 1_invoking_external_programs.c ../src/simpleFuzzer.c ../src/file.c
	gcc -o 2_bugs_fuzzers_find 2_bugs_fuzzers_find.c ../src/simpleFuzzer.c
	gcc -o 4_information_leaks 4_information_leaks.c ../src/simpleFuzzer.c
	gcc -o 5_program_specific_checkers 5_program_specific_checkers.c ../src/dictionary.c ../src/airport.c
	gcc -o 6_fuzzing_architecture 6_fuzzing_architecture.c ../src/runner.c ../src/programRunner.c
	gcc -o 7_fuzzer_test 7_fuzzer_test.c ../src/randomFuzzer.c
1_invoking_external_programs:
	gcc -o 1_invoking_external_programs 1_invoking_external_programs.c ../src/simpleFuzzer.c ../src/file.c

2_bugs_fuzzers_find:
	gcc -o 2_bugs_fuzzers_find 2_bugs_fuzzers_find.c ../src/fuzzer.c

4_information_leaks:
	gcc -o 4_information_leaks 4_information_leaks.c ../src/fuzzer.c

5_program_specific_checkers:
	gcc -o 5_program_specific_checkers 5_program_specific_checkers.c ../src/dictionary.c ../src/airport.c

6_fuzzing_architecture:
	gcc -o 6_fuzzing_architecture 6_fuzzing_architecture.c ../src/programRunner.c

7_fuzzer_test: 
	gcc -o 7_fuzzer_test 7_fuzzer_test.c ../src/randomFuzzer.c
 
clean:
	rm -rf 1_invoking_external_programs 2_bugs_fuzzers_find 4_information_leaks fuzzer.o tmp.* error output program 5_program_specific_checkers 6_fuzzing_architecture 7_fuzzer_test
