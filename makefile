all:
	make Voting.zip

clean:
	rm -f Voting.log
	rm -f Voting.zip
	rm -f RunVoting
	rm -f RunVoting.out
	rm -f RunVoting.tmp
	rm -f TestVoting
	rm -f TestVoting.out

doc: Voting.c++
	doxygen Doxyfile

Voting.log:
	git log > Voting.log

Voting.zip: makefile                                  \
             Voting.c++ Voting.h Voting.log           \
             RunVoting.c++ RunVoting.in RunVoting.out \
             UVaVoting.c++                            \
             TestVoting.c++ TestVoting.out
	zip -r Voting.zip                               \
	       makefile html/                           \
           Voting.c++ Voting.h Voting.log           \
           RunVoting.c++ RunVoting.in RunVoting.out \
           UVaVoting.c++                            \
           TestVoting.c++ TestVoting.out

compile: Voting.h Voting.c++ RunVoting.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ RunVoting.c++ -o RunVoting

RunVoting.out: RunVoting RunVoting.in
	valgrind RunVoting < RunVoting.in > RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

TestVoting.out: TestVoting
	valgrind TestVoting > TestVoting.out

readme:
	echo "Nothing in the read me file" > readme.txt

run:
	./RunVoting < RunVoting.in > RunVoting.out

Debug:
	g++-4.7 UVaVoting.c++ -g -o UVaVoting

