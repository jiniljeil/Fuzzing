SRCS := $(shell find . -name "*.c" -maxdepth 1)
LIBS := $(shell find ../lib -name "*.c" -maxdepth 1)
COVERAGE := --coverage 
LIB_PATH := ../lib
TARGET_LIST = cgi_decode.c crashme.c troff_bug_detect.c

all: target library

target: ../src/fuzzer.c ../src/file.c ../src/whitebox.c ../src/mutation.c ../src/schedule.c
	for test_driver in $(SRCS) ; \
	do \
		gcc -o ."$$(echo $$test_driver | cut -f 2 -d '.')" $$test_driver \
			-I../include/ \
			../src/fuzzer.c ../src/file.c ../src/whitebox.c ../src/mutation.c ../src/schedule.c ;  \
	done

library: $(LIB_PATH)/cJSON.c
	cd $(LIB_PATH) && gcc $(COVERAGE) -o $(LIB_PATH)/json_parser $(LIB_PATH)/json_parser.c $(LIB_PATH)/cJSON.c
	
	for t in $(TARGET_LIST) ; \
	do \
		cd $(LIB_PATH) && gcc $(COVERAGE) -o $(LIB_PATH)/"$$(echo $$t | cut -f 1 -d '.')" $(LIB_PATH)/$$t ; \
	done
	
clean: 
	rm -rf tmp.* *.gcda *.gcno *.gcov
	for test_driver in $(SRCS) ; \
	do \
		rm -rf ."$$(echo $$test_driver | cut -f 2 -d '.')" ; \
		rm -rf ../lib/*.gcno ../lib/*.gcda ; \
	done
	