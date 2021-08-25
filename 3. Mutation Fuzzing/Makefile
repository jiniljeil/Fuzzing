all: cat_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c 
	gcc -o cat_test_driver cat_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c 
	gcc -o troff_bug_detect lib/troff_bug_detect.c 
	gcc -o troff_test_driver troff_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c 
	# gcc -o hunspell_test_driver hunspell_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c  
	# gcc -o cgi_decode_test_driver cgi_decode_test_driver.c src/fuzzer.c src/file.c src/whitebox.c src/mutation.c  

clean:
	rm -rf cat_test_driver tmp.* troff_buf_detect troff_bug_detect troff_test_driver lib/troff_buf_detect mutation_fuzzing_test
	rm -rf hunspell_test_driver cgi_decode_test_driver *.gcno *.gcda cgi_decode *.gcov lib/cgi_decode 

