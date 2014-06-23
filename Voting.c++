// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

#include "Voting.h"


// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
	int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
	int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// collatz_eval
// ------------
int volting_eval (int i, int j) {
    return 0;
}


// -------------
// collatz_print
// -------------

void voting_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    // while (true) {
    // 	const std::pair<int, int> p = collatz_read(r);
    // 	if (p == std::make_pair(0, 0))
    // 		return;
    //     const int v = collatz_eval(p.first, p.second);
    //     collatz_print(w, p.first, p.second, v);
    // }

}
        
