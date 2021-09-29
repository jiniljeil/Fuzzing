all: cat_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c
	gcc -o cat_test_driver cat_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c
	gcc -o troff_test_driver troff_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c
	# gcc -o hunspell_test_driver hunspell_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c  
	gcc -o cgi_decode_test_driver cgi_decode_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c
	gcc -o bc_test_driver bc_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c
	gcc -o crashme_test_driver crashme_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c src/schedule.c

clean:
	rm -rf cat_test_driver tmp.* troff_test_driver mutation_fuzzing_test cgi_decode.c.gcov bc_test_driver crashme_test_driver
	rm -rf hunspell_test_driver cgi_decode_test_driver *.gcno *.gcda *.gcov

