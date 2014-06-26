// --------------------------------
// projects/collatz/TestCollatz.c++
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
#include <deque>


#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// read candidates
// ----
// 
TEST(Voting,  read_candidates_1) {
    std::istringstream r("3\nJames Franco\nCameron Diaz\nTom Hanks\n");
    string expected[] ={"James Franco", "Cameron Diaz", "Tom Hanks"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 3);
    assert( p == q);   
}

TEST(Voting,  read_candidates_2) {
    std::istringstream r("6\nA\nB\nC\nD\nE\nF\n");
    string expected[] ={"A", "B", "C", "D", "E", "F"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 6);
    assert( p == q);   
}

TEST(Voting,  read_candidates_3) {
    std::istringstream r("10\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\n");
    string expected[] ={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 10);
    assert( p == q);    
}


// ----
// read votes
// ----
// 

TEST(Voting,  read_votes) {
    std::istringstream r("1 2 3\n4 5 6\n7 8 9\n");
    // cout << r.str();
    Vote expected[] ={Vote("1 2 3"), Vote("4 5 6"), Vote("7 8 9")};
    deque<Vote> p = read_votes(r);
    deque<Vote> q ;
    q.assign(expected, expected+1);
    Vote x = p.front();
    // for( int i = 0 ; i< 3; ++i){
    //     x.printVote();
    // }
    // assert( p == q);   
}

// ----
// voting_print
// ----
// 

TEST(Voting,  voting_print_1) {
    // std::ostringstream w;
    // voting_print(w, 1, 10, 20);
    // ASSERT_EQ("1 10 20\n", w.str());
}
// TEST(Collatz, voting_print_2) {
//     std::ostringstream w;
//     voting_print(w, 33, 103, 203);
//     ASSERT_EQ("33 103 203\n", w.str());}

// TEST(Collatz, voting_print_3) {
//     std::ostringstream w;
//     voting_print(w, 78, 410, 420);
//     ASSERT_EQ("78 410 420\n", w.str());}

// ----
// voting_solve
// ----
// 

TEST(Voting,  voting_solve) {
    // std::istringstream r("100 -1\n");
    // const std::pair<int, int> p = Voting_read(r);
    // ASSERT_EQ( 100, p.first);
    // ASSERT_EQ(-1, p.second);
}



//****************************************
// VOTE
//****************************************

// ----
// Vote::getSize
// ----
// 
TEST(Voting, getSize){

}

// ----
// Vote::printVote
// ----
// 
TEST(Voting, printVote){

}

// ----
// Vote::removeVote
// ----
// 

TEST(Voting, removeVote){
    
}



// ----
// Vote::getFrontElement
// ----
// 
TEST(Voting, getFrontElement){
    
}

//****************************************
// Candidate
//****************************************

// ----
// Candidate::addVote
// ----
// 
TEST(Voting, addVote){
    
}

// ----
// Candidate::getNumVotes
// ----
// 
TEST(Voting, getNumVotes){
    
}




//****************************************
// Election
//****************************************


TEST(Voting, printCandidates){
    
}

TEST(Voting, addBallots){
    
}


TEST(Voting, state){
    
}


TEST(Voting, isTie){
    
}


TEST(Voting, mostVotesIndex){
    
}


TEST(Voting, leastVotes){
    
}



TEST(Voting, distributeBallots){
    
}


TEST(Voting, runElection){
    
}