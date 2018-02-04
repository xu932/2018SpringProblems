CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS) 
VALGRIND = valgrind --tool=memcheck --leak-check=full
SRCS = pe04.c pe04.h main.c

all: pe02 testcase

pe02:$(SRCS)
	$(GCC) $(SRCS)
	mv a.out pe04

testcase: test1 test2 test3 test4 clean

test1: pe04
	./pe04 database.txt -a > output.txt
	diff output.txt expected1.txt

test2: pe04
	./pe04 database.txt -s > output.txt
	diff output.txt expected2.txt

test3: pe04
	./pe04 database.txt -s aaaaaaaaaaa > output.txt
	diff output.txt expected3.txt

test4: pe04
	./pe04 database.txt -s Ori > output.txt
	diff output.txt expected4.txt

mem1: pe04
	$(VALGRIND) ./pe04 database.txt -a

mem2: pe04
	$(VALGRIND) ./pe04 database.txt -s

mem3: pe04
	$(VALGRIND) ./pe04 database.txt -s aaa

mem4: pe04
	$(VALGRIND) ./pe04 database.txt -s Ori

mem5: pe04
	$(VALGRIND) ./pe04

mem6: pe04
	$(VALGRIND) ./pe04 aaa.txt -a 

clean:
	rm -rf a.out.dSYM
	rm -rf pe04.h.gch
	rm -rf output.txt
