SRCS := $(shell find . -name "*.c" -maxdepth 1)
LIBS := $(shell find ../lib -name "*.c" -maxdepth 1)

all: target library

target: ../src/fuzzer.c ../src/file.c ../src/whitebox.c ../src/mutation.c
	for test_driver in $(SRCS) ; \
	do \
		gcc -o ."$$(echo $$test_driver | cut -f 2 -d '.')" $$test_driver \
			-I../include/ \
			../src/fuzzer.c ../src/file.c ../src/whitebox.c ../src/mutation.c ;  \
	done

library:
	for code in $(LIBS) ; \
	do \
		cd ../lib && gcc --coverage -o ../"$$(echo $$code | cut -f 3 -d '.')" $$code ; \
	done 
	# cp ./*.gcno ../lib ;

clean: 
	rm -rf tmp.* *.gcda *.gcno *.gcov
	for test_driver in $(SRCS) ; \
	do \
		rm -rf ."$$(echo $$test_driver | cut -f 2 -d '.')" ; \
		rm -rf ../lib/*.gcno ../lib/*.gcda ; \
	done
	