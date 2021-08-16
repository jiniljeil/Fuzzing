all: cat_test_driver.c src/fuzzer.c src/create_input.c src/file.c
	gcc -o cat_test_driver cat_test_driver.c src/fuzzer.c src/create_input.c src/file.c
	gcc -o troff_bug_detect troff_bug_detect.c 
	gcc -o troff_test_driver troff_test_driver.c src/fuzzer.c src/create_input.c src/file.c
	
clean:
	rm -rf cat_test_driver tmp.* troff_buf_detect troff_bug_detect troff_test_driver