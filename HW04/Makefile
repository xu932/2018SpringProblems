CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS) 

SRCS = pe04.c pe04.h main.c

all: pe02 testcase

pe02:$(SRCS)
	$(GCC) $(SRCS)
	mv a.out pe04

testcase: test1 test2 test3 test4

test1: pe04
	./pe04 database.txt -a > output.txt
	diff output.txt expected.txt

test2: pe04
	./pe04 database.txt -s > output.txt
	diff output.txt "Wrong arguments\n"

test3: pe04
	./pe04 database.txt -s aaaaaaaaaaa > output.txt
	diff output.txt "No this student\n"

test4: pe04
	./pe04 database.txt -s Ori > output.txt
	diff output.txt "ID:110, Name:Ori, Major: ME, Enrollment:Yes, Year:Senior, Age:21"

test5: pe04
	valgrind ./pe04 database.txt -a

clean:
	rm -rf a.out.dSYM
	rm -rf pe04.h.gch
	rm -rf output.txt
