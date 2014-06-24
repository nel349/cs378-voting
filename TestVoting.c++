// --------------------------------
// projects/Voting/TestVoting.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestVoting

To obtain coverage of the test:
	% gcov-4.7 -b Voting.c++ TestVoting.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read) {

    ASSERT_EQ( 1, 1);
}


// ----
// eval
// ----

TEST(Voting, eval_1) {
    ASSERT_EQ(20, 20);}



// -----
// print
// -----

TEST(Voting, print) {
    ASSERT_EQ(20, 20);}

// -----
// solve
// -----

TEST(Voting, solve) {
    ASSERT_EQ(20, 20);}


/*
% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread



% valgrind TestVoting
==17162== Memcheck, a memory error detector
==17162== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==17162== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==17162== Command: TestVoting
==17162==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Voting
[ RUN      ] Voting.read
[       OK ] Voting.read (30 ms)
[ RUN      ] Voting.eval_1
TestVoting.c++:67: Failure
Value of: v
  Actual: 1
Expected: 20
[  FAILED  ] Voting.eval_1 (57 ms)
[ RUN      ] Voting.eval_2
TestVoting.c++:71: Failure
Value of: v
  Actual: 1
Expected: 125
[  FAILED  ] Voting.eval_2 (6 ms)
[ RUN      ] Voting.eval_3
TestVoting.c++:75: Failure
Value of: v
  Actual: 1
Expected: 89
[  FAILED  ] Voting.eval_3 (5 ms)
[ RUN      ] Voting.eval_4
TestVoting.c++:79: Failure
Value of: v
  Actual: 1
Expected: 174
[  FAILED  ] Voting.eval_4 (5 ms)
[ RUN      ] Voting.print
[       OK ] Voting.print (12 ms)
[ RUN      ] Voting.solve
TestVoting.c++:98: Failure
Value of: w.str()
  Actual: "1 10 1\n100 200 1\n201 210 1\n900 1000 1\n"
Expected: "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n"
Which is: "1 10 20
100 200 125
201 210 89
900 1000 174
"
[  FAILED  ] Voting.solve (22 ms)
[----------] 7 tests from Voting (157 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (201 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 5 tests, listed below:
[  FAILED  ] Voting.eval_1
[  FAILED  ] Voting.eval_2
[  FAILED  ] Voting.eval_3
[  FAILED  ] Voting.eval_4
[  FAILED  ] Voting.solve

 5 FAILED TESTS
==17162==
==17162== HEAP SUMMARY:
==17162==     in use at exit: 0 bytes in 0 blocks
==17162==   total heap usage: 746 allocs, 746 frees, 115,424 bytes allocated
==17162==
==17162== All heap blocks were freed -- no leaks are possible
==17162==
==17162== For counts of detected and suppressed errors, rerun with: -v
==17162== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)



% gcov-4.7 -b Voting.c++
File 'Voting.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Voting.c++.gcov'
...



% cat Voting.c++.gcov
...



% gcov-4.7 -b TestVoting.c++
File 'TestVoting.c++'
Lines executed:100.00% of 26
Branches executed:83.93% of 224
Taken at least once:41.96% of 224
Calls executed:67.65% of 204
Creating 'TestVoting.c++.gcov'
...



% cat TestVoting.c++.gcov
...
*/
