all: ../src/fuzzer.c ../src/file.c ../src/dictionary.c ../src/airport.c ../src/runner.c ../src/programRunner.c
	gcc -o 1_invoking_external_programs 1_invoking_external_programs.c ../src/fuzzer.c ../src/file.c
	gcc -o 2_bugs_fuzzers_find 2_bugs_fuzzers_find.c ../src/fuzzer.c
	gcc -o 4_information_leaks 4_information_leaks.c ../src/fuzzer.c
	gcc -o 5_program_specific_checkers 5_program_specific_checkers.c ../src/dictionary.c ../src/airport.c
	gcc -o 6_fuzzing_architecture 6_fuzzing_architecture.c ../src/runner.c ../src/programRunner.c

invoking_external_programs:
	gcc -o 1_invoking_external_programs 1_invoking_external_programs.c ../src/fuzzer.c ../src/file.c

bugs_fuzzers_find:
	gcc -o 2_bugs_fuzzers_find 2_bugs_fuzzers_find.c ../src/fuzzer.c

information_leaks:
	gcc -o 4_information_leaks 4_information_leaks.c ../src/fuzzer.c

program_specific_checkers:
	gcc -o 5_program_specific_checkers 5_program_specific_checkers.c ../src/dictionary.c ../src/airport.c

fuzzing_architecture:
	gcc -o 6_fuzzing_architecture 6_fuzzing_architecture.c ../src/runner.c ../src/programRunner.c


clean:
	rm -rf 1_invoking_external_programs 2_bugs_fuzzers_find 4_information_leaks fuzzer.o tmp.* error output program 5_program_specific_checkers 6_fuzzing_architecture
